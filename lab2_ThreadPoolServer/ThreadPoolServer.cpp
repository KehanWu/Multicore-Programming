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
#include <netinet/in.h>
#include <iostream>
#include "httpreq.hpp"
#include "httpresp.hpp"
#include "ThreadSafeKVStore.cpp"
#include "md5.h"

using namespace std;
class ThreadPoolServer {
private:
    int portno;
    ThreadSafeListenerQueue<int> safe_queue;
    ThreadSafeKVStore<std::string, std::string > safe_map;
    ThreadSafeKVStore<std::string, std::string > safe_map_md5;

public:
    ThreadPoolServer(int threads_number) {
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
        while (true) {
            int conn;
            safe_queue.listen(conn);
            HTTPReq request(conn);
            std::string body = "";
            if (request.parse() != -1 || !request.isMalformed()) {
                method = request.getMethod();
                //cout << method << endl;
                std::string uri = request.getURI();
                key = uri.substr(1, uri.size()-1);
                //cout << key << endl;
                if (method == "GET") {
                    code = (safe_map_md5.lookup(md5(key), body) == -1? 404:200);
                } else if (method == "DELETE") {
                    std::string value;
                    if (safe_map_md5.lookup(md5(key), value) == -1) {
                        code = 404;
                    } else {
                        safe_map.remove(key);
                        safe_map_md5.remove(md5(key));
                        code = 200;
                    }
                } else { //post
                    body = request.getBody();
                    safe_map.insert(key, body);
                    safe_map_md5.insert(md5(key),body);
                    code = 200;
                }
                //cout << safe_map.map.size() << endl;
            }
            alive = request.keepAlive();
            //cout << body << endl;
            HTTPResp res(code, body, alive);
            std::string response = res.getResponse();

            write(conn, response.data(), response.size());

            if (alive) {
                safe_queue.push(conn);
            }
            close(conn);
        }
        pthread_exit(NULL);
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
            if (newsockfd < 0) {
                cout << "Error on accept" << endl;
                exit(-1);
            }
            safe_queue.push(newsockfd);
        }
    }
};


