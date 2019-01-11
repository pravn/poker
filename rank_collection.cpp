#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <map>
#include <typeinfo>
#include "data_container.h"
#include "deck_operations.h"
#include "check_cases.h"
#include "compare_hands.h"
using namespace std;


void build_map(map <string,int> &M){
  M["2"] = 1; //1
  M["3"] = 2; //2
  M["4"] = 3; //3
  M["5"] = 4; //4
  M["6"] = 5; //5
  M["7"] = 6; //6
  M["8"] = 7; //7
  M["9"] = 8; //8
  M["T"] = 9; //9
  M["J"] = 10; //10
  M["Q"] = 11; //11
  M["K"] = 12; //12 
  M["A"] = 13; //13
}


void build_reverse_map(map <int,string> &R){
  R[1] = "2";
  R[2] = "3";
  R[3] = "4";
  R[4] = "5";
  R[5] = "6";
  R[6] = "7";
  R[7] = "8";
  R[8] = "9";
  R[9] = "T";
  R[10]= "J";
  R[11]= "Q";
  R[12]= "K";
  R[13]= "A";
}
  
void build_score_map(map <Result,int> &score){
  score[Result::high_card]=1;
  score[Result::pair]=2;
  score[Result::two_pair]=3;
  score[Result::three_of_a_kind]=4;
  score[Result::straight]=5;
  score[Result::flush]=6;
  score[Result::full_house]=7;
  score[Result::four_of_a_kind]=8;
  score[Result::straight_flush]=9;
  score[Result::royal_flush]=10;
}


void rank_collection(Collection &c){
  map<string,int> M;
  map<int,string> R;
  map<Result,int> score_map;

  build_map(M);
  build_reverse_map(R);
  build_score_map(score_map);
  
  vector<Cards> Deck(13);

  check_cases(Deck, c, M, R);

  cout << "===============================" << endl;

  //now our collection contains states
  //we can rank them
  compare_hands(c,score_map,M,R);
  
  
}

