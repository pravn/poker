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
#include "rank_royal_flush.h"

using namespace std;

void rank_royal_flush(const Hand &first, const Hand &second, Winner &winner,
		      map<string,int> m){
  winner.hands.push_back(first);
  winner.hands.push_back(second);
}

void rank_royal_flush(const Hand &first, const Hand &second, const Hand &third,
		      Winner &winner, map<int,string> m){
  winner.hands.push_back(first);
  winner.hands.push_back(second);
  winner.hands.push_back(third);
}
