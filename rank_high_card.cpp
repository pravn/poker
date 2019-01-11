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
#include "rank_high_card.h"

using namespace std;


int get_high_card_kickers(const Hand &hand, int i, map<string,int> m){
  int kicker = m[string{hand.high_card_kickers[i]}];
  return kicker;
}


void compare_two_hands_high_card(const Hand &first, const Hand &second,int i, Winner &winner,
				 map<string,int> m){
  auto k_f = get_high_card_kickers(first,i,m);
  auto k_s = get_high_card_kickers(second,i,m);

  if(k_f>k_s){
    winner.hands.push_back(first);
  }

  if(k_f<k_s){
    winner.hands.push_back(second);
  }

  if(k_f==k_s){
    if(i<first.high_card_kickers.size()-1){
      compare_two_hands_high_card(first,second,i+1,winner,m);
	}
    if(i==first.high_card_kickers.size()-1){
      winner.hands.push_back(first);
      winner.hands.push_back(second);
    }
  }
  
}
  
void rank_high_card(const Hand &first, const Hand &second, Winner &winner, map<string,int>m){
  cout << "two " << endl;
  int i=0;
  compare_two_hands_high_card(first,second,i,winner,m);
  
}

void rank_all_different_high_cards(const Hand &first, const Hand &second, const Hand &third,
				   int i,Winner &winner,map<string,int> m){
  auto k_f = get_high_card_kickers(first,i,m);
  auto k_s = get_high_card_kickers(second,i,m);
  auto k_t = get_high_card_kickers(third,i,m);
  
  auto maxkicker = max(k_f,k_s);
  maxkicker = max(maxkicker,k_t);

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

void compare_three_hands_high_card(const Hand &first, const Hand &second, const Hand &third, int i,
				   Winner &winner,map<string,int> m){
  auto k_f = get_high_card_kickers(first,i,m);
  auto k_s = get_high_card_kickers(second,i,m);
  auto k_t = get_high_card_kickers(third,i,m);

  if((k_f==k_s)&&(k_s==k_t)){
    if(i<first.high_card_kickers.size()-1){
      compare_three_hands_high_card(first,second,third,i+1,winner,m);
    }

    if(i==first.high_card_kickers.size()-1){
      winner.hands.push_back(first);
      winner.hands.push_back(second);
      winner.hands.push_back(third);
    }
  }

  if((k_f!=k_s)&&(k_s!=k_t)){
    rank_all_different_high_cards(first,second,third,i,winner,m);
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
    compare_two_hands_high_card(first,second,i,winner,m);
  }

  if((k_s==k_t)&&(k_t>k_f)){
    compare_two_hands_high_card(second,third,i,winner,m);
  }

  if((k_t==k_f)&&(k_f>k_s)){
    compare_two_hands_high_card(third,first,i,winner,m);
  }
    
}

void rank_high_card(const Hand &first, const Hand &second, const Hand &third, Winner &winner,
		    map<string,int>m){
  compare_three_hands_high_card(first,second, third, 0,winner,m);
}
