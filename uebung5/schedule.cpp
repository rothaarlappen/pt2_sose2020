#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>


struct Interval
{
	Interval(const int i, const int start, const int length)
	: index(i)
	, start(start)
	, end(start + length - 1)
	{
	}

	int index;
	int start;
	int end;
};

const static int MaxEnd = 74;
const static int MaxDuration = 10;

const static int N = 20;

std::ostream & operator<<(std::ostream& os, const std::vector<Interval>& I)
{

	// TODO 5.3: Implement a nice print function
	for(int i = 0; i < I.size(); i++){
		int j = 0;
		os << "#" << I[i].index << " ";
		if(!(I[i].index/10)) os << " ";
		os << char(221);
		for(; j < I[i].start; j++) os << "-";
		for(; j < I[i].end; j++) os << char(219);
		for(; j < MaxEnd; j++) os << "-";
		os << char(221) << std::endl;
	}
	return os;
}

// creates random data
void randomize(std::vector<Interval>& intervals)
{
	intervals.clear();
	srand(static_cast<unsigned int>(time(0)));

	for (int i = 0; i < N; i++)
	{
		int duration = rand() % MaxDuration + 1;
		int start = rand() % (MaxEnd - duration + 2);

		intervals.push_back(Interval(i, start, duration));
	}
}

bool operator<(const Interval& i1, const Interval& i2) {
	return i1.end < i2.end;
}

// auto sortIntervals(std::vector<Interval>& intervals){
// 	std::sort(intervals.begin(), intervals.end());
// 	return intervals;
// }

void schedule(const std::vector<Interval>& intervals)
{
	std::cout << std::endl << "Intervals (randomized):" << std::endl << intervals;


	// TODO 5.3: Sort intervals
	// std::sort(intervals.begin(), intervals.end());
	auto sorted = intervals;
	std::sort(sorted.begin(), sorted.end());
	std::cout << std::endl << "Intervals (sorted):" << std::endl << sorted;


	// TODO 5.3: Implement greedy scheduling
	auto scheduled = std::vector<Interval>();
	scheduled.push_back(sorted[0]);
	auto iter = sorted.begin()++;
	while(iter != sorted.end()){
		if((*iter).start >= (*(--scheduled.end())).end)
			scheduled.push_back(*iter);
		iter++;
	}

	std::cout << std::endl << "Intervals (scheduled, " << scheduled.size() << " of " << sorted.size() << " possible)"
		<< std::endl << scheduled << std::endl;
}

int main(int argc, char** argv) {

	auto intervals = std::vector<Interval>();

	randomize(intervals);
	schedule(intervals);

	return 0;
}
