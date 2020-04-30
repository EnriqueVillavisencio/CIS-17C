/* 
 * File:   Waste.h
 * Author: Enrique Villavisencio
 *
 * Created on April 29, 2020, 6:37 PM
 */

#ifndef WASTE_H
#define WASTE_H

class Waste
{
private:
	list<int>* waste;
public:
	Waste();
	~Waste() { delete waste; }
	list<int>* getWaste() { return waste; }
};

Waste::Waste()
{
	waste = new list<int>;
}

#endif /* WASTE_H */

