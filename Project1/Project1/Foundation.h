/* 
 * File:   Foundation.h
 * Author: Enrique Villavisencio
 *
 * Created on April 29, 2020, 6:38 PM
 */

#ifndef FOUNDATION_H
#define FOUNDATION_H

class Foundation
{
private:
	stack<int>* foundation;
public:
	Foundation();
	~Foundation() { delete foundation; }
	stack<int>* getFoundation() { return foundation; }
};

Foundation::Foundation()
{
	foundation = new stack<int>;
}

#endif /* FOUNDATION_H */

