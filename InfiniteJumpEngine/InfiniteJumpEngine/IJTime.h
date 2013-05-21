#pragma once
#ifndef TIME_H
#define TIME_H
#include <time.h>

#pragma once
class IJTime
{
public:
	IJTime(void);
	~IJTime(void);
	long double getSeconds(){return ((long double)internal)/CLOCKS_PER_SEC;}
	long double getMilliseconds(){return ((long double)internal)*1000.0/CLOCKS_PER_SEC;}
	long int getTicks(){return (long int)internal;}
	const IJTime operator-(const IJTime&);
	void reset(){internal = clock();}
protected:
	clock_t internal;
};
#endif TIME_H
