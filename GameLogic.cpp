#include <algorithm>
#include <functional>
#include "GameDebug.h"
#include "GameLogic.h"
using namespace std;
bool GameLogic::getStrength(const HoleCards *hole, const CommunityCards *community, HandStrength *strength){
	vector<Card> allcards;
	hole->copyCards(&allcards);
	community->copyCards(&allcards);
	return getStrength(&allcards, strength);
}
bool GameLogic::getStrength(vector<Card> *allcards, HandStrength *strength){
	HandStrength::Ranking *r = &(strength->ranking);
	vector<Card> *rank = &(strength->rank);
	vector<Card> *kicker = &(strength->kicker);
	sort(allcards->begin(), allcards->end(), greater<Card>());
	rank->clear();
	kicker->clear();
	if (isFlush(allcards, rank) && isStraight(allcards, rank->front().getSuit(), rank))
		*r = HandStrength::StraightFlush;
	else if (isXOfAKind(allcards, 4, rank, kicker))
		*r = HandStrength::FourOfAKind;
	else if (isFullHouse(allcards, rank))
		*r = HandStrength::FullHouse;
	else if (isFlush(allcards, rank))
		*r = HandStrength::Flush;
	else if (isStraight(allcards, -1, rank))
		*r = HandStrength:: Straight;
	else if (isXOfAKind(allcards, 3, rank, kicker))
		*r = HandStrength::ThreeOfAKind;
	else if (isTwoPair(allcards, rank, kicker))
		*r = HandStrength::TwoPair;
	else if (isXOfAKind(allcards, 2, rank, kicker))
		*r = HandStrength::OnePair;
	else
	{
		*r = HandStrength::HighCard;
		rank->clear();
		rank->push_back(allcards->front());
		kicker->clear();
		for (vector<Card>::iterator e = allcards->begin() + 1; e != allcards->end() && kicker->size() < 4; e++)
			kicker->push_back(*e);
	}
	return true;
}
bool GameLogic::isTwoPair(std::vector<Card> *allcards, std::vector<Card> *rank, std::vector<Card> *kicker){
	bool is_twopair = false;
	vector<Card> trank, tkicker;
	if (isXOfAKind(allcards, 2, &trank, &tkicker)){
		Card fp = trank.front();
		if (isXOfAKind(allcards, 2, &trank, &tkicker)){
			Card sp = trank.front();
			rank->clear();
			rank->push_back(fp);
			rank->push_back(sp);
			kicker->clear();
			for (vector<Card>::iterator e = allcards->begin(); e != allcards->end() && kicker->size() < 1; e++)
				if (e->getFace() != fp.getFace() && e->getFace() != sp.getFace())
					kicker->push_back(*e);
			is_twopair = true;
		}
	}
	return is_twopair;
}
bool GameLogic::isStraight(vector<Card> *allcards, const int suit, vector<Card> *rank){
	bool is_straight = false;
	int last_face = -1, count = 0;
	Card high;
	for (vector<Card>::iterator e = allcards->begin(); e != allcards->end(); e++){
		if (suit != -1 && e->getSuit() != suit)
			continue;
		if (last_face == e->getFace())
			continue;
		if (last_face - 1 != e->getFace()){
			count = 1;
			high = *e;
		}
		else{
			if (++count == 5){
				is_straight = true;
				break;
			}
		}
		last_face = e->getFace();
	}
	if (count == 4 && (last_face == Card::Two && allcards->front().getFace() == Card::Ace))
		is_straight = true;
	if (is_straight){
		rank->clear();
		rank->push_back(high);
	}
	return is_straight;
}
bool GameLogic::isFlush(vector<Card> *allcards, vector<Card> *rank){
	bool is_flush = false;
	Card::Suit flush_suit;
	int suit_count[4] = {0, 0, 0, 0};
	for (vector<Card>::iterator e = allcards->begin(); e != allcards->end(); e++){
		if (++suit_count[e->getSuit() - Card::FirstSuit] == 5){
			flush_suit = e->getSuit();
			is_flush = true;
			break;
		}
	}
	if (is_flush){
		rank->clear();
		for (vector<Card>::iterator e = allcards->begin(); e != allcards->end() && rank->size() < 5; e++)
			if (e->getSuit() == flush_suit)
				rank->push_back(*e);
	}
	return is_flush;
}
bool GameLogic::isXOfAKind(vector<Card> *allcards, const unsigned int n, vector<Card> *rank, vector<Card> *kicker){
	bool is_xofakind = false;
	int face = -1;
	Card high;
	unsigned int count = 0;
	for (vector<Card>::iterator e = allcards->begin(); e != allcards->end(); e++){
		if (rank->size() && rank->begin()->getFace() == e->getFace())
			continue;
		if (e->getFace() != face){
			face = e->getFace();
			count = 1;
			high = *e;
		}
		else{
			if (++count == n){
				is_xofakind = true;
				break;
			}
		}
	}
	rank->clear();
	kicker->clear();
	if (is_xofakind){
		rank->push_back(high);
		for (vector<Card>::iterator e = allcards->begin(); e != allcards->end() && kicker->size() < (5 - n); e++)
			if (e->getFace() != face)
				kicker->push_back(*e);
	}
	return is_xofakind;
}
bool GameLogic::isFullHouse(vector<Card> *allcards, vector<Card> *rank){
	bool is_fullhouse = false;
	vector<Card> trank, tkicker;
	if (isXOfAKind(allcards, 3, &trank, &tkicker)){
		Card toak = trank.front();
		if (isXOfAKind(allcards, 2, &trank, &tkicker)){
			Card pc = trank.front();
			rank->clear();
			rank->push_back(toak);
			rank->push_back(pc);
			is_fullhouse = true;
		}
	}
	return is_fullhouse;
}
bool GameLogic::getWinList(vector<HandStrength> &hands, vector< vector<HandStrength> > &winlist){
	winlist.clear();
	winlist.push_back(hands);
	unsigned int index=0;
	while(true){
		vector<HandStrength> &tw = winlist[index];
		vector<HandStrength> tmp;
		sort(tw.begin(), tw.end(), greater<HandStrength>());
		for (unsigned int i=tw.size()-1; i > 0; i--)
			if (tw[i] < tw[0]){
				tmp.push_back(tw[i]);
				tw.pop_back();
			}
		if (!tmp.size())
			break;
		winlist.push_back(tmp);
		index++;
	}
	return true;
}
const char* HandStrength::getRankingName(Ranking r){
	static const char *sstr[] = {
		"High Card",
		"One Pair",
		"Two Pair",
		"Three Of A Kind",
		"Straight",
		"Flush",
		"Full House",
		"Four Of A Kind",
		"Straight Flush"
	};
	return sstr[r - HighCard];
}
bool HandStrength::operator < (const HandStrength &c) const{
	if (getRanking() < c.getRanking())
		return true;
	else if (getRanking() > c.getRanking())
		return false;
	for (unsigned int i=0; i < rank.size(); i++)
		if (rank[i].getFace() < c.rank[i].getFace())
			return true;
		else if (rank[i].getFace() > c.rank[i].getFace())
			return false;
	for (unsigned int i=0; i < kicker.size(); i++)
		if (kicker[i].getFace() < c.kicker[i].getFace())
			return true;
		else if (kicker[i].getFace() > c.kicker[i].getFace())
			return false;
	return false;
}
bool HandStrength::operator > (const HandStrength &c) const{
	if (getRanking() > c.getRanking())
		return true;
	else if (getRanking() < c.getRanking())
		return false;
	for (unsigned int i=0; i < rank.size(); i++)
		if (rank[i].getFace() > c.rank[i].getFace())
			return true;
		else if (rank[i].getFace() < c.rank[i].getFace())
			return false;
	for (unsigned int i=0; i < kicker.size(); i++)
		if (kicker[i].getFace() > c.kicker[i].getFace())
			return true;
		else if (kicker[i].getFace() < c.kicker[i].getFace())
			return false;
	return false;
}
bool HandStrength::operator == (const HandStrength &c) const{
	if (getRanking() != c.getRanking())
		return false;
	for (unsigned int i=0; i < rank.size(); i++)
		if (rank[i].getFace() != c.rank[i].getFace())
			return false;
	for (unsigned int i=0; i < kicker.size(); i++)
		if (kicker[i].getFace() != c.kicker[i].getFace())
			return false;
	return true;
}
