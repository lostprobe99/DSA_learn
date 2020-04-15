#ifndef _QUEUE_H_
#define _QUEUE_H_

#include"list.hpp"

template <typename T>
class queue : public list<T>
{
public:
    queue() {}
    ~queue() {}
    void enqueue(const T & e);
    T    dequeue();
    T &  front() const;
};

#endif
