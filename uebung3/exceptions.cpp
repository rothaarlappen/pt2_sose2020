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
std::vector<std::string> splitLineByDelimiter(std::string line, char delimiter) {
  std::istringstream linestream;
  linestream.str(line);
  std::vector<std::string> parts;
  std::string value;

  while (std::getline(linestream, value, delimiter)) {
    parts.push_back(value);
  }
  return parts;
}

std::string checkDateFormat(std::string date){
  try {
    tm time = stringToTime(date);
    return "";
  }
  catch (...) {
    return "Time ";
  }
}
std::string checkTemperatureFormat(std::string temperatureString){
  try {
    float temperature = std::stof(temperatureString);
    return "";
  }
  catch (...){
    return "Temperature ";
  }
}
std::string checkRainfallFormat(std::string rainfallString){
  try {
    float rainfall = std::stof(rainfallString);
    return "";
  }
  catch (...) {
    return "Rainfall";
  }
}

void parseLine(std::string line, int lineNum)
{
	const std::string fieldNames[3] = { "Date", "Temperature", "Rainfall" };
  FormatException FormatException = {lineNum, ""};
  std::vector<std::string> parts = splitLineByDelimiter(line, ';');
	// TODO 3.1b: parse a given line, check dates by calling stringToTime, check temperature/rainfall by calling std::stof.
	// Catch all exceptions thrown by these methods.
	// If there have been any exceptions, aggregate all necessary information into an instance of FormatException and throw that instance.
  FormatException.m_actFields += checkDateFormat(parts[0]);
  FormatException.m_actFields += checkTemperatureFormat(parts[1]);
  FormatException.m_actFields += checkRainfallFormat(parts[2]);

  if (FormatException.m_actFields != "") {
    throw FormatException;
  }
  return; 
}
// TODO 3.1d
void writeOutFormatException(const FormatException& e)
{
  if(e.m_actLine == 1){
    return;
  }
  std::ofstream logfile;
  std::ios_base::iostate exceptionMask = logfile.exceptions() | std::ios::failbit;
  logfile.exceptions(exceptionMask);

  try{
    logfile.open("FormatExceptions.log", std::ios_base::app);
    logfile << e.m_actLine << " : " << e.m_actFields << std::endl;
    logfile.close();
  }
  catch (std::ofstream::failure e){
    std::cerr << "Exception opening/reading/closing Logfile" << std::endl;
  }
}
void checkData(std::string path)
{
	int validLines = 0;
	int invalidLines = 0;
  int linenumber = 2;
	std::ifstream file;
  std::string line;

  std::ios_base::iostate exceptionMask = file.exceptions() | std::ios::failbit;
  file.exceptions(exceptionMask);

  // TODO 3.1a: open file + read each line + call parseLine function (catch ifstream::failure)
	try {
		file.open(path);
    // Ignoring Header-Line
    std::getline(file, line);
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
    file.close();
    
	  std::cout << "valid data fields: " << validLines << " - invalid data fields: " << invalidLines << std::endl;
  }
	catch (std::ifstream::failure e){
		std::cerr << "Exception opening/reading/closing file" << std::endl;
	}

}

void clearLogfile(){
  std::ofstream logfile;
  try{
    logfile.open("FormatExceptions.log", std::ios_base::binary);
    logfile << "Line : Error Description" << std::endl;
    logfile.close();
  } catch (std::ifstream::failure e){
    std::cerr << "Exception opening/reading/closing Logfile" << std::endl;
  }
}

int main(int argc, char * argv[]){
	if(argc != 2)
	{
		std::cout << "Invalid number of arguments - USAGE: exceptions [DATASET]" << std::endl;
		return -1;
	}
  clearLogfile();
	checkData(argv[1]);

	return 0;
}
