#ifndef _PQ_H_
#define _PQ_H_

template<typename T>
class PQ
{
    virtual void insert(const T&) = 0;
    virtual T& get_max() const = 0;
    virtual T del_max() = 0;
};

#endif