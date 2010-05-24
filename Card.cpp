#include<string>
#include "Card.h"
using namespace std;
string face_symbols="23456789TJQKA";
string s1="♣";
string s2="♦";
string s3="♥";
string s4="♠";
Card::Card(){
	face = Card::FirstFace;
	suit = Card::FirstSuit;
}
Card::Card(Face f, Suit s){
	face = f;
	suit = s;
}
void Card::getValue(Face *f, Suit *s) const{
	if(f)
		*f=face;
	if(s)
		*s=suit;
}
string Card::getName() const{
	string card_name="";
	if(face_symbols[face-Card::FirstFace]=='T')
		card_name+="10";
	else
		card_name+=face_symbols[face-Card::FirstFace];
	switch(suit){
		case Clubs:
			card_name+=s1;break;
		case Diamonds:
			card_name+=s2;break;
		case Hearts:
			card_name+=s3;break;
		case Spades:
			card_name+=s4;break;
	}
	return card_name;
}
