#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cfloat>
#include <iomanip>
#include <vector>
#include <ctime>

// transforms a string to a date. Throws a logic_error if year is *not* between 1893 and 2018
std::tm stringToTime(std::string date)
{
	std::tm t;
#if defined(__GNUC__) && (__GNUC__ < 5)
	strptime(date.c_str(), "%Y%m%d", &t);
#else
	std::istringstream ss(date);
	ss >> std::get_time(&t, "%Y%m%d");
#endif

	if(t.tm_year < -7 || t.tm_year > 118)
		throw std::logic_error("Year should be between 1893 and 2018");

	return t;
}

struct FormatException
{
	int m_actLine;
	std::string m_actFields;
};

void parseLine(std::string line, int lineNum)
{
	const std::string fieldNames[3] = { "Date", "Temperature", "Rainfall" };

	// TODO 3.1b: parse a given line, check dates by calling stringToTime, check temperature/rainfall by calling std::stof.
	// Catch all exceptions thrown by these methods.
	// If there have been any exceptions, aggregate all necessary information into an instance of FormatException and throw that instance.


}

// TODO 3.1d
void writeOutFormatException(const FormatException& e)
{

}

void checkData(std::string path)
{
	int validLines = 0;
	int invalidLines = 0;
	std::ifstream file;

	// TODO 3.1a: open file + read each line + call parseLine function (catch ifstream::failure)
	// TODO 3.1c: read each line + call parseLine function (catch FormatException) + count valid + invalid lines



	std::cout << "valid data fields: " << validLines << " - invalid data fields: " << invalidLines << std::endl;
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		std::cout << "Invalid number of arguments - USAGE: exceptions [DATASET]" << std::endl;
		return -1;
	}

	checkData(argv[1]);

	return 0;
}
