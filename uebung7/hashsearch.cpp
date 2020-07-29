#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const int64_t p = 257; // prime close to the magnitude of the alphabet
const int64_t m = 1e9 + 9; // magnitude hash table

void nextHash(int64_t &hash, const int64_t &p_pow, const char &c_old, const char &c_new)
{
    // char leaving the window:
    hash = (hash - ((p_pow * c_old) % m)) % m;
    hash = (hash < 0) ? hash+m : hash;
    // char entering the window:
    hash = (hash * p) % m;
    hash = (hash + ((p * c_new) % m)) % m;
}

std::vector<int> search(std::string pattern, std::string text)
{
    std::vector<int> positions {};
    if (text.length() < pattern.length())
    {
        return positions;
    }

    int64_t patternLength = pattern.length();
    int64_t textLength = text.length();

    // computation of p_pow based on size of searched string:
    int64_t p_pow = 1;
    for(int i = 0; i < patternLength; i++) {
        p_pow = (p_pow * p) % m;
    }

    // compute patternHash, the hash value of the pattern and the first
    // substringHash.
    int64_t patternHash = 0;
    int64_t substringHash = 0;
    for(int i = 0; i < patternLength; i++){
        patternHash = (((patternHash + pattern[i]) % m ) * p )%m;
    
        substringHash = (((substringHash + text[i]) % m ) * p )%m;
    }
    
    // this could perhaps be moved into the loop, checks the first generated hashs:
    if(substringHash == patternHash){
        positions.push_back(0);
    }
    
    // loop through the remainig chars and check if equal to searched string:
    for(int i = 1; i < textLength-patternLength; i++){
        nextHash(substringHash, p_pow, text[i-1],text[i+patternLength-1]);
        if(substringHash == patternHash){
            positions.push_back(i);
        }
    }
    

    return positions;
}

std::vector<std::string> loadTexts(std::string filename)
{
    std::ifstream file(filename);
    std::string line;

    std::vector<std::string> lines;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    return lines;
}

int main(int argc, char **argv)
{
    auto texts = loadTexts("loremipsum.txt");
    std::string pattern = "ipsum";

    std::cout << "Searching for '" << pattern << "'" << std::endl;

    std::cout << "Found at positions: ";
    int counter = 0;
    for(int t = 0; t < texts.size(); ++t)
    {
        auto indices = search(pattern, texts[t]);
        for (int i : indices)
        {
            std::cout << t << "," << i << " ";
            counter++;
        }
    }
    std::cout << std::endl;
    std::cout << "Number of occurences: " << counter << std::endl; // Expected occurences of 'ipsum': 57
    return 0;
}
