#include <iostream>
#include "ThreadSafeKVStore.cpp"
#include "ThreadSafeListenerQueue.cpp"
#include <random>
#include <getopt.h>
#include <set>
#include <unordered_set>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

struct thread_data {
    int id;
    clock_t launch_time;
    clock_t complete_time;
};

void *test(void* args);
std::string generate_Key();
int32_t generate_Value();
int generate_1to100();
int cnt; // number of current running thread.

std::unordered_set<std::string> key_set;
ThreadSafeListenerQueue<int32_t> *safe_queue;
ThreadSafeKVStore<std::string, int32_t > *safe_map;

using namespace std;

int main(int argc, char* argv[]) {
    int c;
    int number_thread = 5;
    while ((c = getopt(argc, argv, "n:")) != -1) {
        switch (c) {
            case 'n': {
                number_thread = atoi(optarg);
                break;
            }
            default:
                std::cout<< "wrong parameter." << std::endl;
                break;
        }
    }
    key_set = {};
    safe_map = new ThreadSafeKVStore<std::string, int>;
    safe_queue = new ThreadSafeListenerQueue<int32_t>;

    struct thread_data td[number_thread];
    pthread_t threads[number_thread];

    cnt = number_thread;
    for (int i = 0; i < number_thread; i++) {
        td[i].id = i;
        cout << "Thread " << td[i].id << " initialized" << endl;
        pthread_create(&threads[i], NULL, test, (void *)&td[i]);
    }

    int listen_sum = 0;       // listen sum from queue.
    for (int i = 0; i < number_thread; i++) {
        int32_t element = 0;
        safe_queue->listen(element);
        listen_sum += element;
    }

    while (cnt != 0) { // cnt means current running thread number. initialized to n.
        usleep(10);
    }


    // from now on all thread has been terminated.
    int sum_from_map = 0;
    for (std::unordered_map<std::string,int32_t >::iterator it=safe_map->map.begin(); it!=safe_map->map.end(); ++it)
        sum_from_map += it->second;



    for (int i = 0; i < number_thread; i++) {
        cout << "thread " << i << " completion time is: " << td[i].complete_time - td[i].launch_time << endl;
    }
    cout << "time between first lauch and last terminating is: " << td[number_thread-1].complete_time - td[0].launch_time << endl;
    cout << endl;
    cout << "listen from queue sum: " << listen_sum << endl;
    cout << "track of the map sum: " << sum_from_map << endl;
    if (listen_sum == sum_from_map) {
        cout << "Awesome, map and queue being concurrent!" << endl;
    } else {
        cout << "No it's not concurrent." << endl;
    }
    cout << endl;
    pthread_exit(NULL);

}

void *test(void* threadarg) {

    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    my_data->launch_time = clock();
    int32_t sum_value = 0;
    for (int i = 0; i < 10000; i++) {
        if (generate_1to100() <= 20) {
            std::string userkey = generate_Key();
            int32_t uservalue = generate_Value();
            safe_map->accumulate(userkey, uservalue);
            key_set.insert(userkey);
            sum_value += uservalue;
        } else {
            if (!key_set.empty()) {
                auto it = key_set.begin();
                std::string ex = *it;
                int32_t value = 0;
                int res = safe_map->lookup(ex, value);
                if (res != 0) {
                    cout << "Error: no key exist!" << endl;
                }
            }
        }
    }
    safe_queue->push(sum_value);
    cnt--;    // one thread terminated.
    my_data->complete_time = clock();  //record complete time.
    pthread_exit(NULL);
}

std::string generate_Key() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 500);
    int ID = dis(gen);
    std::string result = "user";
    result = result + std::to_string(ID);
    return result;
}

int32_t generate_Value() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int32_t > dis(-256, 256);
    return dis(gen);
}

int generate_1to100() {     // possibility of generated int less or equal than X is X%.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int32_t > dis(1, 100);
    return dis(gen);
}