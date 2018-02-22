//
// Created by Kehan Wu on 2017/11/10.
//
#include "ThreadSafeListenerQueue.cpp"
#include "string"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<sys/time.h>
#include <netinet/in.h>
#include <iostream>
#include "httpreq.hpp"
#include "httpresp.hpp"
#include "ThreadSafeKVStoreLRU.cpp"
#include "md5.h"
#include <atomic>
#include <vector>
#include <time.h>
#include <iostream>
#include <fstream>

struct Data{
    int conn;
    struct timeval start;
    struct timeval end;
};

using namespace std;
class ThreadPoolServer {
private:
    int portno;
    int thread_nums;
    ThreadSafeListenerQueue<Data*> safe_queue;
    ThreadSafeKVStoreLRU<std::string, std::string > safe_map;
    ThreadSafeKVStoreLRU<std::string, std::string > safe_map_md5;
    ThreadSafeKVStoreLRU<std::string, std::string > stats_map;

    ThreadSafeListenerQueue<long> request_time;
    bool verbose;
    std::mutex mut;
    atomic<int> _INSERT_;
    atomic<int> _LOOKUP_;
    atomic<int> _DELETE_;
    atomic<int> _CHECK_DISK_;

public:
    ThreadPoolServer(int threads_number, bool verbose) {
        if (verbose) cout << "now it's using LRU cache" << endl;
        else cout << "now it's using only disk without cache" << endl;
        thread_nums = threads_number;
        this->verbose = verbose;
        _INSERT_ = 0;
        _LOOKUP_ = 0;
        _DELETE_ = 0;
        portno = 8889;
        pthread_t threads[threads_number];
        for (int i = 0; i < threads_number; i++) {
            pthread_create(&threads[i], NULL, start_thread,(void*) this);
        }
    }

    static void* start_thread(void *args) {
        ThreadPoolServer* tp = (ThreadPoolServer*) args;
        tp->run();
        return NULL;
    }

    void* run() {
        std::string method, key;
        int code;
        bool alive;
        Data *data;
        while (true) {
            unsigned long timer;
            int conn;
            safe_queue.listen(data);
            conn = data->conn;
            HTTPReq request(conn);
            std::string body = "";
            if (request.parse() != -1 || !request.isMalformed()) {
                method = request.getMethod();
                //cout << method << endl;
                std::string uri = request.getURI();
                key = uri.substr(1, uri.size()-1);
                //cout << key << endl;
                if (method == "GET") {
                    if (verbose) {
                        code = (safe_map_md5.lookup(md5(key), body) == -1? 404:200);
                        if (code == 404) {
                            code = (check_from_disk(key, body)) == 0? 404:200;
                            if (code == 200) {
                                safe_map.insert(key, body);
                            }
                        }
                    } else {
                        code = check_from_disk(key,body)==0 ? 404:200;
                    }
                    if (isvalid(key)) _LOOKUP_++;
                } else if (method == "DELETE") {
                    if (verbose) {
                        if (safe_map_md5.lookup(md5(key), body) == -1) {
                            if (check_from_disk(key,body) == 0) {
                                code = 404;
                            } else {
                                code = 200;
                                string v = "";
                                modify_from_disk(key, v);
                            }
                        } else {
                            safe_map.remove(key);
                            safe_map_md5.remove(md5(key));
                            string v = "";
                            modify_from_disk(key, v); // pass "" value to delete.
                            code = 200;
                        }
                    } else {
                        if (check_from_disk(key, body) == 0) {
                            code = 404;
                        } else {
                            code = 200;
                            string v = "";
                            modify_from_disk(key,v);
                        }
                    }
                    _DELETE_++;
                } else { //post
                    body = request.getBody();
                    //cout << key << "  " << body <<endl;
                    safe_map.insert(key, body);
                    safe_map_md5.insert(md5(key),body);
                    if (check_from_disk(key, body) == 0) {
                        write_KV_to_file(key, body);
                    } else {
                        modify_from_disk(key, body);
                    }
                    code = 200;
                    _INSERT_++;
                }
                //cout << safe_map.map.size() << endl;
                print_stats();
            }
            //cout << body << endl;
            HTTPResp res(code, body);
            std::string response = res.getResponse();
            gettimeofday(&data->end, NULL);
            write(conn, response.data(), response.size());
            timer = 1000000 * (data->end.tv_sec-data->start.tv_sec)+ data->end.tv_usec-data->start.tv_usec;
            if (isvalid(key)) {
                request_time.push(timer);
                request_time.cnt(timer);
                //cout << "request complete time: " << timer << endl;
                unsigned long mean, maximum, minimum, median;
                sort_stats_time_queue(mean, maximum, minimum, median);
                cout << request_time.inside_list.size() << endl;
                updata_time_map(mean, maximum, minimum, median);
                updata_count_map(_INSERT_, _DELETE_, _LOOKUP_);
                //write_performance_to_file(mean, maximum, minimum, median, _INSERT_, _DELETE_, _LOOKUP_);
            }
            delete data;
            close(conn);
        }
        pthread_exit(NULL);
    }

    void write_KV_to_file(const std::string key, const std::string value) {
        ofstream disk ("diskIO.txt", ios::app);
        disk << key <<  endl;
        disk << value << endl;
        disk.close();
    }

