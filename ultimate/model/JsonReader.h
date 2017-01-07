#pragma once
#include <string.h>
#include <cstring>
#include <map>
#include <iostream>
#include <vector>
using namespace std;
class JsonReader
{
public:
	JsonReader();
	~JsonReader();
	static vector<string> parseJson(string json);
};

