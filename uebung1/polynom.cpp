#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

#pragma region polynom
double polynom(int x, int n, vector<double> coefficients) {
	// ToDo: Exercise 2.b - compute value of P(x)
	double sum = 0;
	for(int i = 0; i <= n; i++){
		sum += pow(x, i) * coefficients[i];
	}
	return sum;
}
void prettyPrint(double decimal)
{
	string output = to_string(decimal);

	int integerPartIndex = output.find_first_of(".");

	for(int i =	integerPartIndex - 1; i > 1; i--){
		if(((integerPartIndex - i) % 3) == 0)
			output.insert(i, ",");
	}
	cout << output << endl;
}

int main(int argc, char* argv[])
{
	// ToDo: Exercise 2.a - read parameters and x, deal with invalid values
	if (argc < 3){
		cout << "Es wird eine Eingabe der Form x, n, a0, a1, ... , aN erwartet " << endl;
		return 1;
	}

	// Exercise 1a) 
	vector<double> coefficients;

	int x = stoi(argv[1]);
	int n = stoi(argv[2]);

	try{
		// aN != 0
		if(n != argc - 4){
			cout << "Falsche Anzahl an Koeffizienten eingegeben" << endl;
			return 1;
		}

		for (int i = 3; i < argc; i++){
			coefficients.push_back(stod(argv[i]));
		}

	} catch (out_of_range){
		cout << "Die eingegebene Zahl ist zu groß. Überprüfen sie ihre Eingabe" << endl;
		return 1;
	} catch (invalid_argument){
		cout << "Bei den eingegebenen Parametern handelt es sich nicht um Zahlen" << endl;
		return 1;
	}

	cout << setprecision(6) << fixed;
	
	// ToDo: Exercise 2.b - print P(x)
	double result = polynom(x, n, coefficients);
	cout << result << endl;

	// ToDo: Exercise 2.c - print P(x) with prettyPrint
	prettyPrint(result);

	return 0;
}
#pragma endregion polynom
