#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

int ** change(const int due, const int paid)
{
	// ToDo: compute and print set of change tuples
	int i1 = 42;
	int i2 = 69;
	int ** arr1 = (int **) malloc(1);
	arr1[0] = (int *) malloc(2);

	int change = paid - due;

	int * coins = (int *) malloc(12 * sizeof(int));
	coins[11] 	= 5000;
	coins[10] 	= 2000;
	coins[9] 	= 1000;
	coins[8] 	= 500;
	coins[7] 	= 200;
	coins[6] 	= 100;
	coins[5] 	= 50;
	coins[4] 	= 20;
	coins[3] 	= 10;
	coins[2] 	= 5;
	coins[1] 	= 2;
	coins[0] 	= 1;
	int * counter = (int *) calloc(12, sizeof(int));

	// compute set of change tuples

	while (change > 0){
		for(int i = 11; i > 0 ; i--){
			if(coins[i] <= change){
				change -= coins[i];
				counter[i] ++;
				break;
			}
		}
	}

    arr1[0] = coins;
	arr1[1] = counter;

	return arr1;
}
// übernommen von https://thispointer.com/c-how-to-check-if-a-string-ends-with-an-another-given-string/
bool endsWith(const std::string &mainStr, const std::string &toMatch)
{
	if(mainStr.size() >= toMatch.size() &&
			mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
			return true;
		else
			return false;
}

int main(int argc, char * argv[])
{
	if(argc != 3 && argc !=5)
		cout << "Ungültige Anzahl an Parametern. Bitte überprüfen sie ihre Eingabe" << endl;

	int ** changeArr;
	int due;
	int paid; 

	try{
		due = std::stoi(argv[1]);
		paid = std::stoi(argv[2]);
	} catch (out_of_range){
		cout << "Die eingegebene Zahl ist zu groß. Überprüfen sie ihre Eingabe" << endl;
		return 1;
	} catch (invalid_argument){
		cout << "Bei den eingegebenen Parametern handelt es sich nicht um Zahlen" << endl;
		return 1;
	}

	changeArr =  change(due, paid);
	
	if(argc == 3){
		for(int i = 0; i < 12 ; i++){
			if (changeArr[1][i])
				cout << changeArr[0][i] << "," << changeArr[1][i] << endl;
		}
	} else if (argc == 5) {		
		string checkString = "-o";
		string fileName = argv[4];

		if(!(checkString.compare(argv[3]) == 0))
			cout << "Ungültige Eingabe" << endl;

		if(!endsWith(fileName, ".txt"))
			fileName += ".txt";

		ofstream a_file( fileName );

		for(int i = 0; i < 12 ; i++){
			if (changeArr[1][i])
			a_file << changeArr[0][i] << "," << changeArr[1][i] << endl;
		}
		a_file.close();
		cout << "Die Ausgabe wurde in die Datei " << fileName << " geschrieben" << endl;
	}
	return 0;
}

