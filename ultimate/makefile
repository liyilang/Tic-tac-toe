all:
	g++ -std=c++11 -c ./controller/TTTController.cpp -o TTTController.o
	g++ -std=c++11 -c ./model/Computer.cpp -o Computer.o
	g++ -std=c++11 -c ./model/Grid.cpp -o Grid.o
	g++ -std=c++11 -c ./model/GridDAOImpl.cpp -o GridDAOImpl.o
	g++ -std=c++11 -c ./model/JsonReader.cpp -o JsonReader.o
	g++ -std=c++11 -c ./model/Mark.cpp -o Mark.o
	g++ -std=c++11 -c ./model/Player.cpp -o Player.o
	g++ -std=c++11 -c ./model/playerDAOImpl.cpp -o playerDAOImpl.o
	g++ -std=c++11 -c ./model/Strategy.cpp -o Strategy.o
	g++ -std=c++11 -c ./model/winRules.cpp -o winRules.o
	g++ -std=c++11 -c main.cpp -o main.o
	g++ -std=c++11 Grid.o Mark.o winRules.o Strategy.o Player.o Computer.o GridDAOImpl.o JsonReader.o playerDAOImpl.o TTTController.o main.o -o ttt
	mv ttt cgi-bin/ttt.cgi
clean:
	rm -rf *.o ttt cgi-bin/ttt.cgi cgi-bin/*.txt
