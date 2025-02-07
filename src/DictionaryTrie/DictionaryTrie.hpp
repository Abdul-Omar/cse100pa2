/*  
 * Filename: DictionaryTrie.hpp
 * Author: Abdulkhaliq Omar/Andrew Masters
 * UserId: cs30s2019ac
 * Date:    10/23/2019
 * Sources of Help: None
 * DictionaryTrie.hpp defines classes Comparator(for priority queue comparison) and
 * DictionaryTrie(TST for autocomplete) and defines all functions inside DictionaryTrie
 * that are fully implemented in DictionaryTrie.cpp
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <string>
#include <utility>
#include <vector>
#include <queue>
#include "TrieNode.hpp"

using namespace std;

/*
 * Compare class for priority queue; compares elements
 */
class Comparator {
public:
    int operator()(std::pair<unsigned int, std::string>& a,
                    std::pair<unsigned int, std::string>& b) const {
	
	//compare frequency first
        if (a.first == b.first){ 
	
	  return a.second < b.second;
	}
        else{
          //sort alphabetically 
	  return (a.first > b.first);
       }
    }
};

//priority_queue< pair<unsigned int, string>, vector<pair<unsigned int, string>>, comparator> & pq,
/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
    // add private members and helper methods here
    // pointer to root of DictionaryTrie
    TrieNode * root;
    
    void getWildCard(TrieNode* root, string wildCard, string prefix, vector<pair<string, unsigned int>> & vect, unsigned int index);
    // Helper function for predictCompletions; finds prefix nodes
    TrieNode* getPrefixRoot(TrieNode* root, string prefix, int charIndex)const;

    // Second helper function for predictCompletions; uses recursion to find all words starting from prefix nodes
    void getAllWords(TrieNode* root, string prefix,  priority_queue< pair<unsigned int, string>, vector<pair<unsigned int, string>>, Comparator> & pq,
  int numCompletions);

    // Helper function for insert; uses recursion to insert TrieNodes
    bool insertHelper(string word, unsigned int freq, TrieNode ** node, int i);

    void deleteAll(TrieNode * node);

  public:
    /* Constructor that intializes Dictionary Trie; sets root to null */
    DictionaryTrie();

    /** Insert function returns true if word was inserted, false if it already exists, given a word and its frequency
     *	Calls insertHelper to recursively insert TrieNodes
     */
    bool insert(string word, unsigned int freq);

    /** Find function return true if word is found, false if it can't be found, given a word
     *	Calls getPrefixRoot to recursively find word
     */
    bool find(string word) const;

    /* PredictCompletions returns a vector of all strings given a prefix and number of words below prefix
     * Calls getPrefixRoot to find the prefix nodes
     * Calls getAllWords to recursively find all words below prefix*/
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /* Deconstructor, deletes all nodes and the root */
    ~DictionaryTrie();
};

#endif
