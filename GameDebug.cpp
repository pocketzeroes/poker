#include"GameDebug.h"
using namespace std;
#if DEBUG
void print_cards(const char *name, vector<Card> *cards){
//	cout<<name;
	for(vector<Card>::iterator e=cards->begin();e!=cards->end();e++){
		if(e->getSuit()==Card::Diamonds||e->getSuit()==Card::Hearts)
			textcolor(RESET,RED,HIDDEN);
		else
			textcolor(RESET,BLACK,HIDDEN);
		cout<<e->getName();
	}
	cout<<endl;
	textcolor(RESET,BLACK,HIDDEN);
}
#endif