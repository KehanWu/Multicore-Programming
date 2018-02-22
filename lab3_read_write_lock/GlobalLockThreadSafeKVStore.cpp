#include <unordered_map>
#include <mutex>
#include <condition_variable>

template <class K, class V> class GlobalLockThreadSafeKVStore {
private:
    std::mutex mut;
    std::condition_variable data_cond;

public:
    std::unordered_map<K,V> map;      // it's better to define map private, but public way provides us convenience to check the element.
    GlobalLockThreadSafeKVStore() {
        map = std::unordered_map<K,V>();
    }
    int insert(K key, V value);
    int accumulate(const K key, const V value);
    int lookup(const K key, V& value);
    int remove(const K key);
    bool empty() const;   // To judge empty should be locked.

};

template <class K,class V> int GlobalLockThreadSafeKVStore<K,V>::insert(K key, V value) {
    std::lock_guard<std::mutex> lk(mut);
    map[key] = value;
    return 0;
}

template <class K,class V> int GlobalLockThreadSafeKVStore<K,V>::accumulate(const K key, const V value) {
    std::lock_guard<std::mutex> lk(mut);
    if (map.empty()) {
        map[key] = value;
        return 0;
    }
    auto search = map.find(key);
    if (search != map.end()) {
        map[key] = search->second + value;
    } else {
        map[key] = value;  // not find.
    }
    return 0;
}

template <class K,class V> int GlobalLockThreadSafeKVStore<K,V>::lookup(const K key, V &value) {
    std::lock_guard<std::mutex> lk(mut);
    if (map.empty()) {
        return -1;
    }
    auto search = map.find(key);
    if(search != map.end()) {
        value = search->second;
        return 0;
    }
    else {
        return -1;
    }
}

template <class K,class V> int GlobalLockThreadSafeKVStore<K,V>::remove(const K key) {
    std::lock_guard<std::mutex> lk(mut);
    if (map.empty()) {
        return 0;
    }
    for (auto& x: map) {
        if (x.first == key) {
            map.erase(key);
        }
    }
    return 0;
}


template <class K,class V> bool GlobalLockThreadSafeKVStore<K,V>::empty() const {
    std::lock_guard<std::mutex> lk(mut);
    return map.empty();
}
