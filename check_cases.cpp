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

using namespace std;

enum class flush_type{
  plain_flush,
    straight_flush,
    royal_flush};

void print_flush_cards(int i, const vector<string> cards, flush_type f){

  if(f==flush_type::plain_flush)
    cout << "Flush " << endl;

  if(f==flush_type::straight_flush)
    cout << "Straight Flush " << endl;

  if(f==flush_type::royal_flush)
    cout << "Royal Flush " << endl;
  
  for(auto c:cards){
    cout <<" " <<  c;
  }
  cout << endl;
}	   

void print_deck(vector<Cards> &deck){
  for(int i=0; i<deck.size(); i++){
    deck[i].print();
  }
}

vector<int> count_pairs(vector<Cards> deck){
  vector<int> pair_index(2,0);
  vector<int> index;
  
  int count=0;
  for(int i=0; i<deck.size(); i++){
    if((deck[i].count==2))
      index.push_back(i);
  }

  if(index.size()>=2){
    pair_index[1]=index[index.size()-1];
    pair_index[0]=index[index.size()-2];
  }

  if(index.size()==1)
    pair_index[0]=index[0];
  
  return pair_index;
}

int count_triplets(vector<Cards> deck){
  int triplet_index{0};

  for(int i=0; i<deck.size(); i++){
    if(deck[i].count==3){
      triplet_index=i;
    }
  }

  return triplet_index;
}
  
vector<int> count_triplet_kickers(vector<Cards> deck){
  vector<int> indices;
  for (int i=0; i<deck.size(); i++){
    if(deck[i].count!=3){
      indices.push_back(i);
    }
  }

  sort(indices.begin(),indices.end(),greater<int>());

  vector<int> kickers;
  kickers.push_back(indices[0]);
  kickers.push_back(indices[1]);

  return kickers;
}
  
int count_quad_kicker(vector<Cards>deck){
  vector<int>indices;
  
  for(int i=0; i<deck.size(); i++){
    if((deck[i].count!=4)&&(deck[i].count>0)){
      indices.push_back(i);
    }
  }

  sort(indices.begin(),indices.end(),greater<int>());

  return indices[0];
}
      


int count_kicker_two_pair(vector<Cards> deck){
  vector<int>indices;
  
  for(int i=0; i<deck.size(); i++){
    if(deck[i].count==1){
      indices.push_back(i);
    }
  }

  sort(indices.begin(), indices.end(),greater<int>());

  return indices[0]; //probably the zero'th index - check later
}

vector<int> count_kicker_pair(vector<Cards> deck){
  vector<int>indices;

  for(int i=0; i<deck.size(); i++){
    if(deck[i].count==1){
      indices.push_back(i);
    }
  }

  sort(indices.begin(), indices.end(),greater<int>());

  vector<int>kickers;

  kickers.push_back(indices[0]);
  kickers.push_back(indices[1]);
  kickers.push_back(indices[2]);
    
  return kickers;
}


int count_quads(vector<Cards> deck){
  int quad_index=0;

  for(int i=0; i<deck.size(); i++){
    if(deck[i].count==4){
      quad_index=i;
    }
  }

  return quad_index;
}

bool handle_flush_type(int i, Hand &hand, vector<string> flush_cards, map<string,int> m, flush_type f){
  if(f==flush_type::royal_flush){
    //handle this as an individual case
    if((flush_cards[0][0]=='T')&&
       (flush_cards[1][0]=='J')&&
       (flush_cards[2][0]=='Q')&&
       (flush_cards[3][0]=='K')&&
       (flush_cards[4][0]=='A')){

      hand.result=Result::royal_flush;
      hand.state_marker = "A";
      return true;
    }
  }
  
  if(f==flush_type::plain_flush){

    hand.result=Result::flush;
    hand.state_marker=string{flush_cards[flush_cards.size()-1][0]};

    //clunky, but we push sorted cards to rank later
    hand.spare_flushes.push_back(string{flush_cards[flush_cards.size()-2][0]});
    hand.spare_flushes.push_back(string{flush_cards[flush_cards.size()-3][0]});
    hand.spare_flushes.push_back(string{flush_cards[flush_cards.size()-4][0]});
    hand.spare_flushes.push_back(string{flush_cards[flush_cards.size()-5][0]});
    return true;
  }

  if(f==flush_type::straight_flush){
      if(check_straight_flush(flush_cards,m)) {

	hand.result=Result::straight_flush;
	hand.state_marker=string{flush_cards[flush_cards.size()-1][0]};
	return true;
      }
  }
  
  return false;
}

