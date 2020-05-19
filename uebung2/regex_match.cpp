#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
int main (){

    std::regex regExp;
    regExp = "^([A-ZÖÄÜ][a-zäöüß]+)(( |\\.?\\-)(([A-ZÖÄÜ][a-zäöüß]+)))*.?$";
    std::string teststring = "Gerd Paul";
    if(std::regex_match(teststring, regExp)){
        std::cout << "RegEx tut matchen, du weißt" << std::endl;
    } else {
        std::cout << "Da matched gar nichts, so wie bei deinem Outfit" << std::endl;
    }
}