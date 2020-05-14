#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

using namespace std;

// 343;"Tempelhof";"Berlin";"Germany";"THF";"EDDI";52.473025;13.403944;167;1;"E";"Europe/Berlin"
// 
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

vector<string> splitString(string toBeSplitted, char byChar){
	vector <string> parts;
    while(toBeSplitted.size()){
        int index = toBeSplitted.find(byChar);
        if(index!=string::npos){
            parts.push_back(toBeSplitted.substr(0,index));
            toBeSplitted = toBeSplitted.substr(index+1);
            if(toBeSplitted.size()==0)parts.push_back(toBeSplitted);
        }else{
            parts.push_back(toBeSplitted);
            toBeSplitted = "";
        }
    }
	return parts;
}

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
			regExp = "[A-Z0-9]{3,4}|^$";
			error_msg = "Der ICAO Code ist fehlerhaft.";
			break;
		case ALTITUDE:
			regExp = "[012]?[0-9]{0,4}";
			error_msg = "Die Altitude ist fehlerhaft.";
			break;
		case DST:
			regExp = "[EASOZNU]{1}";
			error_msg = "DST ist fehlerhaft.";
			break;
		// other column
		default:
			regExp = ".*";
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
	while (std::getline(file, line)) {
		std::istringstream linestream;
		linestream.str(line);
		vector<string> parts = splitString(line, ';');

		columns name = NAME;
		columns timeZone = TIMEZONE_LONG;
		// cout << parts[name] << '-' << parts[timeZone] << endl;
		// TODO: - Split line and write result to std::cout
		//       - Check each part of line with isValueCorrect and log if values are not supported
		//       - Use and extend isValueCorrect function for this

		// checking every Column:
		columns column = NUMBER;
		for(; column < parts.size();){
			if(isValueCorrect(stripString(parts[column]), column) != ""){

				cout << isValueCorrect(stripString(parts[column]), column) << " line: " << lineCounter <<  " content: " << parts[column] << endl;
			}

			column = columns((int(column) + 1));
		}
		
		lineCounter++;
	}

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
