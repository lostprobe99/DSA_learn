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

    void push(T const & e)
    {   this->insert(this->size(), e); }

    T & top()
    {   return this->get(this->size() - 1); }

    T pop()
    {   
        if(this->size() > 0)
            return this->remove(this->size() - 1);  
    }
};

#endif
