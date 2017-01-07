#include <string.h>
#include <stdlib.h>
#include "TTTController.h"
using namespace std;

void TTTController::createPlayer(string name, string marker, int playerNum = 1)
{
	if (playerNum == 1) {
		player1.setName(name);
		player1.setRole(marker);
		player1.setNum(playerNum);
	}
	
	if (playerNum == 2) {
		player2.setName(name);
		player2.setRole(marker);
		player2.setNum(playerNum);
	}

}

void TTTController::createPlayer(string playerJsonObject)
{	
	string name;
	string marker;
	int playerNum;
	rapidjson::Document document;
	document.Parse(playerJsonObject.c_str());
	rapidjson::Value& nameStr = document["name"];
	name = nameStr.GetString();
	rapidjson::Value& roleStr = document["marker"];
	marker = roleStr.GetString();
	if (document.HasMember("playerNum")) {
		rapidjson::Value& numStr = document["playerNum"];
		playerNum = numStr.GetInt();
	}
	else {
		playerNum = 1;
	}
	createPlayer(name, marker, playerNum);
	if (playerNum == 1) {
		playerDAOImpl pdao;
		pdao.savePlayer(player1);
	}

	if (playerNum == 2) {
		playerDAOImpl pdao;
		pdao.savePlayer(player2);
	}

}

void TTTController::startNewGame()
{	
	grid.clear();
	player1.getStrategy().clear();
	player2.getStrategy().clear();
	currentPlayer = 1;
	for (int i = 0; i < 10;i++) {
		string path = "grid" + to_string(i)+ ".txt";
		dao.setPath(path);
		setGrid();
	}
	
}

bool TTTController::setSelection(int row, int col, int currentPlayer)
{	
	bool status = false;
	if (((row > 2) || (col > 2)) || ((row <0) || (col <0)))
		return status;
	int location = row * 3 + col;

	if (currentPlayer == 1) {
		status = player1.setSelection(grid, location, player1.getRole());
		if (status)
			setCurrentPlayer(2);
	}
	else if (currentPlayer == 2) {
		status = player2.setSelection(grid, location, player2.getRole());
		if (status)
			setCurrentPlayer(1);
	}

	return status;  
}

bool TTTController::setSelection(string gameJsonObject)
{
	rapidjson::Document document;
	document.Parse(gameJsonObject.c_str());
	rapidjson::Value& rowStr = document["row"];
	rapidjson::Value& colStr = document["col"];
	rapidjson::Value& playerStr = document["int"];
	rapidjson::Value& outerRowStr = document["outerRow"];
	rapidjson::Value& outerColStr = document["outerCol"];
	int row = rowStr.GetInt();
	int col = colStr.GetInt();
	int player = playerStr.GetInt();
	int outerRow = outerRowStr.GetInt();
	int outerCol = outerColStr.GetInt();
	int filePath = outerRow * 3 + outerCol;
	string path = "grid" + to_string(filePath) + ".txt";
	dao.setPath(path);
	getGrid();
	bool result=setSelection(row,col,player);
	if (result) {
		setGrid();
		determineSubWinner(filePath);
	}
	return result;
}

int TTTController::determineWinner()
{ 

	dao.setPath("grid9.txt");
	int (*r)[3] = rules.getRules();
	getGrid();
	string *g = grid.getGrid();

	for (int row = 0; row < 8; ++row)
	{	
		
		if ((g[r[row][0]] != "-") &&
			(g[r[row][0]] == g[r[row][1]]) &&
			(g[r[row][1]] == g[r[row][2]]))
		{
			if (g[r[row][0]]== player1.getRole()) {
				playerDAOImpl pdao;
				pdao.updatePlayer(player1, "uwin");
				pdao.updatePlayer(player2, "ulose");
				return 1;
			}
			else {
				playerDAOImpl pdao;
				pdao.updatePlayer(player2, "uwin");
				pdao.updatePlayer(player1, "ulose");
				return 2;
			}
		}
		
	}
	if (grid.getMarkNum() == 9) {
		playerDAOImpl pdao;
		pdao.updatePlayer(player1, "utie");
		pdao.updatePlayer(player2, "utie");
		return 3;
	}
	else
	{
		return 0;
	}
	
}

int TTTController::determineSubWinner(int gridNum)
{
	
	int(*r)[3] = rules.getRules();

	for (int row = 0; row < 8; ++row)
	{
		string path = "grid" + to_string(gridNum) + ".txt";
		dao.setPath(path);
		getGrid();
		string *g = grid.getGrid();
		if ((g[r[row][0]] != "-") &&
			(g[r[row][0]] == g[r[row][1]]) &&
			(g[r[row][1]] == g[r[row][2]]))
		{	
			
			if (g[r[row][0]] == player1.getRole()) {
				dao.setPath("grid9.txt");
				getGrid();
				setSelection(gridNum / 3, gridNum % 3, 1);
				setGrid();
				return 1;
			}
			else {
				dao.setPath("grid9.txt");
				getGrid();
				setSelection(gridNum / 3, gridNum % 3, 2);
				setGrid();
				return 2;
			}
		}

	}
	if (grid.getMarkNum() == 9) {
		return 3;
	}
	else
	{
		return 0;
	}
}

string TTTController::getGameDisplay()
{
	string *g = grid.getGrid();
	string output="";


		for (int i = 0; i < 9; i++)
		{
			output = output + g[i] + "|";
			if ((i + 1) % 3 == 0) {
				output = output + "\n";
			}
			
		}
			
	return output;
}

string TTTController::getGameDisplay(bool isJson)
{	
	if (!isJson) {
		return getGameDisplay();
	}
	
	string output = "{\"gameBoard\":[";
	for (int i = 0; i < 9;i++) {
		string path = "grid" + to_string(i) + ".txt";
		dao.setPath(path);
		getGrid();
		string *g = grid.getGrid();
		for (int j = 0; j < 9; j++)
		{
			output = output + "{\"row\":"+to_string(j/3)+",\"col\":"+to_string(j%3)+",\"marker\":\""+g[j]+"\",\"grid\":"+to_string(i)+"}";
			if (!(i==8&&j==8)) {
				output = output + ",";
			}

		}
	}
	output = output + "]}";
	return output;
}

string TTTController::getAllSavedPlayers()
{
	playerDAOImpl dao;
	string allPlayers="{\"players\":[";
	allPlayers= allPlayers+dao.getPlayers()+"]}";
	return allPlayers;
}

int TTTController::getCurrentPlayer() {
	return currentPlayer;
}

void TTTController::setCurrentPlayer(int num) {
	currentPlayer= num;
}

void TTTController::setGrid()
{
	
	dao.setGrid(grid.getGrid());
}

void TTTController::getGrid()
{
	grid.setGrid(dao.getGrid());
	int num = 0;
	string *g = grid.getGrid();
	for (int i=0;i<9;i++)
	{
		if (g[i] != "-")
			num++;
	}
	grid.setMarkNum(num);
}
 
