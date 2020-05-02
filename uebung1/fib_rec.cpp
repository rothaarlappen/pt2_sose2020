#include <cstdlib>
#include <iostream>
#include <string>
#include <climits>

using namespace std;

int stepsNeeded = 0;
bool overflow = false;

#pragma region fibonacci_recursive
// returns array {<nthFibonacci>,<requiredSteps>}
int fibonacci(int number)
{
    if(overflow) return 0;
    stepsNeeded++;
	try{
		// Bad arguments
		if(number <= 2) {
			return 1;
		} else {
			int current;
			int previous = fibonacci(number - 1);
			int preprevious = fibonacci(number - 2);
			
			if(previous > 0 && preprevious > INT_MAX - previous){
				throw overflow_error("Overflow");
			} else { 
				current = previous + preprevious;
				current = previous + preprevious;
				return current;
			}
		}
	} catch(overflow_error){
        overflow = true;
        stepsNeeded = 0;
		return 0;
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
		int nthFibonacci = fibonacci(n);
        if(!overflow){
		    std::cout << n <<  " : " << nthFibonacci << " : " << "#" << stepsNeeded;
        } else {
            cout << "Overflow-Error. Bitte versuche es mit einer kleineren Zahl." << endl;
        }
	} catch(overflow_error){
		cout << "uff" << endl;
	}

	return 0;
}
#pragma endregion fibonacci_recursive