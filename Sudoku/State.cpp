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
	this->_forced = false;
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

State::State(const State& other){
	this->_assignedNumber = other._assignedNumber;
	this->_col = other._col;
	this->_row = other._row;
	this->_domainSize = other._domainSize;
	this->_final = other._final;
	this->_dirty = other._dirty;
	this->_forced = other._forced;

	if (other._domain){
		this->_domain = (bool *)calloc(11, sizeof(bool));
		for (int i = 0; i < 11; i++)
		{
			this->_domain[i] = other._domain[i];
		}
	}
	
	
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
				_forced = true;
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
bool State::compareTo(State& a, State& b)
{
	return a._domainSize > b._domainSize;
}

// Simulate this state to be initial so the number is forced
void State::forceAssignment(int i){
	this->_forced = true;
	this->_assignedNumber = i;
	for (int i = 1; i <= 9; i++){
		if (_assignedNumber != i)
			this->removeFromDomain(i);
	}
}

bool State::isForced(){
	return _forced;
}

// Makes a deep copy of the array, if the state is final, we recycle it
void State::copyStateArray(State * a[][9], State * b[][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			State * tmp;
			if (a[i][j]->isFinal())
			{
				tmp = a[i][j];
			}
			else
			{
				tmp = new State(*a[i][j]); // A copy is made
			}
			b[i][j] = tmp;
		}
	}
}