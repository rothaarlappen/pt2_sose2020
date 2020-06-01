#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cfloat>
#include <iomanip>
#include <vector>
#include <ctime>

#define HEADER_LINE  1
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

	if(t.tm_year < -7 || t.tm_year > 118){
		throw std::logic_error("Year should be between 1893 and 2018");
	}
	return t;
}

struct FormatException
{
	int m_actLine;
	std::string m_actFields;
};

std::vector<std::string> splitStringByDelimiter(std::string line, char delimiter) {
  std::istringstream linestream;
  linestream.str(line);
  std::vector<std::string> parts;
  std::string value;
  // split string into parts
  while (std::getline(linestream, value, delimiter)) {
    parts.push_back(value);
  }
  return parts;
}

void parseLine(std::string line, int lineNum)
{
	const std::string fieldNames[3] = { "Date", "Temperature", "Rainfall" };
  FormatException FormatException;
  FormatException.m_actLine = lineNum;
  FormatException.m_actFields = "";

	// TODO 3.1b: parse a given line, check dates by calling stringToTime, check temperature/rainfall by calling std::stof.
	// Catch all exceptions thrown by these methods.
	// If there have been any exceptions, aggregate all necessary information into an instance of FormatException and throw that instance.
  std::vector<std::string> parts = splitStringByDelimiter(line, ';');
  try {
    tm time = stringToTime(parts[0]);
  }
  catch (...) {
    FormatException.m_actFields += "Time ";
  }
  try {
    float temperature = std::stof(parts[1]);
  }
  catch (...){
    FormatException.m_actFields += "Temperature ";
  }
  try {
    float rainfall = std::stof(parts[2]);
  }
  catch (...) {
    FormatException.m_actFields += "Rainfall";
  }
  if (FormatException.m_actFields != "") {
	// if(FormatException.m_actLine == HEADER_LINE){
	// 	return;
	// }
    throw FormatException;
  }
}

// TODO 3.1d
void writeOutFormatException(const FormatException& e)
{
  try{
	std::ofstream logfile;
	logfile.open("FormatExceptions.log", std::ios_base::app);
	logfile << e.m_actLine << " : " << e.m_actFields << std::endl;
	logfile.close();
  }
  catch (std::ofstream::failure e){
    std::cerr << "Exception opening/reading/closing file" << std::endl;
  }
}

void checkData(std::string path)
{
	int validLines = 0;
	int invalidLines = 0;
  	int linenumber = 1;
	std::ifstream file;
  	std::string line;

  // TODO 3.1a: open file + read each line + call parseLine function (catch ifstream::failure)
	try {
		std::cout << "opening" << std::endl;
		file.open(path);
	}
	catch (std::ifstream::failure e){
		std::cout << "catch" << std::endl;
		std::cerr << "Exception opening/reading/closing file" << std::endl;
	}
    while (!file.eof()) {
      std::getline(file, line);
      // TODO 3.1c: read each line + call parseLine function (catch FormatException) + count valid + invalid lines
      try {
        parseLine(line, linenumber);
        validLines++;
      }
      catch (FormatException e) {
        invalidLines++;
        writeOutFormatException(e);
      }
      linenumber++;
    }

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
