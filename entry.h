/*
 * @Author: lostprobe99 
 * @Date: 2020-05-05 15:21:10 
 * @Last Modified by:   lostprobe99 
 * @Last Modified time: 2020-05-05 15:21:10 
 */
#ifndef _ENTRY_H_
#define _ENTRY_H_

template<typename K, typename V> struct Entry{
    K key; V value;
    Entry(K k = K(), V v = V()) : key(k), value(v) {}
    Entry(const Entry<K, V>& e) : key(e.key), value(e.value) {}

    bool operator<  (const Entry<K, V>& e) {    return key < e.key;     }
    bool operator>  (const Entry<K, V>& e) {    return key > e.key;     }
    bool operator<= (const Entry<K, V>& e) {    return key <= e.key;    }
    bool operator>= (const Entry<K, V>& e) {    return key >= e.key;    }
};

#endif