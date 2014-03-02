// Author: Andres Duran <contact@ekenny.org>
// Sudoku constraint satisfaction implementation
// Link head
#ifndef STATE_H
#define STATE_H
#include "State.h"
#endif

class Link
{
	State * tail;
	State * head;
public:
	Link(State * tail, State * head);
	bool operator() (const Link& x, const Link& y) const 
	{ 
		return x.head == y.head && x.tail == y.head; 
	}
};