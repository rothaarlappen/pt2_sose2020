#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;


// How to use:
// g++ fibnoacci_iterative.cpp -o fibnoacci_iterative
// ./fibnoacci_iterative <integer>
#pragma region fibnoacci_iterative
int* fibonacci(int number)
{
	// ToDo: Exercise 1.c - count number of calculation steps
	// ToDo: Exercise 1.b - return 0 on bad arguments
	if(number < 1) {
		int * a = (int *) calloc(2, sizeof(int)); // {0, 0}
		return a;
	}

	// ToDo: Exercise 1.b - retrieve nth fibonacci number iteratively
	int * result = (int *) malloc(2);
	result[1] = 1;
	result[0] = 1;
	int previous = 1;
	int preprevious;	

	for(int i = 2; i < number; i++){
		preprevious = previous;
		previous = result[0];
		
		if(previous > 0 && preprevious > INT_MAX - previous){
			int * a = (int *) calloc(2, sizeof(int));
			return a;
		} else { 
			result[0] = preprevious + previous;
		}
		result[1]++;
	}

	return result;
}
int main(int argc, char * argv[])
{
	if(argc != 2)
	 	return 1;	
	try{
		int n = stoi(argv[1]);
	} catch (out_of_range){
		cout << "Die eingegebene Zahl ist zu groß. Überprüfen sie ihre Eingabe" << endl;
		return 1;
	} catch (invalid_argument){
		cout << "Bei den eingegebenen Parametern handelt es sich nicht um Zahlen" << endl;
		return 1;
	} catch (exception e){
		cout << "Unbekannter Fehler" << endl;
		return 1;
	}
	int n = std::stoi(argv[1]);

	// ToDo: Exercise 1.c - print calculation steps

	int * result = fibonacci(n);
	std::cout << n << " : " << result[0] << " : " << "#" << result[1];

	free(result);

	return 0;
}
#pragma endregion fibnoacci_iterative