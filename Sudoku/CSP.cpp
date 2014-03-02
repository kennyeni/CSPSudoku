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

#ifndef STATE_H
#define STATE_H
#include "State.h"
#endif

#include "Link.h"
#include "QueueSet.h"

State * states[9][9]; // Arreglo de apuntadores a los estados
QueueSet<Link> queue;


void createLinks(State * state, int i, int j)
{
	Link tmp = Link(states[i][i], states[i][i]);
	queue.push(tmp);
	bool ex = queue.contains(tmp);
	ex = ex;
}

void initializeStates(const int sudoku[9][9])
{
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++)
		{
			int tmp = sudoku[i][j];
			// Nuevo estado, se almacena su apuntador
			State * tmpState = states[i][j] = new State(tmp);
			
			// Si es inicial no es necesario poner dependencias, se asume que estan bien
			if (! tmpState->isInitial()) 
			{
				createLinks(tmpState, i, j);
			}
		}
	}
}

void solveCSP(const int sudoku[][9]){
	initializeStates(sudoku);

	
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
	return 0;
}