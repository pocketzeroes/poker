#include"GameDebug.h"
using namespace std;
#if DEBUG
void print_cards(const char *name, vector<Card> *cards){
//	cout<<name;
	for(vector<Card>::iterator e=cards->begin();e!=cards->end();e++){
		if(e->getSuit()==Card::Diamonds||e->getSuit()==Card::Hearts)
			textcolor(BRIGHT,RED,WHITE);
		else
			textcolor(BRIGHT,BLACK,WHITE);
		cout<<e->getName();
	}
	cout<<endl;
	textcolor(BRIGHT,BLACK,WHITE);
}
#endif
