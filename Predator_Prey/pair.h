#ifndef PAIR
#define PAIR

#include <iostream>

using namespace std;

template<typename K, typename V>
struct Pair
{
    Pair()
    {
    }
    Pair(K k, V v)
    {
        key = k;
        value = v;
    }    
    Pair<V,K> Swap()
    {
        return Pair<V,K>(value, key);
    }
    friend ostream& operator <<(ostream& outs, const Pair& PrintMe)
    {
        outs << PrintMe.key << ": " << PrintMe.value;
        return outs;
    }
    K key;
    V value;
};

#endif // PAIR

