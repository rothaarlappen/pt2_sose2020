#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// How to use:
// g++ change.cpp -o change
// ./change <positive_int_due> <positive_int_paid> [-o <filename>]
#pragma region helperFunction

// übernommen von https://thispointer.com/c-how-to-check-if-a-string-ends-with-an-another-given-string/
bool endsWith(const string &mainStr, const string &toMatch){
	if(mainStr.size() >= toMatch.size() &&
			mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
			return true;
		else
			return false;
}

vector<pair<int, int>> computeChange(const int due, const int paid){
	// ToDo: compute and print set of change tuples
	int change = paid - due;

    vector<pair<int, int>> coins = { 
        {5000, 0}, 
        {2000, 0}, 
        {1000, 0}, 
        {500, 0}, 
        {200, 0}, 
        {100, 0}, 
        {50, 0}, 
        {20, 0}, 
        {10, 0}, 
        {5, 0}, 
        {2, 0}, 
        {1, 0}
    };

	// compute set of change tuples
	while (change > 0){
		for(int i = 0; i < coins.size() ; i++){
			if(coins[i].first <= change){
				change -= coins[i].first;
				coins[i].second++;
				break;
			}
		}
	}
	return coins;
}
void printResultInConsole(vector<pair<int,int>> result){
    for(int i = 0; i < result.size() ; i++){
        if (result[i].second)
            cout << result[i].first << "," << result[i].second << endl;
    }
}
void printResultInFile(vector<pair<int,int>> result, string filename){
    ofstream a_file( filename );

		for(int i = 0; i < result.size() ; i++){
			if (result[i].second)
				a_file << result[i].first << "," << result[i].second << endl;
		}
		a_file.close();
		cout << "Die Ausgabe wurde in die Datei " << filename << " geschrieben" << endl;
}
string getFilename(char * argv[]){
    string filename = argv[4];
    string checkString = "-o";

    if (filename.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") != string::npos)
    {
        cerr << "Ungueltiger Dateiname. Bitte verwenden Sie keine Sonderzeichen und geben Sie den Datentyp nicht an (.txt).";
        return "";
    }
    if(!(checkString.compare(argv[3]) == 0)){
        cerr << "Ungültige Eingabe." << endl;
        return "";
    }

    if(!endsWith(filename, ".txt")){
        filename += ".txt";
    }
    return filename;
}

#pragma endregion helperFunction
#pragma region main
int main(int argc, char * argv[]){
	vector<pair<int,int>> changeVector;
	int due;
	int paid; 

	if(argc != 3 && argc != 5)
		cout << "Ungültige Anzahl an Parametern. Bitte überprüfen sie ihre Eingabe" << endl;

	try{
		due = stoi(argv[1]);
		paid = stoi(argv[2]);
	} catch (out_of_range){
		cout << "Die eingegebene Zahl ist zu groß. Überprüfen sie ihre Eingabe" << endl;
		return 1;
	} catch (invalid_argument){
		cout << "Bei den eingegebenen Parametern handelt es sich nicht um Zahlen" << endl;
		return 1;
	} catch (...){
		cout << "Die eingegebenen Parameter sind fehlerhaft." << endl;
		return 1;
	}

    if(due < 0 || paid < 0){
        cout << "Ungueltige Eingabe." << endl;
        return 1;
    }else if(due > paid){
		cout << "Der bezahlte Betrag ist kleiner als der zu tilgende. Parameter vertauscht?" << endl;
		return 1;
	}

	changeVector =  computeChange(due, paid);
	
	if(argc == 3){
        printResultInConsole(changeVector);
	} else if (argc == 5) {		
		string filename = getFilename(argv);
        if(filename != ""){
		    printResultInFile(changeVector, filename);
        } else {
            return 1;
        }
	}
	return 0;
}
#pragma endregion main
