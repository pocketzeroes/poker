#ifndef _DECK_H
#define _DECK_H
#include <vector>
#include "Card.h"
class Deck{
public:
	void fill();
	void empty();
	int count() const;
	bool push(Card card);
	Card pop();
	bool shuffle();
	void debugRemoveCard(Card card);
	void debugPushCards(const std::vector<Card> *cardsvec);
	void debug();
private:
	std::vector<Card> cards;
};
#endif
