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
#include "rank_straight_flush.h"
#include "rank_straight.h"
#include "rank_flush.h"
#include "rank_triplet.h"
#include "rank_pair.h"
#include "rank_high_card.h"


using namespace std;

void set_hand_score(Hand &hand, map<Result,int> score_map){
  hand.score = score_map[hand.result];
}

void print_result_attributes(Hand hand){
  switch(hand.result){
  case Result::royal_flush:
    cout << "Result: Royal Flush! " << endl;
    break;

  case Result::straight_flush:
    cout << "Result: Straight Flush " << endl;
    cout << "High: " << hand.state_marker << endl;
    break;

  case Result::four_of_a_kind:
    cout << "Result: Four of a kind " << endl;
    cout << "High: " << hand.state_marker << endl;
    cout << "Kicker: " << hand.quad_kicker << endl;
    break;
	       
  case Result::full_house:
    cout << "Result:Full house " << endl;
    cout << "High: " <<  hand.state_marker << endl;
    break;

  case Result::flush:
    cout << "Result: Flush " << endl;
    cout << "High: " << hand.state_marker << endl;
    cout << "Lower flushes: ";
    for (auto a: hand.spare_flushes){
      cout << a << " " ;
    }
    cout << endl;
    break;

  case Result::straight:
    cout << "Result: Straight " << endl;
    cout << "High: " << hand.state_marker << endl;
    break;

  case Result::three_of_a_kind:
    cout << "Result: Three of a kind " << endl;
    cout << "High: " << hand.state_marker << endl;
    cout << "Kickers: ";

    for(auto a:hand.triplet_kickers){
      cout << a << " ";
    }
    cout << endl;
    break;

  case Result::two_pair:
    cout << "Result: Two pair " << endl;
    cout << "High: " << hand.state_marker << endl;
    cout << "Kicker: ";
    cout << hand.two_pair_kicker;
    cout << endl;
    break;

  case Result::pair:
    cout << "Result: Pair " << endl;
    cout << "High: " << hand.state_marker << endl;
    cout << "Kickers: ";

    for (auto a:hand.pair_kickers){
      cout << a << " ";
    }
    cout << endl;
    break;

  case Result::high_card:
    cout << "Result: High card " << endl;
    cout << "High: " << hand.state_marker << endl;
    cout << "Kickers: ";

    for (auto a:hand.high_card_kickers){
      cout << a << " ";
    }
    cout << endl;
    break;
  }
}
  

void print_hand_score(Hand hand){
  cout << "Hand name: " << hand.name << endl;
  print_result_attributes(hand);
  cout << "Score: " << hand.score << endl;
  cout << "=============================="<< endl;
}


void print_winner_attributes(const Winner &winner){
  cout << "Winning hands " << endl;
  for_each(winner.hands.begin(),winner.hands.end(),
	   [] (Hand hand){
	     cout << "Hand name: " << hand.name << endl;
	     print_result_attributes(hand);});
}
	     

struct value_compare{
  map<string,int> m;
  value_compare(map<string,int> _m):m{_m}{}

  bool operator()(string s1, string s2){
    string _one{s1[0]};
    string _two{s2[0]};
    return m[_one]<m[_two];
  }
};



bool all_different(int s1, int s2, int s3){
  if((s1!=s2)&&(s2!=s3))
    return true;
  else
    return false;
}

bool compare_two_hands(const Hand &hand1, const Hand &hand2,Winner &winner, int k1, int k2){
  if(k1>k2){
    winner.hands.push_back(hand1);
  }

  if(k1<k2){
    winner.hands.push_back(hand2);
  }

  if(k1==k2){
    winner.hands.push_back(hand1);
    winner.hands.push_back(hand2);
  }
}
  

void compare_two_hands_quad(Hand &first, Hand &second, Winner &winner, map<string,int> m){
  auto k_f = first.quad_kicker;
  auto k_s = second.quad_kicker;

  if(k_f>k_s){
    winner.hands.push_back(first);
  }

  if(k_f<k_s){
    winner.hands.push_back(second);
  }

  if(k_f==k_s){
    winner.hands.push_back(first);
    winner.hands.push_back(second);
  }
}

void rank_all_different(Winner &winner, Hand &first,Hand &second,Hand &third, int k1, int k2, int k3){
  if(all_different(k1,k2,k3)){
    auto maxstate = max(k1,k2);
    maxstate = max(maxstate,k3);

    if(maxstate==k1){
      winner.hands.push_back(first);
    }

    if(maxstate==k2){
      winner.hands.push_back(second);
    }

    if(maxstate==k3){
      winner.hands.push_back(third);
    }
  }
}

