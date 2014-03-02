// Link implementation
/*
* Copyright (c) 2014 Andres Duran <contact@ekenny.org>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

// The hash is just a concatenated representation of the head and tail Rows and Cols
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

// The equality factor is just if the head and tail point to the same directions
bool Link::equalTo(const Link& a, const Link& b)
{
	return a.head == b.head && a.tail == b.tail;
}