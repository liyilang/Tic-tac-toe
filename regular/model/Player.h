#pragma once
#include <string.h>
#include "Strategy.h"
#include "Mark.h"
#include "Grid.h"
using namespace std;
class Player
{

protected :
	string name;
	string role; 
	int num;
	Strategy strategy;//store the steps that player takes

public:
	Player();
	Player(string name_input, string role_input, int playNum);
	~Player();

	void setName(string name_input);

	string getName();

	void setRole(string role_input);

	string getRole();

	void setStrategy(Mark mark_input);

	Strategy getStrategy();

	bool setSelection(Grid& grid, int location, string role);

	void setNum(int playNum);

	int getNum();
};

