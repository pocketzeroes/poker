#ifndef _CARD_H
#define _CARD_H
#include<string>
using namespace std;
class Card{
public:
	typedef enum {
		Two=2,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		Ten,
		Jack,
		Queen,
		King,
		Ace,
		FirstFace=Two,
		LastFace=Ace
	} Face;
	typedef enum {
		Clubs=1,
		Diamonds,
		Hearts,
		Spades,
		FirstSuit=Clubs,
		LastSuit=Spades
	} Suit;
	Card();
	Card(Face f, Suit s);
	void getValue(Face *f, Suit *s) const;
	Face getFace() const { return face; };
	Suit getSuit() const { return suit; };
	string getName()const;
	bool operator <  (const Card &c) const { return (getFace() < c.getFace()); };
	bool operator >  (const Card &c) const { return (getFace() > c.getFace()); };
	bool operator == (const Card &c) const { return (getFace() == c.getFace()); };
private:
	Face face;
	Suit suit;
};
#endif
