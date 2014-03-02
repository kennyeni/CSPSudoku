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

// Main algorithm point of entry

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#ifndef STATE_H
#define STATE_H
#include "State.h"
#endif

#ifndef LINK_H
#define LINK_H
#include "Link.h"
#endif

#include "QueueSet.h"

State * states[9][9]; // Pointer array that points to all States
QueueSet queue;
int whiteSpaces = 0;


void createLinks(State * state, int row, int col)
{
	// Create row and col links
	for (int i = 0; i < 9; i++)
	{
		if (col != i) // Do not make a pointer to myself
		{
			Link tmp = Link(states[row][col], states[row][i]); // Tail: This, Head: Other
			queue.push(tmp);
		}
		if (row != i) // Do not make a pointer to myself
		{
			Link tmp = Link(states[row][col], states[i][col]); // Tail: This, Head: Other
			queue.push(tmp);
		}
	}
	int rowB, colB;
	rowB = row / 3; // Implicit floor
	colB = col / 3; // Implicit floor
	rowB *= 3;
	colB *= 3;

	for (int i = rowB; i < (rowB + 3); i++)
	{
		for (int j = colB; j < (colB + 3); j++)
		{
			if (i != row && j != col)
			{
				Link tmp = Link(states[row][col], states[i][j]); // Tail: This, Head: Other
				queue.push(tmp);
			}
		}
	}

}

void initializeStates(const int sudoku[9][9])
{
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++)
		{
			int tmp = sudoku[i][j];
			// We save the new State pointer
			states[i][j] = new State(tmp, i, j);
		}
	}

	// We cannot merge this for loop with the upper one, because the states are initilized on NULL
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++)
		{
			State * tmpState = states[i][j];
			// If the state is initial we don't check dependencies, solvable sudokus is assumed
			if (!tmpState->isInitial())
			{
				createLinks(tmpState, i, j);
				whiteSpaces++;
			}
		}
	}

}

bool removeInconsistentValues(Link link)
{
	bool removed = false;
	State * tail = link.getTail();
	State * head = link.getHead();

	for (int i = 0; i < 9; i++)
	{
		if (tail->numberAvailable(i))
		{
			if (head->isInitial())
			{
				tail->removeFromDomain(head->assignedValue());
			}
		}
	}
	return removed;
}

// Like upper implementation but swapped
void addNeighborsToQueueOf(State * state)
{
	int row = state->getRow();
	int col = state->getCol();
	// Create row and col links
	for (int i = 0; i < 9; i++)
	{
		if (col != i) // Do not make a pointer to myself
		{
			if (states[row][i]->isInitial()) continue;
			Link tmp = Link(states[row][i], states[row][col]); // Tail: This, Head: Other
			queue.push(tmp);
		}
		if (row != i) // Do not make a pointer to myself
		{
			if (states[i][col]->isInitial()) continue;
			Link tmp = Link(states[i][col], states[row][col]); // Tail: This, Head: Other
			queue.push(tmp);
		}
	}
	int rowB, colB;
	rowB = row / 3; // Implicit floor
	colB = col / 3; // Implicit floor
	rowB *= 3;
	colB *= 3;

	for (int i = rowB; i < (rowB + 3); i++)
	{
		for (int j = colB; j < (colB + 3); j++)
		{
			if (i != row && j != col)
			{
				if (states[i][j]->isInitial()) continue;
				Link tmp = Link(states[i][j], states[row][col]); // Tail: This, Head: Other
				queue.push(tmp);
			}
		}
	}
}

void arcConsistency()
{
	while (queue.size() > 0)
	{
		Link link = queue.pop();
		if (removeInconsistentValues(link))
		{
			addNeighborsToQueueOf(link.getTail());
		}
	}
}

void solveCSP(const int sudoku[][9]){
	initializeStates(sudoku);
	arcConsistency();
}

int main(){
	/*
	 <program>  Copyright (C) <year>  <name of author>

    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
    This is free software, and you are welcome to redistribute it
    under certain conditions; type `show c' for details.
	*/
	printf("Iniciando simulación de CSP\n");
	int sudoku[9][9];
	for(int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++)
		{
			scanf_s("%d", &sudoku[i][j]);
		}
	}
	solveCSP(sudoku);
	printf("Espacios vacios: %d Tamano:%d", whiteSpaces * 20, queue.size());
	return 0;
}