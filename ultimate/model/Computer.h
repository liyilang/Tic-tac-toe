#pragma once
#include "Player.h"
class Computer :
	public Player
{
public:
	Computer();
	~Computer();
	bool PCsetSelection(Grid& grid, int location
	);
};

