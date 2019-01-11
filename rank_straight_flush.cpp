#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include "data_container.h"
#include <map>
#include <typeinfo>
#include <sstream>
#include "deck_operations.h"
#include "compare_hands.h"
#include "rank_straight_flush.h"

using namespace std;


void rank_straight_flush(const Hand &first, const Hand &second, Winner &winner, map<string,int> m){
  auto f = m[first.state_marker];
  auto s = m[second.state_marker];

  if(f>s){
    winner.hands.push_back(first);
  }

  if(f<s){
    winner.hands.push_back(second);
  }

  if(f==s){
    winner.hands.push_back(first);
    winner.hands.push_back(second);
  }
}
  

void rank_straight_flush(const Hand &first, const Hand &second, const Hand &third, Winner &winner, map<string,int> m){
    auto f= m[first.state_marker];
    auto s = m[second.state_marker];
    auto t = m[third.state_marker];
    
    auto maxres = max(f,s);
    maxres = max(maxres,t);

    if((f!=s)&&(s!=t)){
      if(maxres==f){
	winner.hands.push_back(first);
      }
      if(maxres==f){
	winner.hands.push_back(second);
      }
      if(maxres==t){
	winner.hands.push_back(third);
      }
    }

    //some of these cases will never occur
    //(I think we will only have the case when they are community cards)
    //included for completeness - at any rate, it is logically correct to include
    //all these cases, even if they turn out to be redundant in practice
    if((f==s)&&(s>t)){
      winner.hands.push_back(second);
      winner.hands.push_back(first);
    }
    if((f==s)&&(s<t)){
      winner.hands.push_back(third);
    }

    if((s==t)&&(t>f)){
      winner.hands.push_back(second);
      winner.hands.push_back(third);
    }

    if((s==t)&&(t<f)){
      winner.hands.push_back(first);
    }

    if((t==f)&&(f>t)){
      winner.hands.push_back(third);
      winner.hands.push_back(first);
    }

    if((t==f)&&(f<s)){
      winner.hands.push_back(second);
    }

    if((f==s)&&(s==t)){
      winner.hands.push_back(first);
      winner.hands.push_back(second);
      winner.hands.push_back(third);
    }
}
