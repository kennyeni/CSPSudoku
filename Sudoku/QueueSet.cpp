// Author: Andres Duran <contact@ekenny.org>
#ifndef LINK_H
#define LINK_H
#include "Link.h"
#endif


#ifndef ASSERT_H
#define SSERT_H
#include <assert.h>
#endif

#include "QueueSet.h"

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

bool QueueSet::contains(Link element)
{
	return !(_set.find(element) == _set.end());
}

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
