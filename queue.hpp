#include"queue.h"
#include"list.h"

template <typename T>
inline void queue<T>::enqueue(const T & e)
{   this->insert_before(this->tail(), e);  }

template <typename T>
inline T queue<T>::dequeue()
{   this->remove(this->first());    }

template <typename T>
inline T & queue<T>::front() const
{   return this->first()->data; }
