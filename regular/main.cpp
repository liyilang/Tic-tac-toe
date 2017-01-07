#include <iostream>
#include <string>
#include <sstream>
#include "controller/TTTController.h"
#include "model/JsonReader.h"
#include "model/GridDAOImpl.h"
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
	JsonReader reader;
	//string incomingJsonObjectString = "{\"controllerMethod\":\"determineWinner\",\"player\":{\"name\":\"jason\",\"marker\":\"J\",\"playnum\":2},\"input\":{\"row\":1,\"col\":2,\"playnum\":1}}";
	vector<string> json = reader.parseJson(incomingJsonObjectString);
	string method = json.at(1);
	TTTController controller;	
	string name = json.at(4);
	string role = json.at(6);
	int currentPlayer = stoi(json.at(8));
	
	controller.setCurrentPlayer(currentPlayer);
	controller.createPlayer(name, role, currentPlayer);
	if (method=="setSelection")
	{	
		string input=",";
		int size = json.size();
		for (int i = 10; i < size; i++)
		{
			input = input + json.at(i)+",";
		}
		bool setResult = controller.setSelection(input);
		cout << setResult;
	}
	else if (method=="getAllPlayers") {
		string players = controller.getAllSavedPlayers();
		cout << players;
	}
	else if (method == "determineWinner") {
		controller.getGrid();
		int result = controller.determineWinner();
		cout << result;
	}
	else if (method == "startNewGame") {
		controller.startNewGame();
	}
	else if (method=="createPlayer") {
		string input=",";
		int size = json.size();
		for (int i = 10; i < size; i++)
		{
			input = input + json.at(i)+",";
		}
		controller.createPlayer(input);
	}
	

	
	
	/*instruction();
	char startGame;
	cin >> startGame;
	if ((startGame != 'Y')&&(startGame!='y'))
		return 0;
	TTTController controller;
	string name1;
	string role1;
	string name2;
	string role2;
	cout << "Please input player1 name:";
	cin >> name1;
	cout << "Please input player1 marker:";
	cin >> role1;
	controller.createPlayer(name1, role1, 1);
	cout << "Please input player2 name:";
	cin >> name2;
	cout << "Please input player2 marker:";
	cin >> role2;
	while (role2 == role1) {
		cout << "Same marker,Please input player2 marker again:";
		cin >> role2;
	}
	controller.createPlayer(name2, role2, 2);
	cout <<"\nGame board belows\n"+ controller.getGameDisplay()+"\nplayer1 turn" << endl;
	int row, col;
	
	while (true) {
		int currentPlayer = controller.getCurrentPlayer();
		cout << "Please input the row number:";
		cin >> row;
		cout << "Please input the column number:";
		cin >> col;
		if (((row > 2) || (col > 2))||((row <0) || (col <0))) {
			cout << "\nWrong location! Range 0-2, Please enter again\n";
			continue;
		}
		if (!controller.setSelection(row, col, currentPlayer)) {
			cout << "\nThis location is used, please change\n";
			continue;
		}
		cout << "\nYour step\n" + controller.getGameDisplay() + "\n" << endl;
		int result = controller.determineWinner();
		if (result == 1||result == 2) {
			cout << "Congratulations! You win\nwant to start a new game? (Y/N):";
			cin >> startGame;
			if ((startGame != 'Y') && (startGame != 'y'))
				break;
			else {
				controller.startNewGame();
				cout << "\nGame board belows\n" + controller.getGameDisplay() + "\nyour turn" << endl;
				continue;
			}
			
		}
		else if (result == 3) {
			cout << "Nobody wins\nwant to start a new game? (Y/N):";
			cin >> startGame;
			if ((startGame != 'Y') && (startGame != 'y'))
				break;
			else {
				controller.startNewGame();
				cout << "\nGame board belows\n" + controller.getGameDisplay() + "\nyour turn" << endl;
				continue;
			}
		}
		else
			continue;

	}*/
	
}



