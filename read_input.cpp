#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "data_container.h"
using namespace std;


void global::print_(vector<string> cards){
  for_each(cards.begin(), cards.end(), [](string &c){
      cout << c << " ";
    });
  cout << endl;
    }



void Board::print_(){
  global::print_(board);
}

void Board::read(istream& s){
  for (int i=0; i<board.size(); i++){
    s >> board[i];
  }
}


void Hand::print_(){
    cout << name <<  " ";
    global::print_(hand);
  }
  
void Hand::read(istream &s){
  s >> name;
    for (int i=0; i<hand.size(); i++){
      s >> hand[i];
    }
  }


Collection::Collection(std::istream &s){
  board.read(s);
  for_each (hands.begin(), hands.end(),
	    [&s](Hand &h){
	      h.read(s);
	    }

	    );
}

void Collection::print_(){
  board.print_();
  std::vector<Hand>::iterator h;

  for (h = hands.begin(); h!=hands.end(); h++){
    h->print_();
  }
}

Collection read_collection(ifstream &infile){
  Collection e(infile);
  return e;
}

Collection read_input(ifstream &infile){
  auto e = read_collection(infile);
  cout << "Done reading " << endl;

  e.print_();
  return e;
}

 
