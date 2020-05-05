#ifndef _HSAHTABLE_HPP_
#define _HSAHTABLE_HPP_

#include"bitmap.hpp"
#include"dictionary.h"
#include"pub_release.cpp"

template<typename K, typename V>
class Hashtable : public Dictionary<K, V>
{
private:
    Entry<K, V>** ht;
    int M, N;
    Btimap* lazyRemoveal;

    size_t hash_code(char c) const
    {   return (size_t)c;   }

    size_t hash_code(int i) const
    {   return (size_t)i;   }

    size_t hash_code(long long l) const
    {   return (size_t)((l >> 32) + (int)l);   }

    size_t hash_code(const char s[]){
        int h = 0;
        for(; *s != '\0'; s++){
            h = (h << 5) | (h >> 27);
            h += (int)(*s);
        }
        return (size_t)h;
    }

protected:
    int probe4Hit(const K& key);
    int probe4Free(const K& key);
    void rehash();
    inline void markAsRemoved(int x)
    {   lazyRemoveal->set(x);}

    inline void lazilyRemoved(int x)
    {   return lazyRemoveal->test(x);}
public:
    Hashtable(int c = 5);
    ~Hashtable();
    int size() const
    {   return N;   }
    bool put(const K&, const V&);
    V* get(const K&);
    bool remove(const K&);
};

int primeNLT(int c, int n, char * file)
{
    Bitmap B(file, n);
    while(c < n)
    {
        if(B.test(c))   c++;    // 如果不是素数，跳过
        else    return c;
    }
    return c;
}

template<typename K, typename V>
Hashtable<K, V>::Hashtable(int c)
{
    M = primeNLT(c, 1048576, "prime-1048576-bitmap.out");
    N = 0;
    ht = new Entry<K, V>*[M];
    memset(ht, 0, sizeof(Edge<Te>*) * M);
    lazyRemoveal = new Btimap(M);
}

template<typename K, typename V>
Hashtable<K, V>::~Hashtable()
{
    for(int i = 0; i < M; i++)
        if(ht[i])   release(ht[i]);
    release(ht);
    release(lazyRemoveal);
}

template<typename K, typename V>
int Hashtable<K, V>::probe4Hit(const K& k)
{
    int r = hash_code(k) % M;
    while((ht[r] && ht[r]->key != k) || (!ht[r] && lazyRemoveal(r)))
        r = (r + 1) %  M;
}

template<typename K, typename V>
V* Hashtable<K, V>::get(const K& k)
{
    int r = probe4Hit(k);
    return ht[r] ? &(ht[r]->value) : NULL;
}

template<typename K, typename V>
bool Hashtable<K, V>::remove(const K& k)
{
    int r = probe4Hit(k);
    if(!ht[r])  return false;
    release(ht[r]);
    ht[r] = NULL;
    markAsRemoved(r);
    N--;
    return true;
}

template<typename K, typename V>
int Hashtable<K, V>::probe4Free(const K& k)
{
    int r = hash_code(k) % M;
    while(ht[r])  r = (r + 1) % M;
    return r;
}

template<typename K, typename V>
bool Hashtable<K, V>::put(const K& k, const V& v)
{
    // 键已存在
    if(ht[probe4Hit(k)])    return false;
    int r = probe4Free(k);
    ht[r] = new Entry<K, V>(k, v);
    N++;
    if(2 * N > M)   rehash();
    return true;
}

template<typename K, typename V>
void Hashtable<K, V>::rehash()
{
    int old_capacity = M;
    Entry<K, V>** old_ht = ht;
    M = primeNLTi(2 * M, 1048576, "prime-1048576-bitmap.out");
    N = 0;
    ht = new Entry<K, V>*[M];
    memset(ht, 0, sizeof(Entry<K, V>*) * M);
    release(lazyRemoveal);
    lazyRemoveal = new Btimap(M);
    for(int i = 0; i < old_capacity; i++)
    {
        if(old_ht[i])
            put(old_ht[i]->key, old_ht[i]->value);
    }
    release(old_ht);
}

#endif