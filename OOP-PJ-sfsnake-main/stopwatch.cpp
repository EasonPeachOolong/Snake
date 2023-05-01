#include "Stopwatch.h"

void Stopwatch::start()
{
	starttime = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
}

void Stopwatch::stop()
{
	stoptime = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
}

double Stopwatch::getMilliseconds() const
{
	return (stoptime.time_since_epoch().count() - starttime.time_since_epoch().count()) / 1000.0;
}

double Stopwatch::getMicroseconds() const
{
	return (stoptime.time_since_epoch().count() - starttime.time_since_epoch().count());
}

std::ostream &operator<<(std::ostream &os, const Stopwatch &stopwatch)
{
	os << stopwatch.getMilliseconds() << "ms";
	return os;
}

double operator-(const Stopwatch &a, const Stopwatch &b){
	return a.getMilliseconds() - b.getMilliseconds();
}