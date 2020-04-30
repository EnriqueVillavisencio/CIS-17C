/* 
 * File:   Game.h
 * Author: Enrique Villavisencio
 *
 * Created on April 29, 2020, 6:27 PM
 */

#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Tableau.h"
#include "Foundation.h"
#include "Stock.h"
#include "Waste.h"

class Game
{
private:
	Deck* deck;
	Tableau* tableau[7];
	Foundation* foundation[4];
	Stock* stock;
	Waste* waste;
public:
	Game();
     ~Game();
	void init();
	void deal();
	void displayTable();
	void stockPile();
	list<pair<int, bool>> fromCards(string, int);
	void toTableau(string, int, int);
	void toFoundation(string, int, int);
	bool validateCard(string, string);
	bool validateToT(Card, int, bool);
	bool validateToF(Card, int, bool);
};


Game::Game()
{
	int choice;
	cout << "\t\t\t\t\tSolitaire" << endl;
	cout << "============================================================================================================" << endl;
	cout << "1. Start \t 2. Exit" << endl;
	cout << "Enter choice: ";
	cin >> choice;
	cin.ignore();

	switch (choice)
	{
	case 1:
	{
		system("clear");
		init();

		//Shuffle the deck using random_shuffle
		random_shuffle(deck->getDeck()->begin(), deck->getDeck()->end());

		deal();

		//Start the main game loop and continue looping until end equals true
		bool end = false;
		while (!end)
		{
			system("clear");
			displayTable();
			int choice = 0;
			bool isValid = false;

			while (!isValid)
			{
				choice = 0;
				cout << "1. Move Card    2. Stock Pile   3. Quit" << endl;
				cout << "  Enter choice: ";
				cin >> choice;

				if (cin.fail())
				{
					cout << "Input is invalid. Try aain." << endl;
					cin.clear();
					cin.ignore();
				}
				else
					isValid = true;
			}

			//Start the game or exit depending on the choice you made
			switch (choice)
			{
			case 1:
			{
				string from, to, card;
				bool chooseCard = false;
				int fromIndx, cardIndx;
				cin.ignore();

				isValid = false;

				//Loop to repeat "Choose where to move from:" if input is invalid
				while (!isValid)
				{
					cout << "Tableau: T1, T2, T3, T4, T5, T6, T7    Waste: W" << endl;
					cout << "  Choose where to move from:";
					getline(cin, from);


					//Validate input
					if (from == "W")
					{
						if (waste->getWaste()->empty())
							cout << "Waste Pile is empty." << endl;
						else
							isValid = true;
					}
					else
					{
						if (from.size() > 2 || from.at(0) != 'T' || isalpha(from.at(1)))
							cout << "Invalid input." << endl;
						else
						{
							fromIndx = (from.at(1) - '0') - 1;
							//Check if the tableau index range is within range
							if (fromIndx >= 0 && fromIndx <= 6)
							{
								if (tableau[fromIndx]->getTableau()->empty())
									cout << "Tableau " << fromIndx << " is empty." << endl;
								else
									isValid = true;
							}
							else
								cout << "Invalid input." << endl;
						}
					}
				}

				//Determine if you need to choose a card to move
				if (from != "W")
				{
					if (!(tableau[fromIndx]->only1Up()))
					{
						isValid = false;
						//Loop to repeat if card input is invalid or the card doesn't exist in the pile
						while (!isValid)
						{
							cout << "  Choose the card to move:(Ex: AS for Ace of Spades): ";
							getline(cin, card);
							if (!(deck->validateCardInput(card)))
								cout << "Invalid input, try again." << endl;
							else
							{
								if (validateCard(from, card))
								{
									cardIndx = deck->getCardIndxFromInput(card);
									isValid = true;
								}
								else
									cout << "That card doesn't exist in that pile. Try again." << endl;
							}
						}
					}
					else
						cardIndx = tableau[fromIndx]->getTableau()->front().first;
				}
				else
					cardIndx = waste->getWaste()->front();


				//Choose where to move the card to
				isValid = false;
				int toIndx;
				while (!isValid)
				{
					//Display choices
					cout << "Tableau: T1, T2, T3, T4, T5, T6, T7    Foundation: F1, F2, F3, F4" << endl;
					cout << "  Where do you want to move to:";
					getline(cin, to);

					//Validate the input
					//Check if the from location is the same as the to location
					if (from == to)
						cout << "You can't move a card from the same place." << endl;
					else
					{
						//Check the first character in the string to see if it matches the cases
						switch (to.at(0))
						{
						case 'T':
							//Get the index for the container we are moving the card to
							toIndx = (to.at(1) - '0') - 1;

							//Check if the tableau index is within 0 - 6
							if (toIndx >= 0 && toIndx <= 6)
								isValid = true;
							break;
						case 'F':
							//Get the index for the container we are moving the card to
							toIndx = (to.at(1) - '0') - 1;

							//Check if the foundation index is within 0 - 3
							if (toIndx >= 0 && toIndx <= 3)
								isValid = true;
							break;
						default:
							break;
						}
						if (!isValid)
							cout << "Invalid input." << endl;
					}
				}

				//Start the process to move cards from one pile to another
				switch (to.at(0))
				{
				case 'T':
					toTableau(from, cardIndx, toIndx);
					break;
				case 'F':
					toFoundation(from, cardIndx, toIndx);
					break;
				default:
					break;
				}
                                
                                
				//Winning Condition
				for (int i = 0; i < 7; i++)
				{
					if (!tableau[i]->getTableau()->empty())
						break;
                                        if (i == 6)
                                            end = true;
				}
				break;
			}
			case 2:
				stockPile();
				break;
			case 3:
				exit(0);
				break;
			default:
				break;
			}
		}
	}
		break;
	case 2: 
		exit(0);
		break;
	default:
		break;
	}
}

