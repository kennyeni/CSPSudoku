// Author: Andres Duran <contact@ekenny.org>
#include "QueueSet.h"

template<typename T>
void QueueSet<T>::push(T element)
{
	if (! contains(element))
	{
		_set.insert(element);
		_queue.push(element);
	}
}

template<typename T>
bool QueueSet<T>::contains(T element)
{
	return !(_set.find() == _set.end());
}

template<typename T>
T QueueSet<T>::pop()
{
	State tmp =  _queue.pop();
	_set.erase(tmp);
	return tmp;
}
