#include "Player.h"



Player::Player()
{
}

Player::Player(string name_input, string role_input, int playNum)
{
	name = name_input;
	role = role_input;
	num = playNum;
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
