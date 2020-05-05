#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

template<typename K, typename V>
struct Dictionary
{
    virtual int size() const = 0;
    virtual bool put(const K&, const V&) = 0;
    virtual V* get(const K&) const = 0;
    virtual bool remove(const K&) = 0;
};

#endif