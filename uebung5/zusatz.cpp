#include <iostream>
#include <vector>
#include <iostream>
#include <algorithm>

// Could/Should be both parameters of the isCorrectChangeAvailable - Function.
std::vector<int> coins = {6, 9};
int ChangeToBeChecked = 187;


bool isCorrectChangeAvailable(int remaining_change){
    if(remaining_change < 0)
        return false;
    if(remaining_change == 0)
        return true;

    for(auto coin : coins){
        if(isCorrectChangeAvailable(remaining_change - coin)){
            std::cout << coin << " ";
            return true;
        }
    }
    return false;
}



int main (){
    if(isCorrectChangeAvailable(ChangeToBeChecked)){
        std::cout << "Change is available." << std::endl;
    } else {
        std::cout << "Correct change is not available." << std::endl;
    }
}