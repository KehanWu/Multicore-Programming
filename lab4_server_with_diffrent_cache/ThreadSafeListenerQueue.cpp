#include <list>
#include <mutex>
#include <condition_variable>

template <class T> class ThreadSafeListenerQueue {
private:
    std::mutex mut;
    std::condition_variable data_cond;

public:
    std::list<T> inside_list;
    ThreadSafeListenerQueue() {
        inside_list = std::list<T>();
    }
    T sum;
    int push(const T element);
    int pop(T& element);
    int listen(T& element);
    bool empty() const;
    int cnt(T element);
};

template <class T> bool ThreadSafeListenerQueue<T>::empty() const {
    std::lock_guard<std::mutex> lk(mut);
    return inside_list.empty();
}

template <class T> int ThreadSafeListenerQueue<T>::push(const T element) {
    std::lock_guard<std::mutex> lk(mut);
    inside_list.push_back(element);
    data_cond.notify_one();
    return 0;
}
template <class T> int ThreadSafeListenerQueue<T>::cnt(T element) {
    std::lock_guard<std::mutex> lk(mut);
    sum += element;
    return 0;
}

template <class T> int ThreadSafeListenerQueue<T>::pop(T &element) {
    std::lock_guard<std::mutex> lk(mut);
    if (inside_list.empty()) {
        return 1;
    }
    element = inside_list.front();
    inside_list.pop_front();
    return 0;
}

template <class T> int ThreadSafeListenerQueue<T>::listen(T &element) {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{return !inside_list.empty();});  //once empty, wait for notify.
    element = inside_list.front();
    inside_list.pop_front();
    return 0;
}
