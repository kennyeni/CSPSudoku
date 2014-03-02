// Author: Andres Duran <contact@ekenny.org>
// Sudoku constraint satisfaction implementation
// State head
class State
{
	bool * dominio;
	bool initial;
	int assignedNumber;
public:
	State(int);
	~State();
	bool numberUsed(int);
	bool isInitial();
};