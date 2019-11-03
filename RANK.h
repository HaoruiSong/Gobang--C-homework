#pragma once
#ifndef RANK
#define RANK
#include<string>
class ranklist
{
private:
	char userName[25];
	long time;
	int move;
	bool win;
	//int rank;

public:
	ranklist(const std::string& = "", int = 0, long = 0);//default constructor
	ranklist(ranklist & ranklistToCopy);
	void setname(const std::string & namev);
	void setmove(int);
	void settime(long);
	void setwin(bool);
	bool getwin();
	//void setrank(int);

	std::string getname();
	//int getrank();
	int getmove();
	long gettime();

};
#endif // !RANK
