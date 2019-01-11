#ifndef RANK_TRIPLET_TWO_H
#define RANK_TRIPLET_TWO_H
void rank_triplet(const Hand &first, const Hand &second, Winner &winner,
		  std::map<std::string,int> m);
#endif

#ifndef RANK_TRIPLET_THREE_H
#define RANK_TRIPLET_THREE_H
void rank_triplet(const Hand &first, const Hand &second, const Hand &third,  Winner &winner,
	       std::map<std::string,int> m);
#endif
