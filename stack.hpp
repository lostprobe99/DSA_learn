#include "stack.h"
#include "vec.hpp"

template <typename T>
inline bool stack<T>::empty() const
{   return this->size() == 0 ? true : false;    }

template <typename T>
inline void stack<T>::push(T const & e)
{   this->insert(this->size(), e); }

template <typename T>
inline T & stack<T>::top()
{   return this->get(this->size() - 1); }

template <typename T>
inline T stack<T>::pop()
{   
    if(this->size() > 0)
        return this->remove(this->size() - 1);  
}
