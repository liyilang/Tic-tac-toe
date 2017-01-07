#pragma once
#include <string>
#include <fstream>
#include <cstring>
using namespace std;
class GridDAO {
public:
	virtual string* getGrid() = 0;
	virtual void setGrid(string* grid) = 0;
};

class GridDAOImpl:public GridDAO
{
public:
	string grid[9];
	string path="grid9.txt";
	fstream file;
	GridDAOImpl();
	~GridDAOImpl();
	string* getGrid();
	void setGrid(string* grid);
	void setPath(string path_input);
	
};

