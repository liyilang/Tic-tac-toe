#include "Player.h"



Player::Player()
{
}

Player::Player(string name_input, string role_input, int playNum)
{
	name = name_input;
	role = role_input;
	num = playNum;
	uwin = 0;
	ulose = 0;
	utie = 0;
	win = 0;
	lose = 0;
	tie = 0;
}


Player::~Player()
{
}

void Player::setName(string name_input)
{
	name = name_input;
}

string Player::getName()
{
	return name;
}

void Player::setRole(string role_input)
{
	role = role_input;
}

string Player::getRole()
{
	return role;
}

void Player::setStrategy(Mark mark_input)
{
	strategy.setStrategy(mark_input);
}

Strategy Player::getStrategy()
{
	return strategy;
}

void Player::setNum(int playNum)
{
	num = playNum;
}

int Player::getNum()
{
	return num;
}

int Player::getUwin()
{
	return uwin;
}

int Player::getUlose()
{
	return ulose;
}

int Player::getUtie()
{
	return utie;
}

int Player::getWin()
{
	return win;
}

int Player::getLose()
{
	return lose;
}

int Player::getTie()
{
	return tie;
}

void Player::setUwin(int win_input)
{
	uwin = win_input;
}

void Player::setUlose(int lose_input)
{
	ulose = lose_input;
}

void Player::setUtie(int tie_input)
{
	utie = tie_input;
}

void Player::setWin(int win_input)
{
	win = win_input;
}

void Player::setLose(int lose_input)
{
	lose = lose_input;
}

void Player::setTie(int tie_input)
{
	tie = tie_input;
}


bool Player::setSelection(Grid& grid_input,int location, string role)
{
	string *grid = grid_input.getGrid();
	if (grid[location] == "-")
	{
		grid[location] = role;
		grid_input.addMarkNum();
		Mark mark(location, role);
		setStrategy(mark);
		return true;
	}
	else {
		return false;
	}
}
