#include <iostream>
#include "ThreadPoolServer.cpp"
#include <random>
#include <getopt.h>
#include <set>
#include <unordered_set>
#include <unistd.h>



using namespace std;

int main(int argc, char* argv[]) {
    bool verbose = false;
    int c;
    int number_thread = 3; // default thread number is 3.
    while ((c = getopt(argc, argv, "n:v")) != -1) {
        switch (c) {
            case 'n': {
                number_thread = atoi(optarg);
                break;
            }
            case 'v': {
                verbose = true;    // to show the detai:ils of httperf usage.
                break;
            }
            default:
                std::cout<< "wrong parameter." << std::endl;
                break;
        }
    }
    ThreadPoolServer *thread_pool = new ThreadPoolServer(number_thread, verbose);
    // the default port is 8889.
    //cout << md5("grape") << endl;
    thread_pool->handleConn();
    return 0; //never return
}