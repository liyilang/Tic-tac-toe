#pragma once
typedef int(*rules_2d)[3];
class winRules
{
private: 
	int rules[8][3] = {
		{ 0,1,2 },
		{ 3,4,5 },
		{ 6,7,8 },
		{ 0,3,6 },
		{ 1,4,7 },
		{ 2,5,8 },
		{ 0,4,8 },
		{ 2,4,6 }
	};
public:
	winRules();
	~winRules();
	rules_2d getRules();
	 
};

