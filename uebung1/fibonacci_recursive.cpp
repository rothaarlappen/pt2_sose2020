#include <cstdlib>
#include <iostream>
#include <string>
#include <climits>

using namespace std;

#pragma region fibonacci_recursive
// returns array {<nthFibonacci>,<requiredSteps>}
int * fibonacci(int number)
{
	// Bad arguments
	if(number < 1) {
		int * a = (int *) calloc(2, sizeof(int));
		return a;
	}

	if(number <= 2) {
		int * a = (int *) malloc(2);
		// first and second fibonacci equal 1. 1 step (functioncall) required.
		// frag mal Fabian wie das hier aussieht... ist halt gleichzusetzen mit 1 = 1 + 0 (deswegen schon 1 step)
		a[0] = 1;
		a[1] = 1;
		return a;
	} else {
		int * current = (int *) malloc(2);
		int * previous = fibonacci(number - 1);
		int * preprevious = fibonacci(number - 2);
		
		if(previous[0] > 0 && preprevious[0] > INT_MAX - previous[0]){
			throw overflow_error("Overflow");
		} else { 
			current[0] = previous[0] + preprevious[0];
			current[1] = previous[1] + preprevious[1] + 1;
			
			free(previous);
			free(preprevious);
			return current;
		}
	}

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
	try{
		int * nthFibonacci = fibonacci(n);
		std::cout << n <<  " : " << nthFibonacci[0] << " : " << "#" << nthFibonacci[1];
		free(nthFibonacci);
	} catch(overflow_error){
		cout << "Overflow. Versuche es bitte mit einer kleineren Zahl." << endl;
	}
	return 0;
}
#pragma endregion fibonacci_recursive