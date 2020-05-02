#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

#pragma region polynom
double polynom(int x, int n, vector<int> coefficients) {
	// ToDo: Exercise 2.b - compute value of P(x)
	double sum = 0;
	for(int i = 0; i <= n; i++){
		sum += pow(x, i) * coefficients[i];
	}
	return sum;
}
void prettyPrint(double decimal)
{
	string output = "";
	while(decimal > 0){
		output =  to_string((int) fmod(decimal, 1000)) + "." + output;
		decimal = floor(decimal / 1000);
	}
	output.pop_back();
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
	vector<int> coefficients;

	int x = stoi(argv[1]);
	int n = stoi(argv[2]);

	try{
		// aN != 0
		if(n != argc - 4){
			cout << "Falsche Anzahl an Koeffizienten eingegeben" << endl;
			return 1;
		}

		for (int i = 3; i < argc; i++){
			coefficients.push_back(stoi(argv[i]));
		}

	} catch (out_of_range){
		cout << "Die eingegebene Zahl ist zu groß. Überprüfen sie ihre Eingabe" << endl;
		return 1;
	} catch (invalid_argument){
		cout << "Bei den eingegebenen Parametern handelt es sich nicht um Zahlen" << endl;
		return 1;
	}

	// ToDo: Exercise 2.b - print P(x)
	cout << polynom(x, n, coefficients) << endl;

	// ToDo: Exercise 2.c - print P(x) with prettyPrint
	prettyPrint(polynom(x, n, coefficients));

	return 0;
}
#pragma endregion polynom
