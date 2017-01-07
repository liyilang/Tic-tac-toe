#include "GridDAOImpl.h"


GridDAOImpl::GridDAOImpl()
{
}


GridDAOImpl::~GridDAOImpl()
{
}

string * GridDAOImpl::getGrid()
{
	file.open(path,ios::in);
	string tmp;
	getline(file, tmp);
	char * cstr = new char[tmp.length() + 1];
	strcpy(cstr, tmp.c_str());
	char * pch;
	pch = strtok(cstr, ",");
	
	int i = 0;
	while (pch != NULL)
	{
		string temp(pch);
		grid[i++]=temp;
		pch = strtok(NULL, ",");
	}
	file.close();
	return grid;
}

void GridDAOImpl::setGrid(string *grid_input)
{	
	file.open(path, ios::out);
	string *g = grid_input;
	string input = "";
	for (int i = 0; i < 9; i++)
	{
		input = input + g[i];
		if (i != 8)
			input = input + ",";
	}
	file << input << endl;
	file.close();
}
