// Sudoku constraint satisfaction implementation
// State implementation
#include <stdlib.h>
#include "State.h"

State::State(int initialValue)
{
	if (initialValue > 0)
	{
		initial = true;
		assignedNumber = initialValue;
	}
	else
	{
		dominio = (bool *) calloc(10, sizeof(bool));
		initial = false;
	}
}

State::~State()
{
	free(dominio);
}

bool State::numberUsed(int i)
{
	return !dominio[i];
}

bool State::isInitial()
{
	return initial;;
}


















