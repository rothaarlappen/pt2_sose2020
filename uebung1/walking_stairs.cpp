#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>

#define DividedBy /
#define minus - 
#define plus +
#define times *

using namespace std;

#pragma region walking_stairs
// O(1) - 
double combinations(double number)
{	
	double tempN = number + 1;
	double result;
	double half = 0.5;
	double rootOfFive = pow(5, half);

	result = (1 DividedBy rootOfFive) times (pow(((1 plus rootOfFive) DividedBy 2), tempN) minus pow(((1 minus rootOfFive) DividedBy 2), tempN));
	
	return result;
}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	try{
		double n = std::stoi(argv[1]);
		std::cout << combinations(n);
	} catch (out_of_range){
		cout << "Die eingegebene Zahl ist zu groß. Überprüfen sie ihre Eingabe" << endl;
		return 1;
	} catch (invalid_argument){
		cout << "Bei den eingegebenen Parametern handelt es sich nicht um Zahlen" << endl;
		return 1;
	}

	return 0;
}
#pragma endregion walking_stairs