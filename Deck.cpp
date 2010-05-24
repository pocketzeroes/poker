#include <algorithm>
#include "GameDebug.h"
#include "Deck.h"
using namespace std;
void Deck::fill(){
	cards.clear();
	for(int f=Card::FirstFace;f<=Card::LastFace;f++)
		for(int s=Card::FirstSuit;s<=Card::LastSuit;s++){
			Card c((Card::Face)f,(Card::Suit)s);
			push(c);
		}
}
void Deck::empty(){
	cards.clear();
}
int Deck::count() const{
	return cards.size();
}
bool Deck::push(Card card){
	cards.push_back(card);
	return true;
}
Card Deck::pop(){
	if (!count())
		exit(0);
	Card card=cards.back();
	cards.pop_back();
	return card;
}
bool Deck::shuffle(){
	random_shuffle(cards.begin(), cards.end());
	return true;
}
void Deck::debug(){
	print_cards("Deck", &cards);
}
void Deck::debugRemoveCard(Card card){
	for (vector<Card>::iterator e = cards.begin(); e != cards.end(); e++){
		if (e->getFace() == card.getFace() && e->getSuit() == card.getSuit()) {
			cards.erase(e);
			break;
		}
	}
}
void Deck::debugPushCards(const vector<Card> *cardsvec){
	for (vector<Card>::const_iterator e = cardsvec->begin(); e != cardsvec->end(); e++)
		push(*e);
}
