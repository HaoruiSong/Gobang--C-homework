#pragma once
#include"Role.h"
#include<vector>
#include<string>
class point {
public:
	int x, y;
	int scoreCom, scoreHum;
	int score;
	Role role;
	Role attack;
	int step;
	//int min;
	std::vector<point> steps;
	point() 
	{
		x = -1;
		y = -1;
		scoreCom = 0;
		scoreHum = 0;
		score = 0;
		role.role = Role::empty;
		attack.role = Role::empty;
		steps.clear();
		step = 0;
		//min = INT_MAX;
	}
	point(int x_, int y_, int r = Role::empty) 
	{
		x = x_;
		y = y_;
		role = r;
		scoreCom = 0;
		scoreHum = 0;
		score = 0;
	}
};
class node 
{
public:
	int step;
	std::vector<point> steps;
	int score;
	int abcut;
	node() 
	{
		steps.clear();
		abcut = 0;
		score = 0;
		step = 0;
	}
};
class object 
{
public:
	int deep;
	node score;
	int step;
	std::vector<point> steps;
	std::string b;
};
struct rr 
{
	int step = 0;
	int score = 0;
	int abcut = 0;
	std::vector<point> steps;
	object c;
};

/*struct point {
	int x, y;
	int scoreCom, scoreHum;
	int score;
	Role role;
	node v;
	point(){
		x = -1;
		y = -1;
		scoreCom = 0;
		scoreHum = 0;
		score = 0;
		role.role = Role::empty;
	}
	point(int x_, int y_, int r=Role::empty) {
		x = x_;
		y = y_;
		role = r;
		scoreCom = 0;
		scoreHum = 0;
		score = 0;
	}
};*/