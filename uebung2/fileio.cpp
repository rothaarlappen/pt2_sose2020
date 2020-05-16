#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

using namespace std;

enum columns {
	NUMBER, 
	NAME, 
	TOWN,
	COUNTRY,
	IATA_CODE,		// International Air Transport Association
	ICAO_CODE,		// International Civil Aviation Organization
	LATITUDE,
	LONGITUDE,
	ALTITUDE,
	UTC_OFFSET,
	DST,
	TIMEZONE_LONG,
	END,
};

string stripString(string toBeStripped){
	if(toBeStripped.front() == '"' && toBeStripped.back() == '"' && toBeStripped.size() >= 2){
		toBeStripped = toBeStripped.substr(1, toBeStripped.size() - 2);
	}
	return toBeStripped;
}

string isValueCorrect(const std::string &teststring, columns &column)
{
	std::regex regExp;
	string error_msg;
	switch (column)
	{
		case ICAO_CODE:
			regExp = "^[A-Z0-9]{3,4}$|^$";
			error_msg = "Der ICAO Code " + teststring + " ist fehlerhaft.";
			break;
		case ALTITUDE:
			regExp = "^[12]{1}[0-9]{0,4}|[1-9]{1}[0-9]{0,3}|0$";
			error_msg = "Die Altitude " + teststring + " ist fehlerhaft.";
			break;
		case DST:
			regExp = "^[EASOZNU]{1}$";
			error_msg = "DST " + teststring + " ist fehlerhaft.";
			break;
		// other column
		default:
			regExp = "^.*$";
			error_msg = "Something went wrong.";
			break;
	}
	if(!regex_match(string(teststring), regExp)){
		return error_msg;
	}
	return "";
	//return (regex_match(teststring, regExp)) ? "" : error_msg;  
}

void readTokensAndLines(char* path)
{
	std::ifstream file(path);
	std::string parsed, line;
	int lineCounter = 0;

	ofstream logfile;
	logfile.open ("fileio.log");

	while (std::getline(file, line)) {
		std::istringstream linestream;
		linestream.str(line);
		string value;
		vector<string> parts;
		// split string into parts
		while(std::getline(linestream, value, ';')){
			parts.push_back(stripString(value));
		}

		// print out name and timezone in line
		columns name = NAME;
		columns timeZone = TIMEZONE_LONG;
		cout << parts[name] << " - " << parts[timeZone] << endl;

		// checking every Column:
		columns column = NUMBER;
		vector<string> errorlist;
		for(; column < parts.size();){
			string error = isValueCorrect(parts[column], column);
			if(error != ""){
				errorlist.push_back(error);
			}
			column = columns((int(column) + 1));
		}
		
		// check if errors have been found and write them into file:
		if(errorlist.size()>0){
			logfile << line << endl;
			for(int i = 0; i < errorlist.size(); i++){
				logfile << errorlist[i] << endl;
			}
		}
		lineCounter++;
	}
	logfile.close();
}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		std::cout << "not enough arguments - USAGE: fileio [DATASET]" << std::endl;
		return -1; // invalid number of parameters
	}

	std::cout << "Given path to airports.dat: " << argv[1] << std::endl;

	readTokensAndLines(argv[1]);

	return 0;
}
