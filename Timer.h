#ifndef TIMER_H
#define TIMER_H
#include<ctime>
class time_clock
{
public:
	time_clock();
	long getPlayTime();
	void resetTime();
private:
	long start_time;

};
#endif // !Clock.h