bool is_pair(vector<Cards> &d, Hand &hand, map<string,int> &m, map<int,string> &r){

  auto pair_index = count_pairs(d);

  bool pair = false;
  if((pair_index[0]!=0)&&(pair_index[1]==0))
    pair = true;

  if(pair){
    hand.result = Result::pair;
    hand.state_marker = r[pair_index[0]+1];

    auto int_kickers = count_kicker_pair(d);
    auto first_kicker = r[int_kickers[0]+1];
    auto second_kicker = r[int_kickers[1]+1];
    auto third_kicker = r[int_kickers[2]+1];

    hand.pair_kickers.push_back(first_kicker);
    hand.pair_kickers.push_back(second_kicker);
    hand.pair_kickers.push_back(third_kicker);

    return true;
  }else{
    return false;
  }
}


bool is_two_pair(vector<Cards> &d, Hand &hand, map<string,int> &m, map<int,string> &r){

  auto pair_index = count_pairs(d);

  bool two_pair = false;
  if((pair_index[0]!=0)&&(pair_index[1]!=0))
    two_pair = true;

  if(two_pair==true){
    hand.result = Result::two_pair;

    //mark both pair entries
    ostringstream oss;
    oss << r[pair_index[0]+1] << r[pair_index[1]+1];
    hand.state_marker = oss.str();

    auto int_kicker = count_kicker_two_pair(d);
    auto kicker = r[int_kicker+1];
    hand.two_pair_kicker=kicker ;
    return true;
  }else{
    return false;
  }
}
    
    

bool is_three_of_a_kind(vector<Cards> &d, Hand &hand, map<string,int> &m, map<int,string> &r){

  auto triplet_index = count_triplets(d);

  if(triplet_index){
    auto int_kickers = count_triplet_kickers(d);
    hand.triplet_kickers[0] = r[int_kickers[0]+1];
    hand.triplet_kickers[1] = r[int_kickers[1]+1];
    
    hand.result = Result::three_of_a_kind;
    hand.state_marker = r[triplet_index+1];
    //hand.print_kickers();
    return true;
  }
  else
    return false;
}


bool is_full_house(vector<Cards> &d, Hand &hand, map<string,int> &m, map<int,string> &r){
  auto triplet_index = count_triplets(d);
  auto pair_index = count_pairs(d);

    bool pair = false;


    if((pair_index[0]!=0)&&(pair_index[1]==0))
      pair = true;

    if((pair)&&(triplet_index)){
      hand.result=Result::full_house;
      auto triplet_marker = r[triplet_index+1];
      auto pair_marker = r[pair_index[0]+1];

      ostringstream oss;
      oss << triplet_marker << pair_marker;

      //clunky - but we keep both triplet and pair markers
      hand.state_marker = oss.str();
      return true;
    }
 
    return false;
}





bool is_four_of_a_kind(vector<Cards> &d, Hand &hand, map<string,int> &m, map<int,string> &r){

    auto quad_index = count_quads(d);

    if(quad_index){
      hand.result=Result::four_of_a_kind;
      hand.state_marker=r[quad_index+1];
      auto kicker = count_quad_kicker(d);
      hand.quad_kicker = r[kicker+1];
      return true;
    }
    else
      return false;
}



