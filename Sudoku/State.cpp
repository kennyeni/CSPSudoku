// State implementation
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

#include <stdlib.h>
#include "State.h"
#ifndef ASSERT_H
#define SSERT_H
#include <assert.h>
#endif

State::State(int initialValue, int row, int col)
{
	this->_row = row;
	this->_col = col;
	this->_dirty = false;
	if (initialValue > 0)
	{
		_final = true;
		_assignedNumber = initialValue;
		_domainSize = 0;
	}
	else
	{
		_domain = (bool *) calloc(11, sizeof(bool));
		_final = false;
		_domainSize = 9;
	}
}

State::~State()
{
	free(_domain);
}

// Is the given number still on the domain?
bool State::numberAvailable(int i)
{
	if (_final)
	{
		return i == _assignedNumber;
	}
	return !_domain[i];
}

bool State::isFinal()
{
	return _final;;
}

int State::getRow()
{
	return _row;
}

int State::getCol()
{
	return _col;
}

// Marks the state as dirty if no element is remaining on the domain 
void State::removeFromDomain(int v)
{
	if (_domain[v] == true)
		return;
	if (!this->isFinal())
		_domain[v] = true;

	_domainSize--;

	if (_domainSize == 1){
		for (int i = 1; i <= 9; i++)
		{
			if (!_domain[i]){
				_assignedNumber = i;
				return;
			}
		}
	}

	if (_domainSize <= 0)
	{
		this->_dirty = true;
	}

}

bool State::isDirty()
{
	return _dirty;
}

int State::assignedValue()
{
	return _assignedNumber;
}

// FInalize this state, assume it was given as an initial datum
void State::consolidate(){
	assert(this->_assignedNumber > 0);
	this->_final = true;
	free(_domain);
}

// Gives priority to smaller domain states
bool State::compareTo(const State& a, const State& b)
{
	return a._domainSize > b._domainSize;
}