void rank_all_different(Winner &winner, Hand &first, Hand &second, int k1, int k2){
  auto maxstate=max(k1,k2);
  
  if(k1!=k2){
    if(maxstate==k1){
      winner.hands.push_back(first);
    }

    if(maxstate==k2){
      winner.hands.push_back(second);
    }

  }
}

  
void rank_four_of_a_kind(Hand &hand1, Hand &hand2, Winner &winner, map<string,int>m){
  auto s1 = m[hand1.state_marker];
  auto s2 = m[hand2.state_marker];

  auto k_1 = m[string{hand1.quad_kicker}];
  auto k_2 = m[string{hand2.quad_kicker}];

  rank_all_different(winner,hand1,hand2,s1,s2);

  if(s1==s2){
    rank_all_different(winner,hand1,hand2,k_1,k_2);

    if(k_1==k_2){
      winner.hands.push_back(hand1);
      winner.hands.push_back(hand2);
    }
  }
}



  
  

void rank_four_of_a_kind(Hand &hand1, Hand &hand2, Hand &hand3, Winner &winner, map<string,int>m){
  auto s1 = m[hand1.state_marker];
  auto s2 = m[hand2.state_marker];
  auto s3 = m[hand3.state_marker];

  auto k_1 = m[string{hand1.quad_kicker}];
  auto k_2 = m[string{hand2.quad_kicker}];
  auto k_3 = m[string{hand3.quad_kicker}];

  auto maxstate = max(s1,s2);
  maxstate=max(maxstate,s3);

  if(all_different(s1,s2,s3)){
    if(maxstate==s1){
      winner.hands.push_back(hand1);
    }

    if(maxstate==s2){
      winner.hands.push_back(hand2);
    }

    if(maxstate==s3){
      winner.hands.push_back(hand3);
    }
  }

  if((s1==s2)&&(s2>s3)){
    compare_two_hands_quad(hand1,hand2,winner,m);
  }

  if((s1==s2)&&(s2<s3)){
    winner.hands.push_back(hand3);
  }

  if((s2==s3)&&(s3>s1)){
    compare_two_hands_quad(hand2,hand3,winner,m);
  }

  if((s2==s3)&&(s3<s1)){
    winner.hands.push_back(hand1);
  }

  if((s3==s1)&&(s1>s2)){
    compare_two_hands_quad(hand3,hand1,winner,m);
  }

  if((s3==s1)&&(s1<s2)){
    winner.hands.push_back(hand2);
  }

  if((s1==s2)&&(s2==s3)){
    rank_all_different(winner,hand1,hand2,hand3,k_1, k_2, k_3);

    if((k_1==k_2)&&(k_2>k_3)){
      winner.hands.push_back(hand1);
      winner.hands.push_back(hand2);
    }

    if((k_1==k_2)&&(k_2==k_3)){
      winner.hands.push_back(hand3);
    }

    if((k_2==k_3)&&(k_3>k_1)){
      winner.hands.push_back(hand2);
      winner.hands.push_back(hand3);
    }

    if((k_2==k_3)&&(k_3<k_1)){
      winner.hands.push_back(hand1);
    }

    if((k_3==k_1)&&(k_1>k_2)){
      winner.hands.push_back(hand3);
      winner.hands.push_back(hand1);
    }

    if((k_3==k_1)&&(k_1<k_2)){
      winner.hands.push_back(hand2);
    }

    if((k_3==k_1)&&(k_1==k_2)){
      winner.hands.push_back(hand1);
      winner.hands.push_back(hand2);
      winner.hands.push_back(hand3);
    }
  }
} //rank_four_of_a_kind


//two way tie
void rank_full_house(Hand &hand1, Hand &hand2, Winner &winner, map<string,int> m){
  //I figured out the recursion much later ...
  //all these lines have the same idea though
  //its simple enough in the full house case
  //get triplet markers
  string t1{hand1.state_marker[0]};
  string t2{hand2.state_marker[0]};

  string p1{hand1.state_marker[1]};
  string p2{hand2.state_marker[1]};

  if(m[t1]>m[t2]){
    winner.hands.push_back(hand1);
  }

  if(m[t2]>m[t1]){
    winner.hands.push_back(hand2);
  }

  if(t1==t2){
    if(m[p1]>m[p2]){
      winner.hands.push_back(hand1);
    }
    
    if(m[p2]>m[p1]){
      winner.hands.push_back(hand2);
    }
      
    if(m[p1]==m[p2]){
      cout << "Split Pot! " << hand1.name << " " << hand2.name << endl;
      winner.hands.push_back(hand1);
      winner.hands.push_back(hand2);
    }
  }

}

