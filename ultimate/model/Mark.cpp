#include "Mark.h"




Mark::Mark(int position_input, string role_input)
{	
	position = position_input;
	role = role_input;
}


Mark::~Mark()
{
}

int Mark::getPosition()
{
	return position;
}

string Mark::getRole()
{
	return role;
}



void Mark::setPosition(int position_input)
{
	position = position_input;
}

void Mark::setRole(string role_input)
{
	role = role_input;
}
