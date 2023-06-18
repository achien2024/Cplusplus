// Dictionary.cpp
// Aaron Chien
// 405498016

#include "Dictionary.h"
#include <string> // string variables
#include <vector> // vector variables
#include <cctype>
#include <utility>  
#include <algorithm> // for sort 
#include <functional> // for the hash map used in Nacenberg's slides 
using namespace std;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

  // This class does the real work of the implementation.

class DictionaryImpl
{
  public:
    DictionaryImpl(int maxBuckets);
    ~DictionaryImpl() {}
    // hash map 
        // sort the string alphabetically 
        // use std hash on it 
        // hash function has an index 
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
    int hash_function(string x) const
    {
        sort(x.begin(), x.end());
        // when we do a lookup, look at one bucket
        // for anagrams, the counts are the same and the numbber of each letter are the same too 
        hash<string> str_hash;
        // create a hash function
        unsigned int hashValue = str_hash(x);
        // creates the hash value for a specific string
        unsigned int bucketNum = hashValue % max_buckets;
        // ensure the hash value fits with the map by dividing the max amount of buckets 
        return bucketNum;
    }
  private:
    int max_buckets;
    vector<vector<string> > m_words;
    // my hash map is a vector of vector strings 
};

DictionaryImpl::DictionaryImpl(int maxBuckets)
{
    max_buckets = maxBuckets;
    // constructor of dictionary class
    // sets the number of buckets to max buckets 
    m_words.resize(maxBuckets); 
    // resize the vector to be the max buckets size 
}

void DictionaryImpl::insert(string word)
{
    // to get hash values into vector
    // first figure out the max size of vector
    // modolus the hash number by the max size of the vector, so that it would be in the vector 
    removeNonLetters(word);
    if (!word.empty())
    {
        int bucket = hash_function(word);
        m_words[bucket].emplace_back(word);
        // more efficient method of push_back 
    }
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;

    string permutation = letters;
    int index = hash_function(permutation);
    // get the hash value of the letters, permutation will also be used to sort
    sort(permutation.begin(), permutation.end());
    // sorts the letters itself

    for (int i = 0; i < m_words[index].size(); i++)
    // loop through the vector's bucket's vectors and if the sorted letter equals the same as the sorted string
    // in each index, callback the string 
    {
        string temp_sort = m_words[index][i];
        // creates a temporary string variable
        sort(temp_sort.begin(), temp_sort.end());
        // sorts the temporary string to ensure that the sorted letter to compare is the same, meaning they are anagrams
        // this is to prevent collision 
        if (permutation == temp_sort)
        {
            callback(m_words[index][i]);
        }
    }

    return;
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
} 

//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}
