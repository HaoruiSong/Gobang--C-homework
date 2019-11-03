#include"RANK.h"
#include<iostream>
#include <qstring.h>
using namespace std;

ranklist::ranklist(ranklist & ranklistToCopy)
{
	setname(ranklistToCopy.getname());
	setmove(ranklistToCopy.getmove());
	settime(ranklistToCopy.gettime());
}
ranklist::ranklist(const string& name, int move, long time)
{
	setname(name);
	//setrank(rank);
	setmove(move);
	settime(time);
}

/*void ranklist::setrank(int rank)
{
	this->rank = rank;
}*/

void ranklist::setmove(int move)
{
	this->move = move;
}

void ranklist::settime(long time)
{
	this->time = time;
}

void ranklist::setwin(bool f)
{
	win = f;
}

bool ranklist::getwin()
{
	return win;
}

void ranklist::setname(const string& name)
{
	int length = name.size();
	length = (length < 15 ? length : 14);
	name.copy(this->userName, length);
	userName[length] = '\0';
}

int ranklist::getmove()
{
	return move;
}

long ranklist::gettime()
{
	return time;
}

string ranklist::getname()
{
	return userName;
}

/*int ranklist::getrank()
{
	return rank;
}*/