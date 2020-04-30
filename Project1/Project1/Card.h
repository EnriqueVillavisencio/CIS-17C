/* 
 * File:   Card.h
 * Author: Enrique Villavisencio
 *
 * Created on April 29, 2020, 6:29 PM
 */

#ifndef CARD_H
#define CARD_H

class Card
{
private:
	int value;
	string rank;
	char suit;
	char color;
public:
	Card(int, string, char, char);
	int getValue() { return value; }
	string getRank() { return rank; }
	char getSuit() { return suit; }
	char getColor() { return color; }
};

Card::Card(int v, string r, char s, char c)
{
	value = v;
	rank = r;
	suit = s;
	color = c;
}

#endif /* CARD_H */

