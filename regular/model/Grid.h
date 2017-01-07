#pragma once
#include <string>
using namespace std;

class Grid
{
private:
	string grid[9];

	//store the number of markers on board 
	int markNum=0;
public:
	Grid();

	~Grid();


	string* getGrid();
	void setGrid(string *grid_input);

	//clear the game board
	void clear();

	int getMarkNum();

	void addMarkNum();
	void setMarkNum(int num);

};

