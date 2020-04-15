#ifndef _BTREE_H_
#define _BTREE_H_

#include<stdlib.h>
#include"stack.hpp"
#include"queue.hpp"
#define bnodePosi(T) bnode<T>*

template <typename T>
struct bnode
{
    T data;
    bnodePosi(T) parent;
    bnodePosi(T) lchild;
    bnodePosi(T) rchild;
    int height;

    bnode()
    : parent(NULL), lchild(NULL), rchild(NULL),\
      height(0) {};

    bnode(T const & e,\
          bnodePosi(T) p = NULL,\
          bnodePosi(T) lc = NULL,\
          bnodePosi(T) rc = NULL,\
          int h = 1)
    : data(e), parent(p), lchild(lc),\
      rchild(rc), height(h) {} 

    int          size() const;
    bnodePosi(T) succ() const;
    bnodePosi(T) insertAsLc(T const & e);
    bnodePosi(T) insertAsRc(T const & e);
};

template <typename T>
class btree
{
private:
    int _size;
    bnodePosi(T) _root;
    virtual int update_height(bnodePosi(T) x);
    int update_height_above(bnodePosi(T) x);
    template<typename VST>
    void visit_left_branch(bnodePosi(T) x, VST& visit, stack<bnodePosi(T)>& s);
    void to_left_bottom(bnodePosi(T) x, stack<bnodePosi(T)>& s);
public:
    btree() : _size(0), _root(NULL) {}
    ~btree();
    int          size() const;
    int          remove(bnodePosi(T) x);
    bool         is_empty() const;
    bnodePosi(T) root() const;
    bnodePosi(T) insertAsRoot(const T& e);
    bnodePosi(T) insertAsRc(bnodePosi(T) x, T const &e);
    bnodePosi(T) insertAsLc(bnodePosi(T) x, T const &e);
    template<typename VST>
    void trav_pre(bnodePosi(T) x, VST visit);
    template<typename VST>
    void trav_pre_loop_I(bnodePosi(T) x, VST& visit);
    template<typename VST>
    void trav_pre_loop_II(bnodePosi(T) x, VST& visit);

    template<typename VST>
    void trav_in(bnodePosi(T) x, VST& visit);
    template<typename VST>
    void trav_in_loop_I(bnodePosi(T) x, VST& visit);
    template<typename VST>
    void trav_level(bnodePosi(T) x, VST& visit);
};

#endif
