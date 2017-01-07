#pragma once
#include <string>
using namespace std;

class Mark
{
private:
	int position;
	string role;
public:
	Mark(int position_input, string role_input);
	~Mark();
	int getPosition();

	string getRole();

	void setPosition(int position_input);

	void setRole(string role_input);
	
};

