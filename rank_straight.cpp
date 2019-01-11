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
#include "rank_straight.h"

using namespace std;
//no kickers - sigh!

void rank_straight(const Hand &first, const Hand &second, Winner &winner, map<string,int> m){
  //this is a tie
  //because state markers handle everything
  winner.hands.push_back(first);
  winner.hands.push_back(second);
}

void rank_straight(const Hand &first, const Hand &second, const Hand &third, Winner &winner, map<string,int> m){
  //also tie
  winner.hands.push_back(first);
  winner.hands.push_back(second);
  winner.hands.push_back(third);
}
