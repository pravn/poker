#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include "data_container.h"
#include <map>
#include <typeinfo>

using namespace std;
void update_deck(vector<Cards> &Deck, int i, string s,bool update){
  if(s == "C") Deck[i-1].Club = true;
  if(s == "D") Deck[i-1].Diamond  = true;
  if(s == "H") Deck[i-1].Heart = true;
  if(s == "S") Deck[i-1].Spade = true;
  Deck[i-1].is_hand_card=update;
  Deck[i-1].count++;
}

void print_deck_index(const vector<Cards> Deck, int index, map<string,int> m, map<int,string> r){
  if(Deck[index].Club==true)
    cout << r[index+1] << "C" << " " ;
  if(Deck[index].Diamond==true)
    cout << r[index+1] << "D" << " " ;
  if(Deck[index].Heart==true)
    cout << r[index+1] << "H" << " ";
  if(Deck[index].Spade==true)
    cout << r[index+1] << "S";

  cout << endl;
}

inline void print_line(){
  cout << "===============" << endl;
}

void print_state(Hand hand){
  switch(hand.result){
  case Result::royal_flush:
    cout << "Royal Flush!" << endl;
    print_line();
    break;
  case Result::straight_flush:
    cout << "Straight Flush!" << endl;
    cout << "State: " << hand.state_marker << endl;
    print_line();
    break;
  case Result::four_of_a_kind:
    cout << "Four of a kind!" << endl;
    cout << "State: " << hand.state_marker << endl;
    print_line();
    break;
  case Result::full_house:
    cout <<"Full house!" << endl;
    cout <<"State: " << hand.state_marker << endl;
    print_line();
    break;
  case Result::flush:
    cout << "Flush!" << endl;
    cout << "State: " << hand.state_marker << endl;
    print_line();
    break;
  case Result::straight:
    cout << "Straight!" << endl;
    cout << "State: " << hand.state_marker << endl;
    print_line();
    break;
  case Result::three_of_a_kind:
    cout << "Three of a kind!" << endl;
    cout << "State: " << hand.state_marker << endl;
    print_line();
    break;
  case Result::two_pair:
    cout << "Two pair!" << endl;
    cout << "State: " << hand.state_marker << endl;
    print_line();
    break;
  case Result::pair:
    cout << "Pair!" << endl;
    cout << "State: " << hand.state_marker << endl;
    print_line();
    break;
  case Result::high_card:
    cout << "High card!" << endl;
    print_line();
    break;
  
}
}

void add_board_to_deck(vector<Cards> &Deck,Collection &c, map<string,int> &m){
  //first add board
  auto b = c.board.board;

  for (int i=0; i<b.size(); i++){
    string s{b[i][0]};
    string q{b[i][1]};
    //    cout << "sms " << s << " " <<  m[s] << endl;
    auto j = m[s];
    update_deck(Deck, j,  q,false);
  }

}

void add_hand_to_deck(vector<Cards> &Deck, Hand &hand, map<string,int> &m){

  for (int i=0; i<hand.hand.size(); i++){
    string s{hand.hand[i][0]};
    string q{hand.hand[i][1]};

    auto j = m[s];
    update_deck(Deck, j, q,true);

  } 
  
}

vector<string> append(vector<string> hand, vector<string> board){
  vector <string> appended;

  appended.insert(appended.end(), hand.begin(), hand.end());
  appended.insert(appended.end(), board.begin(), board.end());

  return appended;
}

struct compare{

  mutable map <string,int> _m;
  compare(map<string,int> m): _m(m){}

  bool operator()(const string &a, const string &b) const {
    string _a{a[0]};
    string _b{b[0]};
    return _m[_a] < _m[_b];
  }
};
		     

void sort_cards(vector<string> &cards,const map<string,int> m){
  auto c = compare(m);
  sort(cards.begin(), cards.end(), c);
}

vector<string> rmdup(vector<string> cards, map<string,int> m){
  vector<string> rm_dup;
  rm_dup.push_back(string{cards[0][0]});
  
  //remove duplicates
  string previous{cards[0][0]};
  
  for(int i=1; i<cards.size(); i++){
    string current{cards[i][0]};
    string previous{cards[i-1][0]};
    
    if(m[current]!=m[previous]){
      rm_dup.push_back(string{cards[i][0]});
    }
  }

  return rm_dup;

}


deque <bool> check_straight( vector <string> cards, int sizediff, map<string,int> m){

  deque<bool> straight;

  for (int i=0; i<3-sizediff; i++){
    int count=0;
    bool flag=true;
    for(auto j=i+1; j<=i+4;j++){
      string current{cards[j][0]};
      string previous{cards[j-1][0]};

      if((m[current]-m[previous])!=1){
	flag*=false;
      }
    }
    straight.push_back(flag);
  }

  //consider the low straight case
  //A2345

  
  return straight;
      
}


bool check_straight_flush(vector<string> cards, map<string,int> m){
  bool straight;
  
  for (int i=0; i<1; i++){
    bool flag=true;
    for(auto j=i+1; j<=i+4;j++){
      string current{cards[j][0]};
      string previous{cards[j-1][0]};
      
      if((m[current]-m[previous])!=1){
	flag *= false;
      }
    }

    straight = flag;
  }

  //consider the low straight case
  //A2345

  
  return straight;
}

bool find_hand_card(vector<string> hand, vector<string> cards){

  auto first = find(cards.begin(), cards.end(), hand[0]);
  auto second = find(cards.begin(), cards.end(), hand[1]);

  if((first!=cards.end())||(second!=cards.end())){
    return true;
  }
  else{
    return false;
  }
}