Game::~Game()
{
    delete deck;
    for (int i = 0; i < 7; i++)
        delete tableau[i];
    for(int i = 0; i < 4; i++)
        delete foundation[i];
    delete stock;
    delete waste;
}

void Game::init()
{
	//Create the deck for cards
	deck = new Deck;

	//Create the 7 Tableau piles and assign the max cards they can hold at the start when the cards are being dealt
	for (int i = 0; i < 7; i++)
		tableau[i] = new Tableau(i + 1);

	//Initialize the 4 foundation piles where you will build up whole sequences based on suit
	for (int i = 0; i < 4; i++)
		foundation[i] = new Foundation;

	//Initialize the stock pile where the extra cards will sit
	stock = new Stock;

	//Initialize the waste pile
	waste = new Waste;
}

void Game::deal()
{
	//Deal out the cards from the deck into the 7 tableaus
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0 + i; j < 7; j++)
		{
			//Copy the top card from the deck to the current tableau
			tableau[j]->getTableau()->push_front(pair<int, bool>(deck->getDeck()->front(), false));

			if (tableau[j]->getTableau()->size() == tableau[j]->getStartCards())
				tableau[j]->getTableau()->front().second = true;

			deck->getDeck()->pop_front();
		}
	}

	////Put the rest of the cards into the stock pile
	for (int i = 0; i < deck->getDeck()->size(); i++)
	{
		stock->getStock()->push(deck->getDeck()->front());
		deck->getDeck()->pop_front();
	}
}


void Game::displayTable()
{
	//Game Title and helpful info
	cout << "\t\t\t\t\tSolitaire" << endl;
	cout << "============================================================================================================" << endl;
	cout << "S = Spades, D = Diamonds, C = Clubs, H = Hearts, A = Ace, J = Jack, Q = Queen, K = King, B = Black, R = Red" << endl;

	//Display for the foundation info
	cout << "============================================================================================================" << endl;
	cout << "Foundations:" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << i + 1 << ": ";
		//Check whether the foundation is empty to determine whether to display empty or a card
		if (foundation[i]->getFoundation()->empty())
			cout << "[Empty]";
		else
			deck->displayCard(foundation[i]->getFoundation()->top());
		cout << "\t";
	}
	cout << endl;

	//Display for the Stock and Waste piles
	cout << "============================================================================================================" << endl;
	cout << "Stock Pile: ";
	if (!stock->getStock()->empty())
		cout << "[ ? ] " << endl;
	else
		cout << "Empty." << endl;
	cout << "Waste Pile: ";
	if (waste->getWaste()->empty())
		cout << "[Empty]";
	else
	{
		list<int>::iterator itr = waste->getWaste()->begin();
		list<int> temp;

		for (int i = 0; i < 4; i++, i++)
		{
			if (itr != waste->getWaste()->end())
			{
				temp.push_front(*itr++);
			}
		}
		do
		{
			deck->displayCard(temp.front());
			temp.pop_front();
		} while (!temp.empty());
	}

	cout << endl;
	cout << "============================================================================================================" << endl;
	cout << "Tableaus:" << endl;
	for (int i = 0; i < 7; i++)
	{
		list<pair<int, bool>> temp = *tableau[i]->getTableau();
		temp.reverse();

		cout << i + 1 << ": ";
		for (list<pair<int, bool>>::iterator itr = temp.begin(); itr != temp.end(); itr++)
			deck->displayCard(*itr);
		cout << endl;
	}
	cout << "============================================================================================================" << endl;
}

