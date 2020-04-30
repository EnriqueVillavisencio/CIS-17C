/* 
 * File:   Tableau.h
 * Author: Enrique Villavisencio
 *
 * Created on April 29, 2020, 6:34 PM
 */

#ifndef TABLEAU_H
#define TABLEAU_H

class Tableau
{
private:
	int startCards;
	list<pair<int, bool>>* tableau;
public:
	Tableau(int);
	~Tableau();
	list<pair<int, bool>>* getTableau() { return tableau; }
	int getStartCards() { return startCards; }
	list<pair<int, bool>> removeCards(int);
	bool only1Up();
};

Tableau::Tableau(int n)
{
	tableau = new list<pair<int, bool>>;
	startCards = n;
}

Tableau::~Tableau()
{
	delete tableau;
}

list<pair<int, bool>> Tableau::removeCards(int n)
{
	//Create a temp list to hold the cards that are removed
	list<pair<int, bool>> temp;

	//Move cards from the tableau pile to the temp list to return
	while (!tableau->empty() && tableau->front().second == true)
	{
		temp.push_front(tableau->front());

		if (tableau->front().first == n)
		{
			tableau->pop_front();
			if (tableau->empty())
				return temp;
			else if (tableau->front().second == false)
				tableau->front().second = true;
			break;
		}
		else
			tableau->pop_front();
	}
	return temp;
}

bool Tableau::only1Up()
{
	int count = 0;
	for (list<pair<int, bool>>::iterator itr = tableau->begin(); itr != tableau->end(); itr++)
	{
		if (itr->second == true)
			count++;
	}
	if (count <= 1)
		return true;
	else
		return false;
}

#endif /* TABLEAU_H */

