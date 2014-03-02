// Algorithm main point of entry
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


#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

#ifndef STATE_H
#define STATE_H
#include "State.h"
#endif

#ifndef LINK_H
#define LINK_H
#include "Link.h"
#endif

#ifndef ASSERT_H
#define SSERT_H
#include <assert.h>
#endif

#include "QueueSet.h"

typedef std::priority_queue<State, std::vector<State>, StateCompare> priorityQueue;

State * states[9][9]; // Pointer array that points to all States

void createLinks(QueueSet * queue, State * state, int row, int col)
{
	// Create row and col links
	for (int i = 0; i < 9; i++)
	{
		if (col != i) // Do not make a pointer to myself
		{
			Link tmp = Link(states[row][col], states[row][i]); // Tail: This, Head: Other
			queue->push(tmp);
		}
		if (row != i) // Do not make a pointer to myself
		{
			Link tmp = Link(states[row][col], states[i][col]); // Tail: This, Head: Other
			queue->push(tmp);
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
				queue->push(tmp);
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
}

QueueSet * initialLinks(){
	QueueSet * queue = new QueueSet;
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++)
		{
			State * tmpState = states[i][j];
			// If the state is initial we don't check dependencies, solvable sudokus is assumed
			if (!tmpState->isFinal())
			{
				createLinks(queue, tmpState, i, j);
			}
		}
	}
	return queue;
}

// Removes the invalid values of the domain of the tail, true is it has removed something at all
bool removeInconsistentValues(Link link)
{
	bool removed = false;
	State * tail = link.getTail();
	State * head = link.getHead();

	for (int i = 1; i <= 9; i++)
	{
		A:if (!tail->numberAvailable(i))
			continue;
		for (int j = 1; j <= 9; j++)
		{
			if (i != j && head->numberAvailable(j)){
				i++;
				goto A;
			}
		}
		tail->removeFromDomain(i);
		removed = true;
	}
	return removed;
}

// Like upper implementation but swapped
void addNeighborsToQueueOf(QueueSet * queue, State * state)
{
	int row = state->getRow();
	int col = state->getCol();
	// Create row and col links
	for (int i = 0; i < 9; i++)
	{
		if (col != i) // Do not make a pointer to myself
		{
			if (states[row][i]->isFinal()) continue;
			Link tmp = Link(states[row][i], states[row][col]); // Tail: This, Head: Other
			queue->push(tmp);
		}
		if (row != i) // Do not make a pointer to myself
		{
			if (states[i][col]->isFinal()) continue;
			Link tmp = Link(states[i][col], states[row][col]); // Tail: This, Head: Other
			queue->push(tmp);
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
				if (states[i][j]->isFinal()) continue;
				Link tmp = Link(states[i][j], states[row][col]); // Tail: This, Head: Other
				queue->push(tmp);
			}
		}
	}
}

// Returns true if this path is still good, if this path should be forgotten returns false
bool arcConsistency(QueueSet * queue)
{
	while (queue->size() > 0)
	{
		Link link = queue->pop();
		if (removeInconsistentValues(link))
		{
			if (link.getTail()->isDirty())
			{
				printf_s("Wrong solution found");
				return false;
			}
			addNeighborsToQueueOf(queue, link.getTail());
		}
	}
	// The queue is empty so we can free it
	free(queue);
	return true;
}


void printIfReady(){
	printf("\n");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int val = states[i][j]->assignedValue();
			printf("%d ", val);
		}
		printf("\n");
	}

}

// Finalize values
void consolidateStates()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (states[i][j]->assignedValue() > 0)
			{
				states[i][j]->consolidate();
			}
		}
	}
}

void preprocessing(const int sudoku[][9])
{
	// Creates the states
	initializeStates(sudoku);
	// Creates all Possible Initial Links(Tail: unassigned H : unassigned / assigned)
	QueueSet * queue = initialLinks();
	// Initial consistency
	if (!arcConsistency(queue))
	{
		printf("Unsolvable sudoku!");
	}
	// Since the previous preprocessing is warranted to be true (if a solvable sudoku was given), we consolidate them
	consolidateStates();
}

bool recursiveBacktrack(priorityQueue queue)
{
	if (queue.empty())
		return true;
	return false;
}

bool bactrackSearch()
{
	// Add blank spaces to the list of vars that need to be assigned
	// This queue gives priority to smaller domain states, so we try to assign them first
	priorityQueue queue;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (!states[i][j]->isFinal())
			{
				assert(states[i][j]->assignedValue() == 0);
				assert(!states[i][j]->isDirty());
				queue.push(*states[i][j]);
			}
		}
	}
	State r = queue.top();
	return recursiveBacktrack(queue);
}

void solveCSP(const int sudoku[][9]){
	// First filtering
	preprocessing(sudoku);
	bactrackSearch();

	printIfReady();
}

int main(){
	
	printf_s("CSP Sudoku Solver  Copyright (C) 2014  Andres Duran <contact@ekenny.org>\n\nThis program comes with ABSOLUTELY NO WARRANTY;\nThis is free software, and you are welcome to redistribute it\nunder certain conditions; \n\n");

	printf("Enter your sudoku (plain-text)\n");
	int sudoku[9][9];
	for(int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++)
		{
			scanf_s("%d", &sudoku[i][j]);
		}
	}
	printf_s("\nSolution:");
	solveCSP(sudoku);
	return 0;
}