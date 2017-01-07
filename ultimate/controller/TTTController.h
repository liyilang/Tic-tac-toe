#include <string.h>
#include "../model/Player.h"
#include "../model/Computer.h"
#include "../model/Grid.h"
#include "../model/winRules.h"
#include "../model/Mark.h"
#include "../model/JsonReader.h"
#include "../model/playerDAOImpl.h"
#include "../model/GridDAOImpl.h"
#include "/group/course/cpsc8700/lib/rapidjson-master/include/rapidjson/document.h"
#include "/group/course/cpsc8700/lib/rapidjson-master/include/rapidjson/writer.h"
#include "/group/course/cpsc8700/lib/rapidjson-master/include/rapidjson/stringbuffer.h"
using namespace std;



class TTTController
{
private:
	Player player1;
	Player player2;
	int currentPlayer=1;
	string playerFile = "player.txt";
	

public:
	
	GridDAOImpl dao;

	Grid grid;

	winRules rules;

	JsonReader reader;

	void createPlayer(string name, string marker, int playerNum );

	void createPlayer(string playerJsonObject);

	void startNewGame();

	bool setSelection(int row, int col, int currentPlayer);
	
	bool setSelection(string gameJsonObject);
	// row and col: have to be valid, between 0-2
	// currentPlayer: 1=player1; 2=player2
	//return bool: valid and available location

	int determineWinner();

	int determineSubWinner(int grid);
	//return winner;
	//0= no winner; 1=player1; 2=player2;
	//3 = tie / no more available locations
	
	string getGameDisplay();

	string getGameDisplay(bool isJson);
	//printable display of current selections;
	//shows each players marker

	string getAllSavedPlayers();

	int getCurrentPlayer();
	void setCurrentPlayer(int num);

	void setGrid();
	void getGrid();
};

