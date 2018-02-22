//
// Created by Kehan Wu on 2017/11/10.
//
#include "ThreadSafeListenerQueue.cpp"
#include "GlobalLockThreadSafeKVStore.cpp"
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
#include "ThreadSafeKVStore.cpp"
#include "md5.h"
#include <atomic>
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
    ThreadSafeKVStore<std::string, std::string > safe_map;
    ThreadSafeKVStore<std::string, std::string > safe_map_md5;
    GlobalLockThreadSafeKVStore<std::string, std::string> onelock_safe_map;
    GlobalLockThreadSafeKVStore<std::string, std::string> onelock_safe_map_md5;
    ThreadSafeListenerQueue<long> request_time;
    bool verbose;
    std::mutex mut;
    atomic<int> _INSERT_;
    atomic<int> _LOOKUP_;
    atomic<int> _DELETE_;

public:
    ThreadPoolServer(int threads_number, bool verbose) {
        if (verbose) cout << "now it's using global_lock_kvstore" << endl;
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
                    if (!verbose) {
                        code = (safe_map_md5.lookup(md5(key), body) == -1? 404:200);
                    } else {
                        code = (onelock_safe_map_md5.lookup(md5(key), body) == -1? 404:200);
                    }
                    if (isvalid(key)) _LOOKUP_++;
                } else if (method == "DELETE") {
                    if (!verbose) {
                        if (safe_map_md5.lookup(md5(key), body) == -1) {
                            code = 404;
                        } else {
                            safe_map.remove(key);
                            safe_map_md5.remove(md5(key));
                            code = 200;
                        }
                    } else {
                        if (onelock_safe_map_md5.lookup(md5(key), body) == -1) {
                            code = 404;
                        } else {
                            onelock_safe_map.remove(key);
                            onelock_safe_map_md5.remove(md5(key));
                            code = 200;
                        }
                    }
                    _DELETE_++;
                } else { //post
                    body = request.getBody();
                    if (!verbose) {
                        safe_map.insert(key, body);
                        safe_map_md5.insert(md5(key),body);
                    } else {
                        onelock_safe_map.insert(key, body);
                        onelock_safe_map_md5.insert(md5(key),body);
                    }
                    code = 200;
                    _INSERT_++;
                }
                //cout << safe_map.map.size() << endl;
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
                cout << "request complete time: " << timer << endl;
                unsigned long mean, maximum, minimum, median;
                sort_stats_time_queue(mean, maximum, minimum, median);
                cout << request_time.inside_list.size() << endl;
                //updata_time_map(mean, maximum, minimum, median);
                // updata_count_map(_INSERT_, _DELETE_, _LOOKUP_);
                write_to_file(mean, maximum, minimum, median, _INSERT_, _DELETE_, _LOOKUP_);
            }
            delete data;
            close(conn);
        }
        pthread_exit(NULL);
    }

    void write_to_file(unsigned long& mean, unsigned long& maximum, unsigned long& minimum, unsigned long& median,atomic<int>& _INSERT_,atomic<int>& _DELETE_,atomic<int>& _LOOKUP_) {
        ofstream myfile;
        std::string filename = "stats_with_" + to_string(thread_nums) + "_threads";
        if(verbose) {
            filename = filename + "with_global_lock";
        }
        myfile.open(filename, ios::trunc);
        myfile << "mean: " << mean << ". \n";
        myfile << "max: " << maximum << ". \n";
        myfile << "min: " << minimum << ". \n";
        myfile << "median: " << median << ". \n";
        myfile << "lookup: " << _LOOKUP_ << ". \n";
        myfile << "insert: " << _INSERT_ << ". \n";
        myfile << "delete: " << _DELETE_ << ". \n";
        myfile << "total_operation: " << _LOOKUP_+_INSERT_+_DELETE_ << ". \n";
        myfile.close();
    }

    bool isvalid(const std::string key) {
        if (key =="mean" || key=="max" ||key=="min"||key=="median"||key=="insert"||key=="lookup"||key=="delete") {
            return false;
        }
        return true;
    }

    // void updata_count_map(atomic<int>& _INSERT_,atomic<int>& _DELETE_,atomic<int>& _LOOKUP_) {
    //     if (!verbose) {
    //         safe_map_md5.insert(md5("insert"), to_string(_INSERT_));
    //         safe_map_md5.insert(md5("lookup"), to_string(_LOOKUP_));
    //         safe_map_md5.insert(md5("delete"), to_string(_DELETE_));
    //     } else {
    //         onelock_safe_map_md5.insert(md5("insert"), to_string(_INSERT_));
    //         onelock_safe_map_md5.insert(md5("lookup"), to_string(_LOOKUP_));
    //         onelock_safe_map_md5.insert(md5("delete"), to_string(_DELETE_));
    //     }
    // }

    // void updata_time_map(unsigned long& mean, unsigned long& maximum, unsigned long& minimum, unsigned long& median) {
    //     std::string s_mean = to_string(mean);
    //     std::string s_maximum = to_string(maximum);
    //     std::string s_minimum = to_string(minimum);
    //     std::string s_median = to_string(median);
    //     if (!verbose) {
    //         safe_map_md5.insert(md5("mean"), s_mean);
    //         safe_map_md5.insert(md5("max"), s_maximum);
    //         safe_map_md5.insert(md5("min"), s_minimum);
    //         safe_map_md5.insert(md5("median"), s_median);
    //     } else {
    //         onelock_safe_map_md5.insert(md5("mean"), s_mean);
    //         onelock_safe_map_md5.insert(md5("max"), s_maximum);
    //         onelock_safe_map_md5.insert(md5("min"), s_minimum);
    //         onelock_safe_map_md5.insert(md5("median"), s_median);
    //     }
    // }

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
