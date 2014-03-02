// Author: Andres Duran <contact@ekenny.org>
#include <unordered_set>
#include <queue>
/*
* Esta funcion define una fila con elementos unicos
* en el contexto de esta funcion, los elementos son iguales
* si su direccion de memoria es la misma.
*/

class Hasher
{
public:
	size_t operator() (string const& key) const
	{
		cout << "Hashing called";
		size_t hash = 0;
		for (size_t i = 0; i<key.size(); i++)
		{
			hash += (71 * hash + key[i]) % 5;
		}
		return hash;
	}
};
class EqualFn
{
public:
	bool operator() (string const& t1, string const& t2) const
	{
		cout << "Equal called";
		return !(t1.compare(t2));
	}
};


template<typename T>
class QueueSet
{
	std::queue<T> _queue;
	std::unordered_set<T, T, Hasher, EqualFn> _set;
public:
	QueueSet();
	void push(T);
	T pop();
	bool contains(T);
};