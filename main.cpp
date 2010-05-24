#include<iostream>
#include"Deck.h"
#include"CommunityCards.h"
#include"HoleCards.h"
#include"GameLogic.h"
#include<ctime>
#include<cstdlib>
using namespace std;
int main(int argc,char**argv){
	Deck deck;
	deck.fill();
	srand(time(NULL));
	deck.shuffle();
	HoleCards pocket,his;
	pocket.setCards(deck.pop(),deck.pop());
	cout<<"I have"<<endl;
	pocket.debug();
	his.setCards(deck.pop(),deck.pop());
	cout<<"He has"<<endl;
	his.debug();
	CommunityCards our;
	our.setFlop(deck.pop(),deck.pop(),deck.pop());
	our.setTurn(deck.pop());
	our.setRiver(deck.pop());
	cout<<"River is"<<endl;
	our.debug();
	HandStrength myhs;GameLogic::getStrength(&pocket,&our,&myhs);
	HandStrength hishs;GameLogic::getStrength(&his,&our,&hishs);
	if(myhs<hishs){
		cout<<"He wins with "<<hishs.getRankingName(hishs.getRanking())<<endl;
		cout<<"I had "<<myhs.getRankingName(myhs.getRanking())<<endl;
	}
	if(myhs>hishs){
		cout<<"I win with "<<myhs.getRankingName(myhs.getRanking())<<endl;
		cout<<"He had "<<hishs.getRankingName(hishs.getRanking())<<endl;
	}
	if(myhs==hishs)
		cout<<"It's a Tie! We both had "<<hishs.getRankingName(hishs.getRanking())<<endl;
	return 0;
}
