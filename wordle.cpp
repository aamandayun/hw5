#ifndef RECCHECK
// For debugging
//#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void helper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, std::string& curr, std::set<std::string>& result, size_t pos, int dashcount);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    //compute all possible English language words that exist given a string
    //containing the already guessed letters that are in the correct location
    //floating = yellow, has letters that must be part of the word
    // in = -i--m

    std::set<std::string>result;
    std::string curr(in.length(), ' ');
    std::set<std::string> newDict;

    int dashcount = 0;
    int actualDashcount = 0;


    if(in.length()==0){
      return result;
    }

    // for(string s: dict){
    //   if(containsFloaters(s, floating) && s.length()==in.length() && fixed(s, in, dashcount)){
    //     actualDashcount = dashcount;
    //     newDict.insert(s);
    //   }
    // }
    for(char c:in){
      if(c =='-'){
        actualDashcount++;
      }
    }

    helper(in, floating, dict, curr, result, 0, actualDashcount);


    return result;

}

// Define any helper functions here
void helper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, std::string& curr, std::set<std::string>& result, size_t pos, int dashcount){
  if(pos == in.length()){
    if(dict.find(curr)!=dict.end()){
      result.insert(curr);
    }

    return;
  }

  if(in[pos]!='-'){
    curr[pos] = in[pos];
    helper(in, floating, dict, curr, result, pos+1, dashcount);
  }
  else{
    string floatingCopy = floating;
    // cout <<"dashcount: " <<dashcount<<endl;
    // cout << floating.length()<<endl;

    if(dashcount == floating.length() && floating.length()>0){ //changing from == to <=
      for(int i =0; i<floating.length(); i++){
        char c = floating[i];
      //for(char c : floating){
        curr[pos] = c;
        // pos++;
        floatingCopy.erase(floatingCopy.find(c), 1);
        dashcount--; //added this
        // if(in[pos]!='-'){
        //   break;
        // }
        helper(in, floatingCopy, dict, curr, result, pos+1, dashcount);
        floatingCopy = floating;
        dashcount++;
      }
      //helper(in, floatingCopy, dict, curr, result, pos, dashcount);
    }
    else{
      for(char c = 'a'; c<='z'; ++c){
        curr[pos] = c;
        if(floatingCopy.find(c) != string::npos){
          floatingCopy.erase(floatingCopy.find(c), 1);
        }
        
        dashcount--;
        helper(in, floatingCopy, dict, curr, result, pos+1, dashcount);
        dashcount++;
        floatingCopy = floating;
      }
    }
  }
}


