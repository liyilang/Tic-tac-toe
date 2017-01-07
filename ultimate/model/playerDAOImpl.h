#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "Player.h"
#include "/group/course/cpsc8700/lib/rapidjson-master/include/rapidjson/rapidjson.h"
#include "/group/course/cpsc8700/lib/rapidjson-master/include/rapidjson/document.h"
#include "/group/course/cpsc8700/lib/rapidjson-master/include/rapidjson/reader.h"
#include "/group/course/cpsc8700/lib/rapidjson-master/include/rapidjson/writer.h"
#include "/group/course/cpsc8700/lib/rapidjson-master/include/rapidjson/stringbuffer.h"
using namespace std;
class playerDAO {
public:
	~playerDAO();
	virtual void savePlayer(Player player)=0;
	virtual string getPlayers()=0;
	virtual void updatePlayer(Player player, string grade)=0;

};


class playerDAOImpl:public playerDAO
{
public:
	fstream file;
	string path="players.txt";
	playerDAOImpl();
	~playerDAOImpl();
	void savePlayer(Player player);
	string getPlayers();
	void updatePlayer(Player player, string grade);
};

