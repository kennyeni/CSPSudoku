// Class that represent each sudoku cell
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

class State
{
	bool * _domain;
	int _domainSize;
	bool _final;
	bool _dirty;
	bool _forced;
	int _assignedNumber;
	int _row, _col;
public:
	static void copyStateArray(State * a[][9], State * b[][9]);
	static bool compareTo(State& a, State& b);

	State(int, int, int);
	State(const State&);

	bool numberAvailable(int);
	int getRow();
	int getCol();
	void removeFromDomain(int);
	int assignedValue();
	void consolidate();
	bool isDirty();
	bool isForced();
	bool isFinal();
	void forceAssignment(int);
};

// Helper struct to compare two functions
struct StateCompare {
	bool operator() (State& a, State& b) const {
		return State::compareTo(a, b);
	}
};