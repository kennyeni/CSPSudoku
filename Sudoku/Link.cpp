// Author: Andres Duran <contact@ekenny.org>
// Sudoku constraint satisfaction implementation
// Link implementation
#include "Link.h"

Link::Link(State * t, State * h)
{
	this->tail = t;
	this->head = h;
}

State * Link::getTail(){
	return tail;
}

State * Link::getHead(){
	return head;
}

size_t Link::hash(const Link& a)
{
	int hash = 0;
	hash += (*a.head).getRow();
	hash *= 10;
	hash += (*a.head).getCol();
	hash *= 10;
	hash += (*a.tail).getRow();
	hash *= 10;
	hash += (*a.tail).getCol();
	return hash;
}

bool Link::equalTo(const Link& a, const Link& b)
{
	return a.head == b.head && a.tail == b.tail;
}