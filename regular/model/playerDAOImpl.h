#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "Player.h"
using namespace std;
class playerDAO {
public:
	~playerDAO();
	virtual void savePlayer(Player player)=0;
	virtual string getPlayers()=0;
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
};

