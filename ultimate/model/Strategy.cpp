#include "Strategy.h"



Strategy::Strategy()
{
}


Strategy::~Strategy()
{
}

void Strategy::setStrategy(Mark mark_input)
{
	strategy.push_back(mark_input);
}

list<Mark> Strategy::getStratety()
{
	return strategy;
}

void Strategy::clear()
{
	strategy.clear();
}
