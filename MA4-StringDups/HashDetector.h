/*
 *  Brute force detector implementation
 * 
 *  Aaron S. Crandall <acrandal@wsu.edu> - 2019
 * 
 */

#ifndef __HASH_DETECTOR_H
#define __HASH_DETECTOR_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>        // a C++11 STL std::unordered_map is a hash table

/*
 *  Function to return a list of the strings appearing more than one time in an input vector
 */
std::vector<std::string> find_duplicates_with_hashtable(std::vector<std::string> & strings) {
    std::vector<std::string> dups;

    // MA TODO: Implement the duplicate finder using a hash table (unordered_map)
    std::unordered_map<std::string, std::string> duplicates_hash;
    bool dupFound = false;
    for(int i =0; i<strings.size(); i++)
    {
        auto curr_string = strings[i];
        if(duplicates_hash.find(curr_string) != duplicates_hash.end())
        {
            dupFound = true;
            bool dup_dup = false;
            for( auto seen_str : dups ) {
                if(seen_str.compare(curr_string) == 0) {
                    dup_dup = true;
                }
            }
            if( !dup_dup ) {
                dups.push_back(curr_string);
            }
                //std::string last_found_dup = dups[ dups.size() - 1 ];
                //if( last_found_dup.compare(strings[i]) != 0 ) {              // Not a dup of a dup
                    //dups.push_back(strings[i]);
                //}
        }
        else
        {
            duplicates_hash.insert({strings[i],""});
        }
        
        

    }
    if(dupFound ==false)
    {
        std::cout<< "No duplicate found"<<std::endl;
        
    }



    return dups;
    // Note on return here: it'duplicates_hash returning to the caller via a move constructor
    // The vector (dups) lives on the stack, but the stored array contents live on the heap
    // When dups is returned, a new vector shall be instantiated using a move constructor
    // The new vector'duplicates_hash move constructor is called with dups as the && other object
}




#endif
