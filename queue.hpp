#ifndef _QUEUE_H_
#define _QUEUE_H_

#include"list.hpp"

template <typename T>
class queue : public list<T>
{
public:
    queue() {}
    ~queue() {}

    void enqueue(const T & e)
    {   this->insert_before(this->tail(), e);  }

    T dequeue()
    {   return this->remove(this->first());    }

    T & front() const
    {   return this->first()->data; }
};

#endif
