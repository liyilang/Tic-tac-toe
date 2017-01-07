#include "JsonReader.h"


JsonReader::JsonReader()
{
}


JsonReader::~JsonReader()
{
}
 vector<string> JsonReader::parseJson(string json) {
	
	//json = "{\"controllerMethod\":{\"name\":\"add\"},\"player\":{\"name\":\"John Johnson\",\"marker\":16}}";
	 vector<string> jsonVector;
	 char * cstr = new char[json.length() + 1];
	std::strcpy(cstr, json.c_str());
	char * pch;
	pch = strtok(cstr, "\":{,}");
	while (pch != NULL)
	{	
		string temp(pch);
		jsonVector.push_back(temp);
		pch = strtok(NULL, "\":{,}");
	}
	return jsonVector;
}


	