bool is_equal_three(int t1, int t2, int t3){
  if((t1==t2)&&(t1==t3))
    return true;
  else
    return false;
}

void rank_full_house(Hand &hand1, Hand &hand2, Hand &hand3, Winner &winner, map<string,int> m){
  string t1{hand1.state_marker[0]};
  string t2{hand2.state_marker[0]};
  string t3{hand3.state_marker[0]};

  string p1{hand1.state_marker[1]};
  string p2{hand2.state_marker[1]};
  string p3{hand3.state_marker[1]};

  //three ties
  if(is_equal_three(m[t1],m[t2],m[t3])){
    auto maxp = max(m[p1], m[p2]);
    maxp = max(maxp, m[p3]);

    if(all_different(m[p1],m[p2],m[p3])){
      if(maxp==m[p1]){
	winner.hands.push_back(hand1);
      }
      
      if(maxp==m[p2]){
	winner.hands.push_back(hand2);
      }

      if(maxp==m[p3]){
	winner.hands.push_back(hand3);
      }
    }


    if((p1==p2)&&(maxp==m[p1])){
      //split pot
      cout << "Split pot " << hand1.name << " " << hand1.name << endl;
      winner.hands.push_back(hand1);
      winner.hands.push_back(hand2);
    }
    
    if((p1==p2)&&(maxp==m[p3])){
      winner.hands.push_back(hand3);
    }

    if((p1==p3)&&(maxp==m[p2])){
      winner.hands.push_back(hand2);
    }

    if((p2==p3)&&(maxp==m[p2])){
      cout << "Split pot " << hand2.name << " " << hand3.name << endl;
      winner.hands.push_back(hand2);
      winner.hands.push_back(hand3);
    }

    if((p2==p3)&&(maxp==m[p1])){
      winner.hands.push_back(hand1);
    }

    if((p1==p3)&&(maxp==m[p1])){
      cout << "Split pot " << hand1.name << " " << hand3.name << endl;
      winner.hands.push_back(hand1);
    }

    if((p1==p2)&&(p1==p3)){
      cout << "Split pot " << hand1.name << " " << hand2.name << " " << hand3.name << endl;
      winner.hands.push_back(hand1);
      winner.hands.push_back(hand2);
      winner.hands.push_back(hand3);
    }
  } //is_equal_three

}


