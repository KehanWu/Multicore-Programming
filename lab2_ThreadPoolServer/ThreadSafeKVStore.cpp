#include <unordered_map>
#include <mutex>
#include <pthread.h>

template <class K, class V> class ThreadSafeKVStore {
private:
    pthread_rwlock_t rwlock;
    std::mutex mut;

public:
    std::unordered_map<K,V> map;      // it's better to define map private, but public way provides us convenience to check the element. 
    ThreadSafeKVStore() {
        map = std::unordered_map<K,V>();
    }
    int insert(K key, V value);
    int lookup(const K key, V& value);
    int remove(const K key);
    bool empty() const;   // To judge empty should be locked.

};

template <class K,class V> int ThreadSafeKVStore<K,V>::insert(K key, V value) {
    pthread_rwlock_wrlock(&rwlock);
    map[key] = value;
    pthread_rwlock_unlock(&rwlock);
    return 0;
}

template <class K,class V> int ThreadSafeKVStore<K,V>::lookup(const K key, V &value) {
	pthread_rwlock_tryrdlock(&rwlock);
    if (map.empty()) {
    	pthread_rwlock_unlock(&rwlock);
        return -1;
    }
    auto search = map.find(key);
    if(search != map.end()) {
        value = search->second;
        pthread_rwlock_unlock(&rwlock);
        return 0;
    }
    else {
    	pthread_rwlock_unlock(&rwlock);
        return -1;
    }
}

template <class K,class V> int ThreadSafeKVStore<K,V>::remove(const K key) {
	pthread_rwlock_wrlock(&rwlock);
    if (map.empty()) {
        return 0;
    }
    for (auto& x: map) {
        if (x.first == key) {
            map.erase(key);
        }
    }
    pthread_rwlock_unlock(&rwlock);
    return 0;
}


template <class K,class V> bool ThreadSafeKVStore<K,V>::empty() const {
    std::lock_guard<std::mutex> lk(mut);
    return map.empty();
}