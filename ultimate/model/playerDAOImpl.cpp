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
	//size_t nameFound;
	//size_t markerFound;
	bool found = false;
	while (getline(file, tmp)) {
		rapidjson::Document document;
		document.Parse(tmp.c_str());
		/*nameFound = tmp.find(name);
		markerFound = tmp.find(marker);*/
		rapidjson::Value& nameStr = document["name"];
		rapidjson::Value& markerStr = document["marker"];
		if (((nameStr.GetString()==name) && (markerStr.GetString() == marker))) {
			found = true;
			break;
		}
	}
	file.close();
	if (!found) {
		file.open(path, fstream::app | fstream::out);
		string input = "{\"name\":\"" + player.getName() + "\",\"marker\":\"" + player.getRole() + "\",\"stats\":{\"uwin\":0,\"ulose\":0,\"utie\":0,\"win\":0,\"lose\":0,\"tie\":0}}";
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
		output = output  +tmp;
		if (!file.eof())
			output = output + ",";
	}
	size_t pos = output.find_last_of(",");
	output.erase(pos, 1);
	file.close();
	return output;
}


void playerDAOImpl::updatePlayer(Player player, string grade)
{
	file.open(path, fstream::in);
	fstream tmpFile;
	tmpFile.open("tmp.txt", fstream::out);
	string tmp;
	string name = player.getName();
	string marker = player.getRole();
	while (getline(file, tmp)) {

		rapidjson::Document document;
		document.Parse(tmp.c_str());
		rapidjson::Value& nameStr = document["name"];
		rapidjson::Value& markerStr = document["marker"];
		if (((nameStr.GetString() == name) && (markerStr.GetString() == marker))) {
			rapidjson::Value& gradeStr = document["stats"][grade.c_str()];
			gradeStr.SetInt(gradeStr.GetInt()+1);
			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			document.Accept(writer);
			tmpFile << buffer.GetString() << endl;
		}else
		{
			tmpFile << tmp << endl;
		}
	}
	file.close();
	tmpFile.close();
	file.open(path, fstream::out);
	tmpFile.open("tmp.txt",fstream::in);
	while (getline(tmpFile, tmp)) {
		file << tmp << endl;
	}
	file.close();
	tmpFile.close();
}



playerDAO::~playerDAO()
{
}

void playerDAO::savePlayer(Player player) {

}

void playerDAO::updatePlayer(Player player, string grade){
	
}


