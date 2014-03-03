// QueueSet Implementation
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
#ifndef LINK_H
#define LINK_H
#include "Link.h"
#endif

#ifndef ASSERT_H
#define SSERT_H
#include <assert.h>
#endif

#include "QueueSet.h"

// Insert element if it's new
void QueueSet::push(Link element)
{
	if (! contains(element))
	{
		_set.insert(element);
		_queue.push(element);
		_size++;
	}

	assert(_set.size() == _queue.size());
	assert(_set.size() == _size);
}

// Does the queue has the given element already?
bool QueueSet::contains(Link element)
{
	return !(_set.find(element) == _set.end());
}

// Get and remove top element
Link QueueSet::pop()
{
	Link tmp =  _queue.front();
	_queue.pop();
	_set.erase(tmp);
	_size--;
	assert(_set.size() == _queue.size());
	assert(_set.size() == _size);
	return tmp;
}

int QueueSet::size()
{
	return _size;
}
