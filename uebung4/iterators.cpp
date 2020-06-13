#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>

// function template for printing contents of containers to std::cout
template<class T>
void printContainer(T& container)
{
	std::cout << "{";
	for(auto element : container)
		std::cout << element << " ";
	std::cout << "}" << std::endl;
}


// TODO 4.2a - Merge front-back pairings of elements of inContainer into outContainer. Do *not* use the []-operator.
template<class T>
void front_back_pairing(T& inContainer, T& outContainer)
{
	auto i_b = inContainer.begin();
	auto i_e = --(inContainer.end());
	int switcher = 1;
	int len = inContainer.size()+1;
	while (len-switcher)
		((switcher++)&1)?outContainer.push_back(*(i_b++)): outContainer.push_back(*(i_e--));
}

// TODO 4.2b - Remove all duplicates from the given container. Do *not* use the []-operator.
template<class T>
void remove_duplicates(T& container)
{
	sort( container.begin(), container.end() );
	container.erase(unique(container.begin(), container.end()), container.end());
}

// TODO 4.2c - Expand the given container by inserting the numerical differences of each element to its neighbors. Do *not* use the []-operator.
template<class T>
void insert_differences(T& container)
{
	assert(container.size() > 1);
	
	int n = container.size();
	container.insert(container.begin(), *(container.begin()) - *(--container.end())); 

	long int delta1, delta2;

	auto element1 = container.begin() +1;
	auto element2 = element1 +1;

	for(int i = 1; i < n; i++){
		delta1 = *element2 - *element1;
		delta2 = *element1 - *element2;

		container.insert(element2, delta1);
		container.insert(element2, delta2); 

		element1 = container.begin() +(n*3) + 1;
		element2 = element1+1;
	}
	
}

void testFrontBackPairingFunctionality()
{
	// define sample data
	std::vector<int> sampleDataInt = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	std::list<std::string> sampleDataString = { "Die", "eines", "ist", "Gebrauch", "der", "Sprache", "in", "sein", "Wortes", "Bedeutung" };

	// test for integer vector
	std::vector<int> helpIntVector;
	front_back_pairing(sampleDataInt, helpIntVector);
	printContainer(sampleDataInt);
	printContainer(helpIntVector);

	// test for string list
	std::list<std::string> helpStringList;
	front_back_pairing(sampleDataString, helpStringList);
	printContainer(sampleDataString);
	printContainer(helpStringList);
}

void testRemoveDuplicateFunctionality()
{
	// define sample data
	std::vector<int> sampleDataInt = { 10, 11, 10, 13, 14, 15, 15, 15, 18, 19, 12, 11, 17 };
	std::vector<std::string> sampleDataString = { "Die", "___", "eines", "ist", "Gebrauch", "der", "Sprache", "in", "sein", "Wortes", "Bedeutung", "Die", "ist", "blabla" };

	// test for integer vector
	printContainer(sampleDataInt);
	remove_duplicates(sampleDataInt);
	printContainer(sampleDataInt);

	// test for string vector
	printContainer(sampleDataString);
	remove_duplicates(sampleDataString);
	printContainer(sampleDataString);
}

void testAddDifferenceFunctionality()
{
	// define sample data
	std::vector<int> sampleDataInt = { 10, 11, 14, 16, 1, 18 };

	// test for integer vector
	printContainer(sampleDataInt);
	insert_differences(sampleDataInt);
	printContainer(sampleDataInt);
}

int main(int argc, char** argv)
{
	testFrontBackPairingFunctionality();
	testRemoveDuplicateFunctionality();
	testAddDifferenceFunctionality();

	return 0;
}
