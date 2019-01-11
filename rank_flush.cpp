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
#include "rank_flush.h"

using namespace std;

int get_spare_flushes(const Hand &hand, int i, map<string,int> m){
  int flush = m[string{hand.spare_flushes[i]}];
  return flush;
}
  

void compare_two_hands_flush(const Hand &first, const Hand &second, int i, Winner &winner,
			     map<string,int> m){
  auto k_f = get_spare_flushes(first,i,m);
  auto k_s = get_spare_flushes(second,i,m);

  if(k_f>k_s){
    winner.hands.push_back(first);
  }

  if(k_f<k_s){
    winner.hands.push_back(second);
  }

  if(k_f==k_s){
    if(i<first.spare_flushes.size()-1){
      compare_two_hands_flush(first,second,i+1,winner,m);
    }

    if(i==first.spare_flushes.size()-1){
      winner.hands.push_back(first);
      winner.hands.push_back(second);
    }
  }
}


void rank_flush(const Hand &first, const Hand &second, Winner &winner, map<string,int> m){
  int i=0;
  compare_two_hands_flush(first,second,i,winner,m);
}

void rank_all_different_flush(const Hand &first, const Hand &second, const Hand &third,
			      int i, Winner &winner, map<string,int> m){
  auto k_f = get_spare_flushes(first,i,m);
  auto k_s = get_spare_flushes(second,i,m);
  auto k_t = get_spare_flushes(third,i,m);

  auto maxf = max(k_f,k_s);
  maxf = max(maxf,k_t);

  if(maxf==k_f){
    winner.hands.push_back(first);
  }

  if(maxf==k_s){
    winner.hands.push_back(second);
  }

  if(maxf==k_t){
    winner.hands.push_back(third);
  }
}

void compare_three_hands_flush(const Hand &first, const Hand &second, const Hand &third, int i,
			       Winner &winner, map<string,int> m){
  auto k_f = get_spare_flushes(first,i,m);
  auto k_s = get_spare_flushes(second,i,m);
  auto k_t = get_spare_flushes(third,i,m);

  if((k_f==k_s)&&(k_s==k_t)){
    if(i<first.spare_flushes.size()-1){
      compare_three_hands_flush(first,second,third,i+1,winner,m);
    }

    if(i==first.spare_flushes.size()-1){
      winner.hands.push_back(first);
      winner.hands.push_back(second);
      winner.hands.push_back(third);
    }
  }

  if((k_f!=k_s)&&(k_s!=k_t)){
    rank_all_different_flush(first,second,third,i,winner,m);
  }

  if((k_f==k_s)&&(k_s<k_t)){
    winner.hands.push_back(third);
  }

  if((k_s==k_t)&&(k_t<k_f)){
    winner.hands.push_back(first);
  }

  if((k_t==k_f)&&(k_f<k_s)){
    winner.hands.push_back(second);
  }

  if((k_f==k_s)&&(k_s>k_t)){
    compare_two_hands_flush(first,second,i,winner,m);
  }

  if((k_s==k_t)&&(k_t>k_f)){
    compare_two_hands_flush(second,third,i,winner,m);
  }

  if((k_t==k_f)&&(k_f>k_s)){
    compare_two_hands_flush(third,first,i,winner,m);
  }
}
  
  

void rank_flush(const Hand &first, const Hand &second, const Hand &third, Winner &winner,
		map <string,int> m){
  compare_three_hands_flush(first,second,third,0,winner,m);
}
