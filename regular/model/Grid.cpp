
#include "Grid.h"

Grid::Grid()
{
	for (int i = 0; i < 9; i++)
	{
		
			grid[i] = "-";
		
	}
}


Grid::~Grid()
{
}



 string* Grid::getGrid()
{
	return grid;
}

 void Grid::setGrid(string * grid_input)
 {
	 for (int i = 0; i < 9; i++)
	 {
		 grid[i] = grid_input[i];
	 }
 }


 void Grid::setMarkNum(int num)
 {
	 markNum = num;
 }

 int Grid::getMarkNum() {
	 return markNum;
}

 void Grid::addMarkNum() {
	 markNum++;
 }

 void Grid::clear()
 {
	 for (int i = 0; i < 9; i++)
	 {

		 grid[i] = "-";

	 }
	 markNum = 0;
 }
