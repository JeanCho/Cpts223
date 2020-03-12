/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;
using std::get;

//
// Separate chaining based hash table - inherits from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
public:
    ChainingHash(int n = 11) {
        chain.resize(n);
    }

    ~ChainingHash() {
        this->clear();
        
    }
private:
    //vector<std::pair<K,list<V>>> c;

    vector<list<std::pair<K,V>>> chain;
    
    
    
    int currentSize =0;
     

    bool empty() {
        if(currentSize == 0)
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

       list<std::pair<K,V>> Tlist =chain[hashnum];
       for(auto el : Tlist) // pair in list
       {
           if(el.first == key)
           {
               
               return  el.second;
           }
       }
       throw std::out_of_range("Key not in hash");
       
       
        
    }

    V& operator[](const K& key) {
        
    //     int hashnum = hash(key);
    //     //std::cout<<" [][][][][][] ########"<<endl;
    //    list<std::pair<K,V>> Tlist =chain[hashnum];
       
       
    //    for(auto el =Tlist.begin(); el != Tlist.end();el++) // pair in list
    //    {    std::cout<<" inside FOR######################"<<endl;
    //        if((*el).first == key)
    //        {
                
              
    //            return ((*el).second);
               
    //        }
    //    }
        for(size_t i =0; i<chain.size(); i++)
        {
           
            for(auto itr=chain[i].begin(); itr!= chain[i].end();itr++)
            {
                std::cout<<" [catch]]]]]]]]]]]]]]]]"<<endl;
                if(itr->first ==key)
                {
                     
                    return itr->second;
                }
            }
        }
       throw std::out_of_range("Key not in hash");
       
      
       
       
    }

    int count(const K& key) {
        //how many element of key k
        int count =0;
        int hashnum = hash(key);

       list<std::pair<K,V>> Tlist =chain[hashnum];
       for(auto el : Tlist) // pair in list
       {
           if(el.first == key)
           {
               
               
                   count++;
               
               
           }
       }
        return count;
    }

    void emplace(K key, V value) {

        int hashnum = hash(key);
        bool emplaced =false;
        //std::cout<<" emplace########"<<endl;
       list<std::pair<K,V>> Tlist =chain[hashnum];
       
       for(auto el =Tlist.begin(); el != Tlist.end();el++) // pair in list
       {
           if((*el).first == key)
           {
               //std::pair<K,V> ss = <key, value>;
               Tlist.push_back(std::make_pair(key,value));
               currentSize ++; //update current size
               //std::cout<<"V :   "<<(*el).second<<endl;
               emplaced = true;
               
           }
       }
       if(!emplaced) //if the list is empty
       {
           //std::cout<<" emplace########"<<endl;
           
           Tlist.push_back(std::make_pair(key,value));
           currentSize++;
       }
       

    }

    void insert(const std::pair<K, V>& pair) {

         int hashnum = hash(pair.first);
        bool inserted =false;
       list<std::pair<K,V>> Tlist =chain[hashnum];
       for(auto el =Tlist.begin(); el != Tlist.end();el++) // pair in list
       {
           if((*el).first == pair.first)
           {
               //std::pair<K,V> ss = <key, value>;
               Tlist.push_back(pair);
               currentSize ++; //update current size
               inserted =true;
           }
       }
       if(inserted == false)
       {
           Tlist.push_back(pair);
           currentSize ++;
           inserted = true;
       }
        
        //c[pair.fist].second = pair.second;
        //something for new key
        
    }

    void erase(const K& key) {

        int erased = count(key);

        int hashnum = hash(key);

       list<std::pair<K,V>> Tlist =chain[hashnum];
       for(auto el =Tlist.begin(); el != Tlist.end();el++) // pair in list
       {
           if((*el).first == key)
           {
               
               Tlist.erase(el);
               currentSize = currentSize - erased; //update current size
           }
       }

    }

    void clear() {
        chain.clear();
        currentSize =0;
    }

    int bucket_count() {
        int count =0;
        //list<std::pair<K,V>> Tlist =chain[n];
       for(auto el : chain) // buckets (number of vector) in the hash
       {
           
               count++;
         
           
       }
        return count;
    }

    int bucket_size(int n) {
        int size =0;

       

       list<std::pair<K,V>> Tlist =chain[n];
       for(auto el : Tlist) // pair in list
       {
           
               
         size++;
           
       }
        return size;
    }

    int bucket(const K& key) {

        int count=0;
        for(const auto  &blist : chain)
        {
            for(const auto &bpair : blist )
            {  
                
                if(bpair.first == key)
                {
                    
                    return count;
                }
                count++;
               
            }
        }
        throw std::out_of_range("Key not in hash");
    }

    float load_factor() {

        int numbucket =  this->bucket_count();
        return currentSize/numbucket;
    }

    void rehash() {
        int numbucket =  this->bucket_count();
        int hashsize = findNextPrime(2*numbucket);
    }

    void rehash(int n) {
        int hashsize = findNextPrime(n);
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
        int hashval =key % numbucket;
        return hashval;
        
             // This technicall works, but is very very bad
    }

};

#endif //__CHAINING_HASH_H
