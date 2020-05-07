#ifndef _STACK_H_
#define _STACK_H_

#include"vec.hpp"

template <typename T>
class stack : public vec<T>
{
public:
    stack() {}
    ~stack() {}
    bool empty() const
    {   return this->size() == 0 ? true : false;    }

    bool is_empty() const
    {   return empty(); }

    void push(T const & e)
    {   this->insert(this->size(), e); }

    T & top()
    {   return this->get(this->size() - 1); }

    T pop()
    {   return this->remove(this->size() - 1);  }
};

#endif
