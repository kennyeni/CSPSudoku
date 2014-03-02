// Author: Andres Duran <contact@ekenny.org>
// Sudoku constraint satisfaction implementation
// State head
class State
{
	bool * _domain;
	int _domainSize;
	bool _final;
	int _assignedNumber;
	int _row, _col;
public:
	State(int, int, int);
	~State();
	bool numberAvailable(int);
	bool isFinal();
	int getRow();
	int getCol();
	void removeFromDomain(int);
	int assignedValue();
	void consolidate();
};