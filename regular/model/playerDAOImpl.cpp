#include "playerDAOImpl.h"


playerDAOImpl::playerDAOImpl()
{
}


playerDAOImpl::~playerDAOImpl()
{
}

void playerDAOImpl::savePlayer(Player player)
{
	file.open(path, fstream::in);
	string tmp;
	string name = player.getName();
	string marker = player.getRole();
	size_t nameFound;
	size_t markerFound;
	bool found = false;
	while (getline(file, tmp)) {
		nameFound = tmp.find(name);
		markerFound = tmp.find(marker);
		if (((nameFound != string::npos) && (markerFound != string::npos))) {
			found = true;
			break;
		}
	}
	file.close();
	if (!found) {
		file.open(path, fstream::app | fstream::out);
		string input = "\"name\":\"" + player.getName() + "\",\"marker\":\"" + player.getRole() + "\"";
		file << input << endl;
		file.close();
	}
}

string playerDAOImpl::getPlayers()
{
	file.open(path, ios::in);
	string output="";
	string tmp;
	while (getline(file,tmp)) {
		output = output +"{" +tmp+"}";
		if (!file.eof())
			output = output + ",";
	}
	size_t pos = output.find_last_of(",");
	output.erase(pos, 1);
	file.close();
	return output;
}

playerDAO::~playerDAO()
{
}

void playerDAO::savePlayer(Player player) {

}