void Game::stockPile()
{
	if (stock->getStock()->empty())
	{
		while (waste->getWaste()->size() > 0)
		{
			stock->getStock()->push(waste->getWaste()->front());
			waste->getWaste()->pop_front();
		}
	}
	else
	{
		waste->getWaste()->push_front(stock->getStock()->top());
		stock->getStock()->pop();
	}
}

void Game::toTableau(string from, int cardIndx, int toIndx)
{
	bool isValid = false;
	Card fromCard = deck->getCard(cardIndx);

	if (validateToT(fromCard, toIndx, tableau[toIndx]->getTableau()->empty()))
	{
		list<pair<int, bool>> temp = fromCards(from, cardIndx);
		for (list<pair<int, bool>>::iterator itr = temp.begin(); itr != temp.end(); itr++)
			cout << itr->first << " ";
		cout << endl;

		do
		{
			tableau[toIndx]->getTableau()->push_front(temp.front());
			temp.pop_front();
		} while (!temp.empty());
	}
}

void Game::toFoundation(string from, int cardIndx, int toIndx)
{
	Card fromCard = deck->getCard(cardIndx);
	
	if (validateToF(fromCard, toIndx, foundation[toIndx]->getFoundation()->empty()))
	{
		if (from == "W")
		{
			foundation[toIndx]->getFoundation()->push(waste->getWaste()->front());
			waste->getWaste()->pop_front();
		}
		else
		{
			list<pair<int, bool>> temp = fromCards(from, cardIndx);
			foundation[toIndx]->getFoundation()->push(temp.front().first);
		}
	}
}

list<pair<int, bool>> Game::fromCards(string from, int cardIndx)
{
	list<pair<int, bool>> temp;

	if (from == "W")
	{
		temp.push_front(pair<int, bool>(waste->getWaste()->front(), true));
		waste->getWaste()->pop_front();
		return temp;
	}
	else
	{
		int i = (from.at(1) - '0') - 1;

		//Tableau test for removing cards
		list<pair<int, bool>> temp = tableau[i]->removeCards(cardIndx);
		return temp;
	}
}

//Validate if the card exists in the pile
bool Game::validateCard(string from, string card)
{
	int i = (from.at(1) - '0') - 1;

	for (list<pair<int, bool>>::iterator itr = tableau[i]->getTableau()->begin(); itr != tableau[i]->getTableau()->end(); itr++)
	{
		int indx = deck->getCardIndxFromInput(card);
		if (itr->first == indx)
			return true;
	}
}

bool Game::validateToT(Card fromCard, int toIndx, bool empty)
{
	if (empty)
	{
		//Check if the rank of the card we are moving is a king
		if (fromCard.getRank() == "K")
			return true;
	}
	//If the top card in the tableau you are moving to has a value of 1 it returns false because you can't put a card above a card of value 1 in the tableau
	if (fromCard.getValue() == 1)
		return false;

	Card toCard = deck->getCard(tableau[toIndx]->getTableau()->front().first);
	//Checks if the card being moved is 1 value less than the top card in the tableau we are moving it to
	if (fromCard.getValue() == toCard.getValue() - 1 && fromCard.getColor() != toCard.getColor())
		return true;
	else
		return false;
}

bool Game::validateToF(Card fromCard, int toIndx, bool empty)
{
	if (empty)
	{
		//Check if the rank of the card you are moving is an Ace
		if (fromCard.getRank() == "A")
			return true;
	}
	Card toCard = deck->getCard(foundation[toIndx]->getFoundation()->top());

	if (fromCard.getSuit() != toCard.getSuit())
		return false;
}

#endif /* GAME_H */

