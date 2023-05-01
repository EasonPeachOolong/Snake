// Author: Vincent Wang
// Date  : 2016/3/16
// Purpose:
//	简单的码表类，参考
//  http://blog.csdn.net/qq_31175231/article/details/77923212
//  调用方法
//  Stopwatch sw;
// sw.start();
// ....
// sw.stop();
// cout << sw;

#pragma once

#include <chrono>
#include <ctime>
#include <iostream>

class Stopwatch
{
public:
	void start();
	void stop();
	double getMicroseconds() const;
	double getMilliseconds() const;

private:
	using MicroClock = std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds>;

	MicroClock starttime, stoptime;
};

std::ostream &operator<<(std::ostream &os, const Stopwatch &stopwatch);

double operator-(const Stopwatch &a, const Stopwatch &b);
