// Author: Andres Duran <contact@ekenny.org>
#ifndef LINK_H
#define LINK_H
#include "Link.h"
#endif
#include "QueueSet.h"

void QueueSet::push(Link element)
{
	if (! contains(element))
	{
		_set.insert(element);
		_queue.push(element);
	}
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
	return tmp;
}
