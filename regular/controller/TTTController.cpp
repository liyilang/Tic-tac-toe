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
	vector<string> json = reader.parseJson(playerJsonObject);
	string name = json.at(1);
	string marker = json.at(3);
	string::size_type sz;
	int playerNum = stoi(json.at(5),&sz);
	createPlayer(name, marker, playerNum);
	if (playerNum == 1) {
		playerDAOImpl dao;
		dao.savePlayer(player1);
	}

	if (playerNum == 2) {
		playerDAOImpl dao;
		dao.savePlayer(player2);
	}

}

void TTTController::startNewGame()
{	
	grid.clear();
	player1.getStrategy().clear();
	player2.getStrategy().clear();
	currentPlayer = 1;
	setGrid();
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
	vector<string> json = reader.parseJson(gameJsonObject);
	string::size_type sz;
	int row = stoi(json.at(1), &sz);
	int col = stoi(json.at(3), &sz);
	int player = stoi(json.at(5), &sz);
	getGrid();
	bool result=setSelection(row,col,player);
	if (result)
		setGrid();
	return result;
}

int TTTController::determineWinner()
{ 
	int (*r)[3] = rules.getRules();

	string *g = grid.getGrid();

	for (int row = 0; row < 8; ++row)
	{	
		if ((g[r[row][0]] != "-") &&
			(g[r[row][0]] == g[r[row][1]]) &&
			(g[r[row][1]] == g[r[row][2]]))
		{
			if (g[r[row][0]]== player1.getRole()) {
				return 1;
			}
			else {
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
	getGrid();
	string *g = grid.getGrid();
	string output = "{\"gameBoard\":[";
	for (int i = 0; i < 9; i++)
	{
		output = output + "{\"row\":"+to_string(i/3)+",\"col\":"+to_string(i%3)+",\"marker\":\""+g[i]+"\"}";
		if (i!=8) {
			output = output + ",";
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
 
