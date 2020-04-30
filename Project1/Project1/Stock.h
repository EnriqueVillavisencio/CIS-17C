/* 
 * File:   Stock.h
 * Author: Enrique Villavisencio
 *
 * Created on April 29, 2020, 6:36 PM
 */

#ifndef STOCK_H
#define STOCK_H

class Stock
{
private:
	stack<int>* stock;
public:
	Stock();
	~Stock() { delete stock; }
	stack<int>* getStock() { return stock; }
};

Stock::Stock()
{
	stock = new stack<int>;
}

#endif /* STOCK_H */

