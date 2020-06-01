#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>

int main (){
    std::vector <int> firstVec = {1, 2, 3, 4, 5, 6};
    std::vector <int> secondVec (firstVec.size());


    std::transform (firstVec.begin(), firstVec.end(), secondVec.begin(), [](int i ) { return i*i;});

    for(auto i: secondVec){
        std::cout << i << std::endl;
    }

}