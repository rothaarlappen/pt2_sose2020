#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstdint> 

using namespace std;


#pragma region walking_stairs
// O(1) - 
uint64_t combinations(int number){	
	uint64_t result = 1;
	uint64_t previous = 1;
	uint64_t preprevious = 0;

	if(number == 0)
		return 0;
	if(number == 1)
		return 1;

	for(int i = 2; i < number + 1; i++){
		preprevious = previous;
		previous = result;
		result = previous + preprevious;
	}
	
	return result;
}

int main(int argc, char * argv[]){
	if(argc != 2)
		return 1;	// invalid number of parameters

	try{
		int n = stoi(argv[1]);
		cout << combinations(n) << endl;
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