//five cards in sequential value
bool is_straight(Collection &coll, int i, map <string,int> &m){

  auto hands = coll.hands;
  auto board = coll.board.board;

  auto cards_orig = append(hands[i].hand,board);

  sort_cards(cards_orig,m);
  auto cards = rmdup(cards_orig,m);

  auto sizediff = cards_orig.size()-cards.size();

  auto straight = check_straight(cards,sizediff,m);

  //if we find a straight then return
  //any straight that we find based on this sorting scheme
  //2345...A (A is highest) will miss the low straight case
  //and is higher than the low straight case
  for(int k=0; k<3-sizediff; k++){
    vector<string> c(cards.begin()+k,cards.begin()+k+5);
    if(straight[k]==1){
      coll.hands[i].result = Result::straight;
      coll.hands[i].state_marker = cards[k+4][0];
      return true;
    }
  }

  //low straight case
  //A2345 => 2345..A in our sorting scheme (A is highest)
  if((cards[0][0]=='2')&&
     (cards[1][0]=='3')&&
     (cards[2][0]=='4')&&
     (cards[3][0]=='5')&&
     (cards[6][0]=='A')){

    coll.hands[i].result = Result::straight;
    coll.hands[i].state_marker = "5";
    return true;
  }
  return false;
}

bool is_flush(Collection &coll, int i, map<string,int> m, flush_type f){
  //five cards of the same suit
  auto hands = coll.hands;
  auto board = coll.board.board;

  //  for (int i=0; i<hands.size(); i++){
  auto cards = append(hands[i].hand,board);

  sort(cards.begin(), cards.end(), [](const string &a, const string &b){
      string _a{a[1]};
      string _b{b[1]};
      return _a < _b;
    });

  vector<int> entries(4,0); //fill flush entries with 0

  for_each(cards.begin(), cards.end(),
	   [&entries](string card){
	     if(card[1]=='C')
	       entries[0]++;
	     if(card[1]=='H')
	       entries[1]++;
	     if(card[1]=='D')
	       entries[2]++;
	     if(card[1]=='S')
	       entries[3]++;
	   });

  //check if entries are >=5
  int previous_entry=0;
  for(int j=0; j<4;j++){
    if(entries[j]>=5){
      vector<string> c(cards.begin()+previous_entry,cards.begin()+previous_entry+entries[j]);
      sort_cards(c,m);
      auto start = c.size()-5;
      vector<string> flush_cards(c.begin()+start,c.end());
      return handle_flush_type(i,coll.hands[i],flush_cards,m,f);
    }
    previous_entry += entries[j]; //important bug fix - previously the '+' was missing 
  }

  return false;

}

bool is_high_card(Collection &coll, int i, map<string,int> &m){
  //sort cards
  auto hands = coll.hands;
  auto board = coll.board.board;

  auto cards = append(hands[i].hand,board);
  sort_cards(cards,m);

  coll.hands[i].result = Result::high_card;
  coll.hands[i].state_marker = cards[cards.size()-1][0];

  coll.hands[i].high_card_kickers.push_back(string{cards[cards.size()-1][0]});
  coll.hands[i].high_card_kickers.push_back(string{cards[cards.size()-2][0]});
  coll.hands[i].high_card_kickers.push_back(string{cards[cards.size()-3][0]});
  coll.hands[i].high_card_kickers.push_back(string{cards[cards.size()-4][0]});
  coll.hands[i].high_card_kickers.push_back(string{cards[cards.size()-5][0]});

  return true;

}
  

void check_cases(vector<Cards> &Deck, Collection &c, map<string,int> &m, map <int,string> &r){
  add_board_to_deck(Deck,c,m);
  vector<vector<Cards>> d(c.hands.size());

  for(int i=0; i<c.hands.size(); i++){
    d[i] = Deck;
  }


  for(int i=0; i<c.hands.size(); i++){
    add_hand_to_deck(d[i], c.hands[i],m);
    if(is_flush(c,i,m,flush_type::royal_flush)){
      continue;
    }
   
    if(is_flush(c,i,m,flush_type::straight_flush)){
      continue;
    }
    
    if(is_four_of_a_kind(d[i],c.hands[i],m,r)){
      continue;
      }

    if(is_full_house(d[i],c.hands[i],m,r)){
      continue;
    }

    if(is_flush(c,i,m,flush_type::plain_flush)){
      continue;
    }

    if(is_straight(c,i,m)){
      continue;
    }

    if(is_three_of_a_kind(d[i],c.hands[i],m,r)){
      continue;
    }
    
    if(is_two_pair(d[i],c.hands[i],m,r)){
      continue;
    }

    if(is_pair(d[i],c.hands[i],m,r)){
      continue;
    }
    
    //if it gets to this line, it is a high card
    if(is_high_card(c,i,m)){
      continue;
    }
    

  }

}
    
