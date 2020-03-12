#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>
#include "Hash.h"

using std::vector;
using std::pair;
//using namespace std;
// Can be used for tracking lazy deletion for each element in your table
enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename K, typename V>
class ProbingHash : public Hash<K,V> {
private:
    // Needs a table and a size.
    // Table should be a vector of std::pairs for lazy deletion

    vector<pair<int,pair<K,V> > > probe;   
    // 0 if empty 1 if not empty 2 if deleted
    int currentSize =0;
    int defaultbucketnum = 11;

public:
    ProbingHash(int n = 11) {
        
    }

    ~ProbingHash() {
        // Needs to actually free all table contents
        this->clear();
    }

    bool empty() {
        if(currentSize ==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int size() {
        return currentSize;
    }

    V& at(const K& key) {
         int hashnum = hash(key);
        
        pair<int,pair<K,V>> Tpair =probe[hashnum];
        if(currentSize!= 0 &&Tpair.first == key)
        {
            
            pair<K,V> Apair = Tpair.second;
            return Apair.second;
        }
        
        
       throw std::out_of_range("Key not in hash");
    }

    V& operator[](const K& key) {

        int hashnum = hash(key);
        
        pair<int,pair<K,V>> Tpair =probe[hashnum];
        if(currentSize!= 0 &&Tpair.first == key)
        {
            
            pair<K,V> Apair = Tpair.second;
            return Apair.second;
        }
        
       throw std::out_of_range("Key not in hash");
    }

    int count(const K& key) {
         int hashnum = hash(key);

        pair<int,pair<K,V>> Tpair =probe[hashnum];
        if(Tpair.first == key)
        {
            
            return Tpair.first;
        }
    }

    void emplace(K key, V value) {
        int hashnum = hash(key);
         pair<int,pair<K,V>> Tpair =probe[hashnum];
         if(Tpair.first != 1)
         {
             currentSize++;
         }
         Tpair.first =1;
         pair<K,V> Apair = Tpair.second;
         Apair.second = value;
         

    }

    void insert(const std::pair<K, V>& pair) {
        int hashnum = hash(pair.first);
        auto Tpair =probe[hashnum];
        if(Tpair.first != 1)
        {
            currentSize++;
        }
        Tpair.first =1;
        auto Apair = Tpair.second;
        Apair.second = pair.second;
    }

    void erase(const K& key) {
    }

    void clear() {
        probe.clear();
        currentSize =0;

    }

    int bucket_count() {
        int count =0;
        //list<std::pair<K,V>> Tlist =chain[n];
       for(auto el : probe) // buckets (number of vector) in the hash
       {
           
               count++;
         
           
       }
        return count;
    }

    int bucket_size(int n) {
    }

    int bucket(const K& key) {
    }

    float load_factor() {
        int numbucket =  this->bucket_count();
        return currentSize/numbucket;
    }

    void rehash() {
    }

    void rehash(int n) {
        
    }

private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) {
        int numbucket =  this->bucket_count();
        if(numbucket <= 0)
        {
            numbucket =defaultbucketnum;
        }
        int hashval =key % numbucket;
        return hashval;   // This technicall works, but is very very bad
    }
    
};

#endif //__PROBING_HASH_H
