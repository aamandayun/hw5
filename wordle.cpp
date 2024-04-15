#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

#include <unordered_map>




// Add prototypes of helper functions here
bool containsFloaters(string s, string floating){
  std::unordered_map<char, int> freq;
  
  for(char c : floating){
    if(c != '-'){
      if(s.find(c)==std::string::npos){
        return false;
      }
      s.erase(s.find(c), 1);
    }
    
  }

  return true;
}

bool fixed(string s, string in, int &dashcount){
  int pos = 0;
  for(char c : in){
    if(c!='-'){
      if(s[pos]!=c){
        dashcount = 0;
        return false;
      }
    }else{
      dashcount++;
    }
    
    pos++;
  }

  return true;
  
}

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
      for(char c : floating){
        curr[pos] = c;
        pos++;
        floatingCopy.erase(floatingCopy.find(c), 1);
        dashcount--; //added this
        if(in[pos]!='-'){
          break;
        }
        cout <<c<<endl;
      }
      helper(in, floatingCopy, dict, curr, result, pos, dashcount);
    }
    else{
      for(char c = 'a'; c<='z'; ++c){
        curr[pos] = c;
        helper(in, floating, dict, curr, result, pos+1, dashcount);
      }
    }
  }
}


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
    cout << in<<endl;

    if(in.length()==0){
      return result;
    }

    for(string s: dict){
      if(containsFloaters(s, floating) && s.length()==in.length() && fixed(s, in, dashcount)){
        actualDashcount = dashcount;
        newDict.insert(s);
      }
    }

    helper(in, floating, newDict, curr, result, 0, actualDashcount);


    return result;

}

// Define any helper functions here

