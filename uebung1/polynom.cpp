#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <string>
#include <cmath>
#include <cfloat>

using namespace std;

#pragma region polynom
bool CheckForOverflow(double firstSummand, double secondSummand){
	return (secondSummand > 0) ? (firstSummand > DBL_MAX - secondSummand) : (firstSummand < DBL_MIN - secondSummand);
}

double polynom(int x, int n, vector<double> coefficients) {
	// ToDo: Exercise 2.b - compute value of P(x)
	double sum = 0;
	for(int i = 0; i <= n; i++){
		double summand = pow(x, i) * coefficients[i];
		if(CheckForOverflow(sum, summand))
			throw overflow_error("shit happens");
		sum += summand;
	}
	return sum;
}

void prettyPrint(double decimal){
	string output = to_string(decimal);

	int commaPosition = output.find_first_of(".");

	for(int i =	commaPosition - 3; i > 0; i = i - 3){
		output.insert(i, ",");
	}
	cout << output << endl;
}

int main(int argc, char* argv[]){
	vector<double> coefficients;
	int n;
	double x;
	cout << setprecision(6) << fixed;
	// ToDo: Exercise 2.a - read parameters and x, deal with invalid values
	if (argc < 3){
		cout << "Es wird eine Eingabe der Form x, n, a0, a1, ... , aN erwartet " << endl;
		return 1;
	}

	// Exercise 1a) 
	try{
		x = stod(argv[1]);
		n = stoi(argv[2]);
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

	// ToDo: Exercise 2.b - print P(x)
	try{
		double result = polynom(x, n, coefficients);
		cout << result << endl;
		// ToDo: Exercise 2.c - print P(x) with prettyPrint
		prettyPrint(result);
	}catch(overflow_error){
		cout << "Overflow" << endl;
		return 1;
	}
	

	return 0;
};
#pragma endregion polynom
