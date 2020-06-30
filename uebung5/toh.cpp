#include <cassert>
#include <iostream>
#include <string>
#include <cstddef>
#include <vector>
#include <cstring>
#include <cmath>

static const auto N = 7;

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

    const int y  = 2 + 1 + (2 * N); // Höhe des Turms mit Boden
    const int x = (N * 2) + 1;  // Breite eines Turms mit Rand rechts

    std::vector<std::string> ausgabe;
    std::string empty;

    // inizialize the playground for string manipulation (aka. string array):
    for(int i = 0; i < x * 3 + 2; i++) empty.append(" ");
    for(int i = 0; i < y; i++) ausgabe.push_back(empty);
    
    const int shift = x +1;
    const int pole_length = y - 2;
    std::vector<Tower> towers {A, B, C};

    for(int offset = 0; offset < 3; offset++)
    {
        // make bottom:
        for(int i = 0; i < x; i++)
        {
            ausgabe[y-2][i + (offset * (x+1))] = char(219);
            ausgabe[y-1][i + (offset * (x+1))] = char(219);
        }
        
        ausgabe[y-1][N] = 'A';
        ausgabe[y-1][(x+1) + N ] = 'B';
        ausgabe[y-1][2 * (x+1) + N ] = 'C';
        
        // make poles:
        for(int i = 0; i < pole_length; i++)
        {
            ausgabe[i][offset * (x+1) + N] = char(219);
        }
        
        // make disks:
        int disk;
        for(int i = 0; i < towers[offset].second.size(); i++)
        {   
            disk = towers[offset].second[i];
            for(int d_size = 0; d_size < disk; d_size++)
            {
                ausgabe[y-4 - (i * 2)][offset * (x+1) + N + d_size + 1] = char(219);
                ausgabe[y-4 - (i * 2)][offset * (x+1) + N - d_size - 1] = char(219);
            }
        }
    }
    
    // make console more "centered" :
    std::cout << "\n\n\n" << std::endl;

    // actually print them towers:
    for(int i = 0; i < y; i++)
        std::cout << ausgabe[i] << std::endl;
	std::cout << std::endl << std::endl;

}

void ToH(const int n, Tower &beg, Tower &aux, Tower &end, int &moves)
{
    // move n plates from a over b to c
    // TODO 5.2: Implement ToH and print
    if(n==1)
	{
        // move disk from beg to end
        moves++;
        end.second.push_back(beg.second.back());
        beg.second.pop_back();
        // print new towers:
        print();
        std::cout << "Move disk " << n << " from " << beg.first << " to " << end.first << std::endl;
        getchar();
        // return 1 as 1 move has been made
    	return ;
    }
    
	
	ToH(n-1, beg ,end ,aux, moves);
    // moving disk n from beg to end:
	moves++;
    end.second.push_back(beg.second.back());
    beg.second.pop_back();
    // print new towers:
    print();
    std::cout << "Move disk " << n << " from " << beg.first << " to " << end.first << std::endl;
    getchar();
    ToH(n-1, aux, beg, end, moves);
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
