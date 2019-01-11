#ifndef GLOBAL_H
#define GLOBAL_H

namespace global{
  void print_(std::vector<std::string> cards);
  /*  void print(std::vector<std::string> cards){
    for_each(cards.begin(), cards.end(), [](std::string &c){
	std::cout << c << " ";
    });
    std::cout << endl;
    }*/
}
#endif

#ifndef BOARD_H
#define BOARD_H
struct Board{
  std::vector<std::string> board = std::vector<std::string>(5);
  void print_();
  void read(std::istream& s);
  void check_errors();
};
#endif

#ifndef RESULT_H
#define RESULT_H
enum class Result{
  royal_flush,
    straight_flush,
    four_of_a_kind,
    full_house,
    flush,
    straight,
    three_of_a_kind,
    two_pair,
    pair,
    high_card};
#endif

#ifndef STATE_H
#define STATE_H
struct State{
  Result result;
  std::string state_marker;
};
#endif

#ifndef HAND_H
#define HAND_H
struct Hand{
  std::string name;
  std::vector<std::string> hand = std::vector<std::string>(2);
  void print_();
  void read(std::istream &s);
  void check_errors();
  Result result;
  int score; //score associated with result
  std::string state_marker;
  //also need kickers - as I learnt very late
  std::vector<std::string> triplet_kickers = std::vector<std::string>(2);
  std::string two_pair_kicker;
  std::vector<std::string> pair_kickers;
  std::vector<std::string> high_card_kickers;
  std::string quad_kicker;
  std::vector<std::string> spare_flushes;

  void print_kickers();

};
#endif

#ifndef COLLECTION_H
#define COLLECTION_H
  struct Collection{
    Board board;
    std::vector<Hand> hands = std::vector<Hand>(3);

    Collection(std::istream &s);
    void read_board(std::istream &s);
    void read_hands(std::istream &s);
    void print_();
  };
#endif
    
#ifndef CARDS_H
#define CARDS_H
struct Cards{
  bool Spade;
  bool Club;
  bool Heart;
  bool Diamond;
  int count;
  bool is_hand_card=false;

  void print(){
    std::cout << "S " << Spade << std::endl;
    std::cout << "C " << Club << std::endl;
    std::cout << "H " << Heart << std::endl;
    std::cout << "D " << Diamond << std::endl;
    std::cout << "count " << count << std::endl;
  }

};

#endif  

#ifndef WINNER_H
#define WINNER_H
struct Winner{
  std::vector<Hand> hands;
};
#endif

  
  

