#include <iostream>
#include <string>
#include <sstream>
#include "controller/TTTController.h"
#include "model/JsonReader.h"
#include "model/GridDAOImpl.h"
#include "/group/course/cpsc8700/lib/rapidjson-master/include/rapidjson/document.h"
#include "/group/course/cpsc8700/lib/rapidjson-master/include/rapidjson/writer.h"
#include "/group/course/cpsc8700/lib/rapidjson-master/include/rapidjson/stringbuffer.h"
using namespace std;

void instruction() {
	cout << "Please read the instruction below:\nThe object of Tic Tac Toe is to get three in a row.\nYou play on a three by three game board. The first player is known as X and the second is O.\nPlayers alternate placing Xs and Os on the game board until either oppent has three in a row \nor all nine squares are filled.X always goes first,and in the event that no one has three\nin a row,the stalemate is called a cat game.\nWarning:row and column are range from 0-2." << endl;
	cout << "START NEW GAME (Y/N)£¿ ";
}



int main()
{

	cout << "content-type: text/html\n\n";
	stringstream post;
	post << std::cin.rdbuf();
	string incomingJsonObjectString = post.str();
	//const char incomingJsonObjectString [] = "{\"controllerMethod\":\"setSelection\",\"player\":{\"name\":\"jason\",\"marker\":\"S\",\"playNum\":1},\"input\":{\"row\":2,\"col\":0,\"outerRow\":0,\"outerCol\":0,\"currentPlayer\":1}}";
	//const char incomingJsonObjectString[] = "{\"controllerMethod\":\"setSelection\",\"player\":{\"name\":\"jason\",\"marker\":\"J\",\"playNum\":2},\"input\":{\"row\":0,\"col\":2,\"outerRow\":0,\"outerCol\":0,\"currentPlayer\":2}}";
	//const char incomingJsonObjectString[] = "{\"controllerMethod\":\"createPlayer\",\"player\":{\"name\":\"seth\",\"marker\":\"s\",\"playNum\":1},\"input\":{\"name\":\"seth\",\"marker\":\"s\",\"playNum\":1}}";
	rapidjson::Document document;
	document.Parse(incomingJsonObjectString.c_str());
	rapidjson::Value& methodStr = document["controllerMethod"];
	rapidjson::Value& nameStr = document["player"]["name"];
	rapidjson::Value& roleStr = document["player"]["marker"];
	rapidjson::Value& numStr = document["player"]["playNum"];


	string method(methodStr.GetString());

	string name(nameStr.GetString());
	string role(roleStr.GetString());
	int currentPlayer = numStr.GetInt();

	TTTController controller;
	controller.setCurrentPlayer(currentPlayer);
	controller.createPlayer(name, role, currentPlayer);
	if (method == "setSelection")
	{
		rapidjson::Value& inputStr = document["input"];
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		inputStr.Accept(writer);
		bool setResult = controller.setSelection(buffer.GetString());
		cout << setResult;
	}
	else if (method == "getAllPlayers") {
		string players = controller.getAllSavedPlayers();
		cout << players;
	}
	else if (method == "determineSubWinner") {
		rapidjson::Value& gridNumStr = document["input"]["gridNum"];
		int gridNum = gridNumStr.GetInt();
		int result = controller.determineSubWinner(gridNum);
		cout << result;
	}
	else if (method == "determineWinner") {
		nameStr = document["player2"]["name"];
		roleStr = document["player2"]["marker"];
		numStr = document["player2"]["playNum"];
		name = nameStr.GetString();
		role = roleStr.GetString();
		currentPlayer = numStr.GetInt();
		controller.createPlayer(name, role, currentPlayer);
		int result = controller.determineWinner();
		cout << result;
	}
	else if (method == "startNewGame") {
		controller.startNewGame();
	}
	else if (method == "createPlayer") {
		rapidjson::Value& inputStr = document["input"];
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		inputStr.Accept(writer);
		controller.createPlayer(buffer.GetString());
	}
	else if (method == "getGameDisplay") {
		controller.getGameDisplay(true);
	}

}