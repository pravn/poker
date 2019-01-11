#ifndef IS_PAIR_H
#define IS_PAIR_H
bool is_pair();
#endif

#ifndef IS_TWO_PAIR_H
#define IS_TWO_PAIR_H
bool is_two_pair();
#endif

#ifndef IS_THREE_OF_A_KIND_H
#define IS_THREE_OF_A_KIND_H
bool is_three_of_a_kind();
#endif

#ifndef CHECK_CASES_H
#define CHECK_CASES_H
void check_cases(std::vector<Cards> &Deck, Collection &c, std::map<std::string,int> &m,
		 std::map<int, std::string> &r);
#endif
