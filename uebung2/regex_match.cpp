#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
int main (){

    
    // Müllerstr.
    // Prof-Dr.-Heisestr.
    // Wilhelmstraße
    // Deine Mamastr.

    std::regex regExp;
    regExp = "[A-Z0-9]{3,4}";
    std::string teststring = "AYGA";
    if(std::regex_match(teststring, regExp)){
        std::cout << "RegEx tut matchen, du weißt" << std::endl;
    } else {
        std::cout << "Da matched gar nichts, so wie bei deinem Outfit" << std::endl;
    }
}