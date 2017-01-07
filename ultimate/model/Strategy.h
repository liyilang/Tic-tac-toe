#pragma once
#include <iostream>
#include <list>
#include "Mark.h"
using namespace std;

class Strategy
{
private:
	list<Mark> strategy;
public:
	Strategy();
	~Strategy();
	void setStrategy(Mark mark_input);
	list<Mark> getStratety();
	void clear();
};

