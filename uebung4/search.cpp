#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>

struct Route
{
	int airlineId;
	int sourceId;
	int destinationId;
};

bool operator<(const Route& r1, const Route& r2) {
	return r1.destinationId < r2.destinationId;
}

void importRoutesData(char* path, std::vector<Route>& routes)
{
	std::cout << "Importing routes data.." << std::endl;
	std::ifstream file(path);
	std::string field, line;

	while (std::getline(file, line))
	{
		std::istringstream linestream;
		linestream.str(line);
		int fieldNum = 0;
		Route route;
		route.airlineId = route.sourceId = route.destinationId = -1;

		while (std::getline(linestream, field, ';'))
		{
			try
			{
				switch (fieldNum)
				{
					case 1: // airline id
						route.airlineId = std::stoi(field);
						break;
					case 3: // source id
						route.sourceId = std::stoi(field);
						break;
					case 5: // dest id
						route.destinationId = std::stoi(field);
						break;
					default:
						break;
				}
			}
			catch (const std::invalid_argument&)
			{
				//std::cout << "Couldn't convert field " << currentLineNum << " correctly (invalid argument)!" << std::endl;
				//std::cout << field << std::endl;
			}
			catch (const std::out_of_range&)
			{
				//std::cout << "Couldn't convert field " << currentLineNum << " correctly (out of range)!" << std::endl;
				//std::cout << field << std::endl;
			}

			fieldNum++;
		}

		if (route.airlineId > -1 && route.sourceId > -1 && route.destinationId > -1)
			routes.push_back(route);
	}
}

// TODO 4.3a - Return the number of routes for the given destination id based on a linear search. Count the number of lookups.
int linearSearch(int destID, std::vector<Route>& routes, long long& numLookups)
{
	int numRoutes = 0;
	for(int i = 0; i < routes.size(); i++){
		numLookups++;
		if(routes[i].destinationId == destID){
			numRoutes++;
		}
	}
	return numRoutes;
}

// TODO 4.3a - Evaluate the linearSearch function by calling it for every possible destination id (1..9541).
// Return the number of lookups and the processing time as a pair of long longs.
// Use std::chrono for time measurement.
std::pair<long long, long long> evaluateLinearSearch(std::vector<Route>& routes)
{
	long long numLookups = 0;
	long long duration = 0;
	auto start = std::chrono::steady_clock::now();	
	for(int i = 1; i <= 9541; i++){
		int numRoutes = linearSearch(i, routes, numLookups);
	}
	auto end = std::chrono::steady_clock::now();

	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	return std::make_pair(numLookups, duration);
}

// TODO 4.3b - Return the number of routes for the given destination id based on a binary search. Count the number of lookups.
// The vector should have been sorted before calling this function.
int binarySearch(int destID, std::vector<Route>& routes, long long& numLookups)
{
	int numRoutes = 0;

	int intervalStart = 0;
	int intervalEnd = routes.size() - 1;

	while(intervalStart <= intervalEnd){
		int intervalMid = (intervalStart + intervalEnd) / 2;
		
		if(routes[intervalMid].destinationId < destID){
			numLookups += 1;
			intervalStart = intervalMid + 1;
		} else if (routes[intervalMid].destinationId > destID){
			numLookups += 2;
			intervalEnd = intervalMid - 1;
		} else {
			numLookups += 2;
			intervalStart = intervalMid;
			while(routes[--intervalStart].destinationId == destID) { numRoutes++; numLookups++; }
			while(routes[intervalMid++].destinationId == destID) { numRoutes++; numLookups++; }
			return numRoutes;
		}
	}

	return numRoutes;
}

// TODO 4.3b - Evaluate the binarySearch function by calling it for every possible destination id (1..9541).
// Return the number of lookups and the processing time as a pair of long longs.
// Use std::chrono for time measurement.
// Attention: sorting is *not* part of the evaluation and should be conducted beforehand.
std::pair<long long, long long> evaluateBinarySearch(std::vector<Route>& routes)
{
	long long numLookups = 0;
	long long duration = 0;
	auto start = std::chrono::steady_clock::now();
	std::cout << "Routesize" << routes.size() << std::endl;
	for(int i = 1; i < 9541; i++){
		int numRoutes = binarySearch(i, routes, numLookups);
	}
	auto end = std::chrono::steady_clock::now();

	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	return std::make_pair(numLookups, duration);
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		std::cout << "not enough arguments - USAGE: sort [ROUTE DATASET]" << std::endl;
		return -1;	// invalid number of parameters
	}

	static std::vector<Route> routes;

	std::cout << "Given path to routes.csv: " << argv[1] << std::endl;

	importRoutesData(argv[1], routes);

	auto result = evaluateLinearSearch(routes);
	std::cout << result.first << " - " << result.second << std::endl;

	std::sort(routes.begin(), routes.end());
	result = evaluateBinarySearch(routes);
	std::cout << result.first << " - " << result.second << std::endl;

	return 0;
}
