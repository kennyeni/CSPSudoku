// Author: Andres Duran <contact@ekenny.org>
// Sudoku constraint satisfaction implementation
// State head
class State
{
	bool * dominio;
	bool initial;
	int assignedNumber;
	int row, col;
public:
	State(int, int, int);
	~State();
	bool numberAvailable(int);
	bool isInitial();
	int getRow();
	int getCol();
	void removeFromDomain(int);
	int assignedValue();
};