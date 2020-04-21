#ifndef _QUEUE_H_
#define _QUEUE_H_

#include"list.hpp"

template <typename T>
class queue : public list<T>
{
public:
    queue() {}
    ~queue() {}

    void queue<T>::enqueue(const T & e)
    {   this->insert_before(this->tail(), e);  }

    T queue<T>::dequeue()
    {   this->remove(this->first());    }

    T & queue<T>::front() const
    {   return this->first()->data; }
};

#endif
