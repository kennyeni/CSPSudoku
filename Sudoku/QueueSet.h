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

/*
* Helper class that defines an unordered queue with
* unique elements
*/

#include <unordered_set>
#include <queue>
#ifndef LINK_H
#define LINK_H
#include "Link.h"
#endif

// Helper structs to make Link comparable and hashable
// Requires class to implement static hash and equalTo methods 
struct Hasher {
	size_t operator() (const Link& a) const { return Link::hash(a); }
};

struct Equal {
	bool operator() (const Link& a, const Link& b) const { return Link::equalTo(a, b); }
};

// Main header
class QueueSet
{
	std::queue<Link> _queue;
	std::unordered_set<Link, Hasher, Equal> _set;
	int _size;
public:
	void push(Link);
	Link pop();
	bool contains(Link);
	int size();
};