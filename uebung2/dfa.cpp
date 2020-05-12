#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <string>
#include <cassert>

using namespace std;

std::string step(std::string state, int value)
{
	// TODO: Handle all possible states and values and return the respective new state
	// Note: Accepted coin values are {10, 20, 50}.
	string dispense = "dispense";
	vector<int> acceptedValues = {10, 20, 50};

	if(value != 10 && value != 20 && value != 50) return state;

	switch(stoi(state)) {
		case 0:
			switch(value){
				case 50: return dispense; break;
				default : return to_string(value); break;
			}
		case 10:
			switch(value){
				case 10: return "20";
				case 20: return "30";
				default: return dispense;
			}
		case 20:
			switch(value){
				case 10: return "30";
				case 20: return "40";
				default: return dispense;
			}
		case 30:
			switch(value){
				case 10: return "40";
				default: return dispense;
			}
		case 40:
			switch(value){
				default: return dispense;
			}
	}



	// for all states and inputs which are not handled above show a message and return original state
	std::cout << "Invalid input.\n";
	return state;
}


std::string stepExtended(std::string state, int value)
{
	string dispense = "dispense";
	// TODO: Handle all possible states and values and return the respective new state
	// Note: Accepted coin values are {10, 20, 50}. Accepted drink selection values are {1, 2, 3}.
	switch(stoi(state)){
		case 0:
			return to_string(value);
		case 1: 
			switch (value){
				case 0: return state;
				case 10: return "110";
				case 20: return "120";
				case 50: return dispense;
				default: break;
			}
		case 2:
			switch (value){
				case 0: return state;
				case 10: return "210";
				case 20: return "220";
				case 50: return "250";
				default: break;
			}
		case 3:
			switch (value){
				case 0: return state;
				case 10: return "310";
				case 20: return "320";
				case 50: return "350";
				default: break;
			}
		case 110:
			switch (value){
				case (10): return "120";
				case (20): return "130";
				case (50): return dispense;
			}
		case 120:
			switch (value){
				case (10): return "130";
				case (20): return "140";
				case (50): return dispense;
			}
		case 130:
			switch (value){
				case (10): return "140";
				default: return dispense;
			}
		case 140:
			return dispense;
		case 210:
			switch(value){
				case (10): return "220";
				case (20): return "230";
				case (50): return "260";
				default: break;
			}
		case 220:
			switch(value){
				case (10): return "230";
				case (20): return "240";
				case (50): return "270";
				default: break;
			}
		case 230:
			switch(value){
				case (10): return "240";
				case (20): return "250";
				default: dispense;
			}
		case 240:
			switch(value){
				case (10): return "250";
				case (20): return "260";
				default: dispense;
			}
		case 250:
			switch(value){
				case (10): return "260";
				case (20): return "270";
				default: dispense;
			}
		case 260:
			switch(value){
				case (10): return "270";
				default: return dispense;
			}
		case 270:
			return dispense;
		case 310:
			switch(value){
				case (10): return "320";
				case (20): return "330";
				case (50): return "360";
				default: break;
			}
		case 320:
			switch(value){
				case (10): return "330";
				case (20): return "340";
				case (50): return "370";
				default: break;
			}
		case 330:
			switch(value){
				case (10): return "340";
				case (20): return "350";
				case (50): return "380";
				default: break;
			}
		case 340:
			switch(value){
				case (10): return "350";
				case (20): return "360";
				case (50): return "390";
				default: break;
			}
		case 350:
			switch(value){
				case (10): return "360";
				case (20): return "370";
				default: return dispense;
			}
		case 360:
			switch(value){
				case (10): return "370";
				case (20): return "380";
				default: return dispense;
			}
		case 370:
			switch(value){
				case (10): return "380";
				case (20): return "390";
				default: return dispense;
			}
		case 380:
			switch(value){
				case (10): return "390";
				default: return dispense;
			}
		case 390:
			return dispense;

	}

	// for all states and inputs which are not handled above show a message and return original state
	std::cout << "Invalid input.\n";
	return state;
}


int main(int argc, char * argv[])
{
	std::string state = "0";
	bool extendedMode = false;

	if(argc == 2)
		extendedMode = true;

	while(true)
	{
		int value = 0;
		std::string input;
		if(state == "0" && extendedMode)
			std::cout << "Current state: " << state << ". Please select a drink (1, 2, 3): ";
		else
			std::cout << "Current state: " << state << ". Please input a coin (10, 20, 50): ";
		std::getline(std::cin, input);
		std::stringstream(input) >> value;

		state = extendedMode ? stepExtended(state, value) : step(state, value);

		if(state == "dispense")
		{
			std::cout << "Here is your drink. Goodbye!\n\n";
			state = "0";
		}
	}
}
