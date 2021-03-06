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
#include "rank_triplet.h"

using namespace std;

int get_triplet_kickers(const Hand &hand, int i, map<string,int> m){
  int kicker = m[string{hand.triplet_kickers[i]}];
  return kicker;
}

void compare_two_hands_triplet(const Hand &first, const Hand &second, int i, Winner &winner,
			       map<string,int> m){
  auto k_f = get_triplet_kickers(first,i,m);
  auto k_s = get_triplet_kickers(second,i,m);

  if(k_f>k_s){
    winner.hands.push_back(first);
  }

  if(k_f<k_s){
    winner.hands.push_back(second);
  }

  if(k_f==k_s){
    if(i<first.triplet_kickers.size()-1){
      compare_two_hands_triplet(first,second,i+1,winner,m);
    }

    if(i==first.triplet_kickers.size()-1){
      winner.hands.push_back(first);
      winner.hands.push_back(second);
    }
  }
}

void rank_triplet(const Hand &first, const Hand &second, Winner &winner, map<string,int> m){
  int i=0;
  compare_two_hands_triplet(first,second,i,winner,m);
}

void rank_all_different_triplet(const Hand &first, const Hand &second, const Hand &third,
				int i, Winner &winner, map<string,int> m){
  auto k_f = get_triplet_kickers(first,i,m);
  auto k_s = get_triplet_kickers(second,i,m);
  auto k_t = get_triplet_kickers(third,i,m);

  auto maxkicker= max(k_f,k_s);
  maxkicker=max(maxkicker,k_t);

  if(maxkicker==k_f){
    winner.hands.push_back(first);
  }

  if(maxkicker==k_s){
    winner.hands.push_back(second);
  }

  if(maxkicker==k_t){
    winner.hands.push_back(third);
  }
}

void compare_three_hands_triplet(const Hand &first, const Hand &second, const Hand &third, int i,
				 Winner &winner, map<string,int> m){
  auto k_f = get_triplet_kickers(first,i,m);
  auto k_s = get_triplet_kickers(second,i,m);
  auto k_t = get_triplet_kickers(third,i,m);

  if((k_f==k_s)&&(k_s==k_t)){
    if(i<first.triplet_kickers.size()-1){
      compare_three_hands_triplet(first,second,third,i+1,winner,m);
    }

    if(i==first.triplet_kickers.size()-1){
	winner.hands.push_back(first);
	winner.hands.push_back(second);
	winner.hands.push_back(third);
      }
  }

  if((k_f!=k_s)&&(k_s!=k_t)){
    rank_all_different_triplet(first,second,third,i,winner,m);
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
    compare_two_hands_triplet(first,second,i,winner,m);
  }

  if((k_s==k_t)&&(k_t>k_f)){
    compare_two_hands_triplet(second,third,i,winner,m);
  }

  if((k_t==k_f)&&(k_f>k_s)){
    compare_two_hands_triplet(third,first,i,winner,m);
  }
}

void rank_triplet(const Hand &first, const Hand &second, const Hand &third, Winner &winner,
		  map <string,int>m){
  compare_three_hands_triplet(first,second,third,0,winner,m);
}
    
      
