/* 
 * File:   Deck.h
 * Author: Enrique Villavisencio
 *
 * Created on April 29, 2020, 6:32 PM
 */

#ifndef DECK_H
#define DECK_H

#include "Card.h"

using namespace std;

class Deck
{
private:
	const string RANK[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	const char SUIT[4] = { 'S', 'D', 'C', 'H' };
	const char COLOR[2] = { 'B', 'R' };

	string valRank[52];
	pair<char, char> suitColor[4];
	deque<int>* deckIndx;
	map<string, int> inputRef;
	map<int, Card> deckRef;
public:
	Deck();
	Card getCard(int);
	deque<int>* getDeck() { return deckIndx; }
	void displayCard(int);
	void displayCard(pair<int, bool>);
	bool validateCardInput(string);
	int getCardIndxFromInput(string card) { return inputRef.find(card)->second; }
};

Deck::Deck()
{
	//Setting up CARD[52] for player card input reference
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			valRank[(13 * i) + j] = RANK[j] + SUIT[i];
			inputRef.insert(pair<string, char>(valRank[(13 * i) + j], (13 * i) + j));
		}
	}

	//Pair the suits with the correct colors
	for (int i = 0; i < 4; i++)
	{
		suitColor[i] = pair<char, char>('1', '2');
		if (SUIT[i] == 'C' || SUIT[i] == 'S')
			suitColor[i] = make_pair(SUIT[i], COLOR[0]);
		else
			suitColor[i] = make_pair(SUIT[i], COLOR[1]);
	}

	//Create Deck Index using Deque
	deckIndx = new deque<int>;
	for (int i = 0; i < 52; i++)
		deckIndx->push_back(i);

	//Create the deck of card reference
	deque<int>::iterator itr = deckIndx->begin();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			Card* card = new Card(j, RANK[j], suitColor[i].first, suitColor[i].second);
			deckRef.insert(make_pair(*itr, *card));
			itr++;
		}
	}
}

Card Deck::getCard(int n)
{	
	map<int, Card>::iterator itr = deckRef.find(n);
	return itr->second;
}

void Deck::displayCard(int n)
{
	map<int, Card>::iterator itr = deckRef.find(n);
	cout << "[" << itr->second.getRank() << ":" << itr->second.getSuit() << ":" << itr->second.getColor() << "]";
}

//Prints out the specific card 
void Deck::displayCard(pair<int, bool> p)
{
	if (p.second == false)
		cout << "[ ? ]";
	else
	{
		map<int, Card>::iterator itr = deckRef.find(p.first);
		cout << "[" << itr->second.getRank() << ":" << itr->second.getSuit() << ":" << itr->second.getColor() << "]";
	}
}

bool Deck::validateCardInput(string card)
{
	for (int i = 0; i < 52; i++)
	{
		if (card == valRank[i])
			return true;
	}
	return false;
}


#endif /* DECK_H */

