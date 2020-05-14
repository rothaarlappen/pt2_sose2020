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


bool isValueCorrect(const std::string &teststring, const int &column)
{
	std::regex regExp;

	switch (column)
	{
		case ICAO_CODE:
			regExp = "[A-Z0-9]{3,4}";
			break;
		case ALTITUDE:
			regExp = "[012]{1}[0-9]{0,4}";
			break;
		case DST:
			regExp = "[EASOZNU]{1}";
			break;
		// other column
		default:
			regExp = ".*";
			break;
	}

	return std::regex_match(teststring, regExp);
}

void readTokensAndLines(char* path)
{
	std::ifstream file(path);
	std::string parsed, line;

	while (std::getline(file, line)) {
		std::istringstream linestream;
		linestream.str(line);
		vector<string> parts = splitString(line, ';');
		
		columns name = NAME;
		columns timeZone = TIMEZONE_LONG;
		cout << parts[name] << '-' << parts[timeZone] << endl;
		// TODO: - Split line and write result to std::cout
		//       - Check each part of line with isValueCorrect and log if values are not supported
		//       - Use and extend isValueCorrect function for this
		for (auto const&: ){

		}
		//std::cout << linestream << std::endl;
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
