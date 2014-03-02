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
	State * getTail();
	State * getHead();
	static size_t hash(const Link&);
	static bool equalTo(const Link&, const Link&);
};