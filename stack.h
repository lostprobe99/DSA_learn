#ifndef _STACK_H_
#define _STACK_H_

#include"vec.h"

template <typename T>
class stack : public vec<T>
{
public:
    stack() {}
    ~stack() {}
    bool empty() const;
    bool is_empty() const { return empty(); };
    void push(T const & e);
    T    pop();
    T &  top();
};

#endif
