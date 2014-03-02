// Sudoku constraint satisfaction implementation
// State implementation
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

void State::removeFromDomain(int v)
{
	if (_domain[v] == true)
		return;
	if (!this->isFinal())
		_domain[v] = true;

	_domainSize--;
	assert(_domainSize > 0);

	if (_domainSize == 1){
		for (int i = 1; i <= 9; i++)
		{
			if (!_domain[i]){
				_assignedNumber = i;
				return;
			}
		}
	}
}

int State::assignedValue()
{
	return _assignedNumber;
}

void State::consolidate(){
	assert(this->_assignedNumber > 0);
	this->_final = true;
	free(_domain);
}