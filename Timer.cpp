#include"Timer.h"
using namespace std;

time_clock::time_clock()
{
	resetTime();
}

long time_clock::getPlayTime()
{
	long playtime = time(0) - start_time;
	return playtime;
}

void time_clock::resetTime()
{
	start_time = time(0);
}