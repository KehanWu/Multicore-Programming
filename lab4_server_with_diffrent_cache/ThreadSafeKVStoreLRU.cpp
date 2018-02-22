#include <unordered_map>
#include <mutex>
#include <pthread.h>
#include <list>

using namespace std;
template <class K, class V> class ThreadSafeKVStoreLRU {
private:
    pthread_rwlock_t rwlock;
    std::mutex mut;
    list<pair<K,V>> item_list;
    size_t cache_size;

public:
    std::unordered_map<K, decltype(item_list.begin())> map;
    ThreadSafeKVStoreLRU() {
        this->cache_size = 128;
    }
    int insert(K key, V value);
    int lookup(const K key, V& value);
    int remove(const K key);
    bool empty() const;   // To judge empty should be locked.

};

template <class K,class V> int ThreadSafeKVStoreLRU<K,V>::insert(K key, V value) {
    pthread_rwlock_wrlock(&rwlock);
    auto it = map.find(key);
    if (it != map.end()) {
        item_list.erase(it->second);
        map.erase(it);
    }
    item_list.push_front(make_pair(key,value));
    map.insert(make_pair(key, item_list.begin()));
    while (map.size() > cache_size) {
        auto last_ptr = item_list.end();
        last_ptr--;
        map.erase(last_ptr->first);
        item_list.pop_back();
    }
    pthread_rwlock_unlock(&rwlock);
    return 0;
}



template <class K,class V> int ThreadSafeKVStoreLRU<K,V>::lookup(const K key, V &value) {
    pthread_rwlock_tryrdlock(&rwlock);
    if (map.count(key) <= 0) {
        return -1;
    }
    auto it = map.find(key);
    item_list.splice(item_list.begin(), item_list, it->second);
    value = it->second->second;
    pthread_rwlock_unlock(&rwlock);
    return 0;
}

template <class K,class V> int ThreadSafeKVStoreLRU<K,V>::remove(const K key) {
    pthread_rwlock_wrlock(&rwlock);
    if (map.count(key) <= 0) {
        return -1;
    }
    auto it = map.find(key);
    item_list.erase(it->second);
    map.erase(it);
    pthread_rwlock_unlock(&rwlock);
    return 0;
}


template <class K,class V> bool ThreadSafeKVStoreLRU<K,V>::empty() const {
    std::lock_guard<std::mutex> lk(mut);
    return map.empty();
}