#ifndef RANK_PAIR_TWO_H
#define RANK_PAIR_TWO_H
void rank_pair(const Hand &first, const Hand &second, Winner &winner,
	       std::map<std::string,int> m);
#endif

#ifndef RANK_PAIR_THREE_H
#define RANK_PAIR_THREE_H
void rank_pair(const Hand &first, const Hand &second, const Hand &third, Winner &winner,
	       std::map<std::string,int> m);
#endif
