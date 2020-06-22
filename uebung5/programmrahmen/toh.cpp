#include <cassert>
#include <iostream>
#include <string>
#include <cstddef>
#include <vector>
#include <cstring>
#include <cmath>


static const auto N = 4;

using Tower = std::pair<char, std::vector<int>>;
auto A = Tower(static_cast<unsigned char>('A'), std::vector<int>());
auto B = Tower(static_cast<unsigned char>('B'), std::vector<int>());
auto C = Tower(static_cast<unsigned char>('C'), std::vector<int>());

void print()
{
    #ifdef _WIN32
    std::system("cls");
    #else
    std::system("clear");
    #endif

    // TODO 5.2: Print current state


	std::cout << std::endl << std::endl;
}

void ToH(const int n, Tower &a, Tower &b, Tower &c, int &moves)
{
    // move n plates from a over b to c
    // TODO 5.2: Implement ToH and print
}

int main(int argc, char** argv)
{
    int moves = 0;

    for (int i = N; i > 0; --i)
        A.second.push_back(i);

    print();
    getchar();
    ToH(N, A, B, C, moves);
    std::cout << "minimal number of moves: " << moves << std::endl;

    getchar();
    return 0;
}
