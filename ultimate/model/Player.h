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
	int uwin;
	int ulose;
	int utie;
	int win;
	int lose;
	int tie;
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

	int getUwin();

	int getUlose();

	int getUtie();

	int getWin();

	int getLose();

	int getTie();
	
	void setUwin(int win_input);

	void setUlose(int lose_input);

	void setUtie(int tie_input);

	void setWin(int win_input);

	void setLose(int lose_input);

	void setTie(int tie_input);
};

