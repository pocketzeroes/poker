#ifndef _GAMELOGIC_H
#define _GAMELOGIC_H
#include <vector>
#include "Card.h"
#include "HoleCards.h"
#include "CommunityCards.h"
class HandStrength
{
friend class GameLogic;
public:
	typedef enum {
		HighCard=0,
		OnePair,
		TwoPair,
		ThreeOfAKind,
		Straight,
		Flush,
		FullHouse,
		FourOfAKind,
		StraightFlush
	} Ranking;
	Ranking getRanking() const { return ranking; };
	static const char* getRankingName(Ranking r);
	void copyRankCards(std::vector<Card> *v) const { v->insert(v->end(), rank.begin(), rank.end()); };
	void copyKickerCards(std::vector<Card> *v) const { v->insert(v->end(), kicker.begin(), kicker.end()); };
	void setId(int rid) { id = rid; };
	int getId() const { return id; };
	bool operator < (const HandStrength &c) const;
	bool operator > (const HandStrength &c) const;
	bool operator == (const HandStrength &c) const;
private:
	Ranking ranking;
	std::vector<Card> rank;
	std::vector<Card> kicker;
	int id;
};
class GameLogic
{
public:
	GameLogic();
	static bool getStrength(std::vector<Card> *allcards, HandStrength *strength);
	static bool getStrength(const HoleCards *hole, const CommunityCards *community, HandStrength *strength);
	static bool isTwoPair(std::vector<Card> *allcards, std::vector<Card> *rank, std::vector<Card> *kicker);
	static bool isStraight(std::vector<Card> *allcards, const int suit, std::vector<Card> *rank);
	static bool isFlush(std::vector<Card> *allcards, std::vector<Card> *rank);
	static bool isXOfAKind(std::vector<Card> *allcards, const unsigned int n, std::vector<Card> *rank, std::vector<Card> *kicker);
	static bool isFullHouse(std::vector<Card> *allcards, std::vector<Card> *rank);
	static bool getWinList(std::vector<HandStrength> &hands, std::vector< std::vector<HandStrength> > &winlist);
};
#endif
