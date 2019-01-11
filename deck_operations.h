#ifndef UPDATE_DECK_H
#define UPDATE_DECK_H
void update_deck(std::vector<Cards> &Deck, int i, std::string s);
#endif

#ifndef ADD_BOARD_TO_DECK_H
#define ADD_BOARD_TO_DECK_H
void add_board_to_deck(std::vector<Cards> &Deck, Collection &c, std::map<std::string,int> &m);
#endif

#ifndef ADD_HAND_TO_DECK_PAIR_H
#define ADD_HAND_TO_DECK_PAIR_H
void add_hand_to_deck(std::vector<Cards> &Deck, Hand &hand, std::map<std::string, int> &m);
#endif

#ifndef APPEND_H
#define APPEND_H
std::vector<std::string> append(std::vector<std::string> hand, std::vector<std::string> board);
#endif

#ifndef SORT_CARDS_H
#define SORT_CARDS_H
void sort_cards(std::vector<std::string> &cards, const std::map<std::string, int> m);
#endif

#ifndef REMOVE_DUPLICATES_H
#define REMOVE_DUPLICATES_H
std::vector<std::string> rmdup(std::vector<std::string> cards,
			       std::map<std::string,int> m);
#endif

#ifndef CHECK_STRAIGHT_H
#define CHECK_STRAIGHT_H
std::deque<bool> check_straight(std::vector<std::string> cards, int sizediff,
				std::map<std::string, int> m);
#endif

#ifndef CHECK_STRAIGHT_FLUSH_H
#define CHECK_STRAIGHT_FLUSH_H
bool check_straight_flush(std::vector<std::string> cards, std::map<std::string, int> m);
#endif

#ifndef PRINT_DECK_INDEX_H
#define PRINT_DECK_INDEX_H
void print_deck_index(const std::vector<Cards> Deck, int index, std::map <std::string,int> m, std::map<int,std::string> r);
#endif

#ifndef FIND_HAND_CARD_H
#define FIND_HAND_CARD_H
bool find_hand_card(std::vector<std::string> hand, std::vector<std::string> cards);
#endif

#ifndef PRINT_STATE_H
#define PRINT_STATE_H
void print_state(Hand hand);
#endif
