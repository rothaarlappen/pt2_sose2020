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
	DONT_KNOW,
	BOOL_WHATEVER,
	TIMEZONE_SHORT,
	TIMEZONE_LONG,
};

vector<string> splitString(string toBeSplitted, char byChar){
	vector <string> parts;
	while(toBeSplitted.find_first_of(byChar) != string::npos){
		
	}

	return parts;
}


bool isValueCorrect(const std::string &teststring, const int &column)
{
	std::regex regExp;

	switch (column)
	{
		// example regExp for column 1
		/*case 1:
			regExp = "[a-zA-Z]+";
			break;*/

		// TODO: implement cases for other columns

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
		//cout << line << endl;

		// TODO: - Split line and write result to std::cout
		//       - Check each part of line with isValueCorrect and log if values are not supported
		//       - Use and extend isValueCorrect function for this

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
