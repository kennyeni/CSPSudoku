// Author: Andres Duran <contact@ekenny.org>
// Sudoku constraint satisfaction implementation
// Link implementation
#include "Link.h"

Link::Link(State * t, State * h)
{
	this->tail = t;
	this->head = h;
}

Link::Link(){}

size_t Link::hash(const Link& a)
{
	return ((size_t)&a / sizeof(Link));
}

bool Link::equalTo(const Link& a, const Link& b)
{
	return a.head == b.head && a.tail == b.tail;
}