    void swipe_file() {
        fstream fs;
        fs.open("diskIO.txt", ios::out);
        fs.close();
    }

    int check_from_disk(const std::string key, string &value) {
        _CHECK_DISK_++;
        cout << "now check from disk" << endl;
        string readk;
        string readv;
        ifstream infile("diskIO.txt");
        while (infile >> readk >> readv) {
            if (readk == key) {
                value = readv;
                return 1;
            }
        }
        return 0;
    }

    void modify_from_disk(const std::string key, const std::string value) {
        vector<string> vec;
        std::ifstream infile("diskIO.txt");
        string readk;
        string readv;
        while (infile >> readk >> readv) {
            if (key != readk) {
                vec.push_back(readk);
                vec.push_back(readv);
            } else {
                if (value != "") {
                    vec.push_back(readk);
                    vec.push_back(value);
                } else {
                    continue;
                }
            }
        }
        infile.close();
        ofstream outFile("diskIO.txt");

        for (int i = 0; i < vec.size(); i++) {
            outFile << vec[i] << endl;
        }
        outFile.close();
    }

//    void write_performance_to_file(unsigned long &mean, unsigned long &maximum, unsigned long &minimum,
//                                   unsigned long &median, atomic<int> &_INSERT_, atomic<int> &_DELETE_,
//                                   atomic<int> &_LOOKUP_) {
//        ofstream myfile;
//        std::string filename = "stats_with_" + to_string(thread_nums) + "_threads";
//        if(verbose) {
//            filename = filename + "with_global_lock";
//        }
//        myfile.open(filename, ios::trunc);
//        myfile << "mean: " << mean << ". \n";
//        myfile << "max: " << maximum << ". \n";
//        myfile << "min: " << minimum << ". \n";
//        myfile << "median: " << median << ". \n";
//        myfile << "lookup: " << _LOOKUP_ << ". \n";
//        myfile << "insert: " << _INSERT_ << ". \n";
//        myfile << "delete: " << _DELETE_ << ". \n";
//        myfile << "total_operation: " << _LOOKUP_+_INSERT_+_DELETE_ << ". \n";
//        myfile.close();
//    }

    bool isvalid(const std::string key) {
        if (key =="mean" || key=="max" ||key=="min"||key=="median"||key=="insert"||key=="lookup"||key=="delete") {
            return false;
        }
        return true;
    }

     void updata_count_map(atomic<int>& _INSERT_,atomic<int>& _DELETE_,atomic<int>& _LOOKUP_) {
         stats_map.insert(md5("insert"), to_string(_INSERT_));
         stats_map.insert(md5("lookup"), to_string(_LOOKUP_));
         stats_map.insert(md5("delete"), to_string(_DELETE_));
     }

     void updata_time_map(unsigned long& mean, unsigned long& maximum, unsigned long& minimum, unsigned long& median) {
         std::string s_mean = to_string(mean);
         std::string s_maximum = to_string(maximum);
         std::string s_minimum = to_string(minimum);
         std::string s_median = to_string(median);
         stats_map.insert(md5("mean"), s_mean);
         stats_map.insert(md5("max"), s_maximum);
         stats_map.insert(md5("min"), s_minimum);
         stats_map.insert(md5("median"), s_median);
     }

    void print_stats() {
        string mean,min,max,median;
        stats_map.lookup(md5("mean"),mean);
        stats_map.lookup(md5("min"),min);
        stats_map.lookup(md5("max"),max);
        stats_map.lookup(md5("median"),median);
        cout << "mean: " << mean << endl;
        cout << "min: " << min << endl;
        cout << "max: " << max << endl;
        cout << "median: " << median << endl;
        cout << "check_disk_time: " << _CHECK_DISK_ << endl;
        cout << "lookup: " << _LOOKUP_ << endl;
        cout << "delete: " << _DELETE_ << endl;
        cout << "insert: " << _INSERT_ << endl;
    }

    void sort_stats_time_queue(unsigned long& mean, unsigned long& maximum,unsigned long& minimum,unsigned long& median) {
        std::lock_guard<std::mutex> lk(mut);
        int size = request_time.inside_list.size();
        request_time.inside_list.sort();
        mean = request_time.sum / size;
        minimum = request_time.inside_list.front();
        maximum = request_time.inside_list.back();
        auto l_median = request_time.inside_list.begin();
        std::advance(l_median, (size -1)/2);
        median = *l_median;
    }

    void handleConn() {
        int sockfd;
        struct sockaddr_in serv_addr;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            cout << "Error opening socket" << endl;
            exit(-1);
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);
        ::bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
        if (listen(sockfd, 5) == -1) {
            perror("listen error");
            exit(-1);
        }
        while (true) {
            struct sockaddr_in cli_addr;
            socklen_t clilen = sizeof(cli_addr);
            int newsockfd;
            newsockfd = accept(sockfd,
                               (struct sockaddr *) &cli_addr, &clilen);
            Data *data = new Data();
            data->conn = newsockfd;
            gettimeofday(&data->start, NULL);
            if (newsockfd < 0) {
                cout << "Error on accept" << endl;
                exit(-1);
            }
            safe_queue.push(data);
        }
    }
};
