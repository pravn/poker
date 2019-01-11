#ifndef RANK_ROYAL_FLUSH_TWO_H
#define RANK_ROYAL_FLUSH_TWO_H
void rank_royal_flush(const Hand &first, const Hand &second, Winner &winner,
		      std::map<std::string,int> m);
#endif

#ifndef RANK_ROYAL_FLUSH_THREE_H
#define RANK_ROYAL_FLUSH_THREE_H
void rank_royal_flush(const Hand &first, const Hand &second, const Hand &third,
		      Winner &winner, std::map<std::string,int> m);
#endif