void rank_two_pair(const Hand &first, const Hand &second, const Hand &third, Winner &winner, map<string,int> m){
  auto f_0 = m[string{first.state_marker[0]}];
  auto f_1 = m[string{first.state_marker[1]}];
  auto s_0 = m[string{second.state_marker[0]}];
  auto s_1 = m[string{second.state_marker[1]}];
  auto t_0 = m[string{third.state_marker[0]}];
  auto t_1 = m[string{third.state_marker[1]}];

  cout << "first.string marker " << first.state_marker << endl;
  cout << "second.string marker " << second.state_marker << endl;
  cout << "third.string_marker " << third.state_marker << endl;

  if(all_different(f_0, s_0, t_0)){
    int maxfirst = max(f_0,s_0);
    maxfirst = max(maxfirst,t_0);

    if(maxfirst==f_0){
      winner.hands.push_back(first);
    }

    if(maxfirst==s_0){
      winner.hands.push_back(second);
    }

    if(maxfirst==t_0){
      winner.hands.push_back(third);
    }
  }

  //six painful cases now
  //first, second
  if((f_0==s_0)&&(s_0>t_0)){
    if(f_1>s_1){
      winner.hands.push_back(first);
    }

    if(f_1<s_1){
      winner.hands.push_back(second);
    }

    if(f_1==s_1){
      auto k_f = m[string{first.two_pair_kicker}];
      auto k_s = m[string{second.two_pair_kicker}];

      compare_two_hands(first,second,winner,k_f,k_s);
    }
  }

  if((f_0==s_0)&&(s_0<t_0)){
    winner.hands.push_back(third);
  }

  //second, third
  if((s_0==t_0)&&(t_0>f_0)){
    if(s_1>t_1){
      winner.hands.push_back(second);
    }

    if(s_1<t_1){
      winner.hands.push_back(third);
    }

    if(s_1==t_1){
      auto k_s =m[string{second.two_pair_kicker}];
      auto k_t = m[string{third.two_pair_kicker}];

      compare_two_hands(second,third, winner, k_s, k_t);
    }
  }

  if((s_0==t_0)&&(t_0<f_0)){
    winner.hands.push_back(first);
  }

  //third, first
  if((t_0==f_0)&&(f_0>s_0)){
    if(t_1>f_1){
      winner.hands.push_back(third);
    }

    if(t_1<f_1){
      winner.hands.push_back(first);
    }

    if(t_1==f_1){
      auto k_t = m[string{third.two_pair_kicker}];
      auto k_f = m[string{first.two_pair_kicker}];

      compare_two_hands(third,first,winner,k_t,k_f);
    }
  }

  if((t_0==f_0)&&(f_0<s_0)){
    winner.hands.push_back(second);
  }

  //most painful case first=second=third
  if((f_0==s_0)&&(s_0==t_0)){
    if(all_different(f_1,s_1,t_1)){
      auto maxint = max(f_1,s_1);
      maxint = max(maxint,t_1);

      if(maxint==f_1){
	winner.hands.push_back(first);
      }

      if(maxint==s_1){
	winner.hands.push_back(second);
      }

      if(maxint==t_1){
	winner.hands.push_back(third);
      }

    }

    if((f_1==s_1)&&(s_1>t_1)){
      auto k_f = m[string{first.two_pair_kicker}];
      auto k_s = m[string{second.two_pair_kicker}];
      compare_two_hands(first,second,winner,k_f,k_s);
    }

    if((f_1==s_1)&&(s_1<t_1)){
      winner.hands.push_back(third);
    }

    //second, third
    if((s_1==t_1)&&(t_1>f_1)){
      auto k_s = m[string{second.two_pair_kicker}];
      auto k_t = m[string{third.two_pair_kicker}];
      compare_two_hands(second,third,winner,k_s,k_t);
    }

    if((s_1==t_1)&&(t_1<f_1)){
      winner.hands.push_back(first);
    }

    //third,first

    if((t_1==f_1)&&(f_1>s_1)){
      auto k_t = m[string{third.two_pair_kicker}];
      auto k_f = m[string{first.two_pair_kicker}];
      compare_two_hands(third,first,winner,k_t,k_f);
    }

    if((t_1==f_1)&&(f_1<s_1)){
      winner.hands.push_back(second);
    }

    if((f_1==s_1)&&(s_1==t_1)){
      auto k_f = m[string{first.two_pair_kicker}];
      auto k_s = m[string{second.two_pair_kicker}];
      auto k_t = m[string{third.two_pair_kicker}];

      if(all_different(k_f,k_s,k_t)){
	auto maxkicker = max(k_f,k_s);
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

      if((k_f==k_s)&&(k_s>k_t)){
	winner.hands.push_back(first);
	winner.hands.push_back(second);
      }

      if((k_f==k_s)&&(k_s<k_t)){
	winner.hands.push_back(third);
      }

      if((k_s==k_t)&&(k_t>k_f)){
	winner.hands.push_back(second);
	winner.hands.push_back(third);
      }

      if((k_s==k_t)&&(k_t<k_f)){
	winner.hands.push_back(first);
      }

      if((k_t==k_f)&&(k_f>k_s)){
	winner.hands.push_back(third);
	winner.hands.push_back(first);
      }

      if((k_t==k_f)&&(k_f<k_s)){
	winner.hands.push_back(second);
      }

      if((k_f==k_s)&&(k_s==k_t)){
	winner.hands.push_back(first);
	winner.hands.push_back(second);
	winner.hands.push_back(third);
      }
    
    }//f_1==s_1 && s_1 == t_1
      
  }//f_0==s_0 && s_0 == t_0

}


void rank_two_pair(const Hand &first, const Hand &second, Winner &winner,map<string,int>m){
  //read off first and second chars of state markers
  auto f_0 = m[string{first.state_marker[0]}];
  auto f_1 = m[string{first.state_marker[1]}];
  auto s_0 = m[string{second.state_marker[0]}];
  auto s_1 = m[string{second.state_marker[1]}];

  //compare first state marker (higher pair)
  if(f_0>s_0){
    winner.hands.push_back(first);
  }

  if(s_0>f_0){
    winner.hands.push_back(second);
  }

  //compare second state marker (lower pair)
  if(f_0==s_0){
    if(f_1>s_1){
      winner.hands.push_back(first);
    }

    if(s_1>f_1){
      winner.hands.push_back(second);
    }

    //now compare kicker
    if(f_1==s_1){
      auto k_f = first.two_pair_kicker;
      auto k_s = second.two_pair_kicker;

      if(k_f>k_s){
	winner.hands.push_back(first);
      }

      if(k_s>k_f){
	winner.hands.push_back(second);
      }

      if(k_f==k_s){
	//tie 
	winner.hands.push_back(first);
	winner.hands.push_back(second);
      }
    }
  }

}


  

void rank_threeway_ties(Hand &first, Hand &second, Hand &third, Winner &winner, map<string,int>m){
  auto result = first.result;

  switch(result){
  case Result::royal_flush:
    winner.hands.push_back(first);
    winner.hands.push_back(second);
    winner.hands.push_back(third);
    break;
    
  case Result::straight_flush:
      rank_straight_flush(first,second,third,winner,m);
      break;

  case Result::four_of_a_kind:
    rank_four_of_a_kind(first,second,third,winner,m);
    break;

  case Result::full_house:
    rank_full_house(first,second,third,winner,m);
    break;

  case Result::flush:
    rank_flush(first,second,third,winner,m);
    break;

  case Result::straight:
    rank_straight(first,second,third,winner,m);
    break;

  case Result::three_of_a_kind:
    rank_triplet(first,second,third,winner,m);
    break;
    
  case Result::two_pair:
    rank_two_pair(first,second,third,winner,m);
    break;

  case Result::pair:
    rank_pair(first,second,third,winner,m);
    break;

  case Result::high_card:
    rank_high_card(first,second,third,winner,m);
    break;
    
  }
}

void rank_twoway_ties(Hand &first, Hand &second, Winner &winner, map<string,int> m){
  auto result = first.result;

  switch(result){
  case Result::royal_flush:
    rank_royal_flush(first,second,winner,m);
    break;

  case Result::straight_flush:
    rank_straight_flush(first,second,winner,m);
    break;

  case Result::four_of_a_kind:
    rank_four_of_a_kind(first,second,winner,m);
    break;

  case Result::full_house:
    rank_full_house(first,second,winner,m);
    break;

  case Result::flush:
    rank_flush(first,second,winner,m);
    break;

  case Result::straight:
    rank_straight(first,second,winner,m);
    break;

  case Result::three_of_a_kind:
    rank_triplet(first,second,winner,m);
    break;

  case Result::two_pair:
    rank_two_pair(first,second,winner,m);
    break;

  case Result::pair:
    cout << "ranking pair " << endl;
    rank_pair(first,second,winner,m);
    break;

  case Result::high_card:
    rank_high_card(first,second,winner,m);
    break;
 }
}
    
    
  


void handle_scores(Collection &c, Winner &winner, map<string,int>m){
  //compare 1,2
  auto first = c.hands[0].score;
  auto second = c.hands[1].score;
  auto third = c.hands[2].score;


  //sorted order - unique (easy) case
  if((first>second)&&(second>third)){
    winner.hands.push_back(c.hands[0]);
  }

  if((first>second)&&(second==third)){
    winner.hands.push_back(c.hands[0]);
  }

  if((first>second)&&(second==third))
    winner.hands.push_back(c.hands[0]);
  
  if((first==second)&&(second>third)){ //twoway tie
    cout << "Doing two way ties " << endl;
    rank_twoway_ties(c.hands[0],c.hands[1], winner, m);
  }

  if((first==second)&&(second==third)){ //threeway tie
    rank_threeway_ties(c.hands[0],c.hands[1],c.hands[2], winner, m);
  }

}
  

void compare_hands(Collection &c, map<Result,int> score_map, map<string,int> m, map<int,string> r)   {

  Winner winner;
  
  //first set score (we have only set result so far)
  for (int i=0; i<c.hands.size(); i++){
    set_hand_score(c.hands[i],score_map);
  }

  //first sort in order of score
  sort(c.hands.begin(), c.hands.end(),
       [](Hand &a, Hand &b){
	 return a.score>b.score;
       });

  //since we only have 3 scores we can handle them individually
  handle_scores(c,winner,m);

  cout << "Hands " << endl;
  for(int i=0; i<c.hands.size(); i++){
    print_hand_score(c.hands[i]);
  }

  print_winner_attributes(winner);
    
  
}

  
  
