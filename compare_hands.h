#ifndef SET_HAND_SCORE_H
#define SET_HAND_SCORE_H
void set_hand_score(Hand &hand, std::map<Result,int> score_map);
#endif

#ifndef COMPARE_HANDS_H
#define COMPARE_HANDS_H
void compare_hands(Collection &c, std::map<Result,int> score_map, std::map<std::string,int> M,
		   std::map<int, std::string> R);
#endif
