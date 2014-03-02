// Author: Andres Duran <contact@ekenny.org>
// Sudoku constraint satisfaction implementation
// Link implementation
#include "Link.h"

Link::Link(State * t, State * h)
{
	this->tail = t;
	this->head = h;
}