#pragma once
#ifndef GAME
#define GAME
#include"AI.h"
#include"Point.h"
#include"Config.h"
#include<iostream>
#include"Board.h"
class Game :public Board
{
private:
	AI board;
public:
	
	Game():board()
	{
		board.init();
	}
	void start() 
	{
		board.init();
	}
	point begin() 
	{
		if (board.steps.size() == 0) 
		{
			set(7, 7, Role::com);
			return point(7, 7);
		}
		point p;
		if (Config::opening) 
		{
			p = board.match();
		}
		if (p.x == -1 && p.y == -1) 
		{
			p = board.deeping(Config::searchDeep);
		}
		board.put(p, Role::com, true);
		return p;
	}
	void set(int x, int y, int r) 
	{
		board.put(point(x, y), r, true);
	}
	point turn(int x, int y) 
	{
		set(x, y, Role::hum);
		return begin();
	}
	void back() 
	{
		board.back();
		decrement();
	}
	int check() 
	{
		int temp = board.win();
		if (temp != 0) 
		{
			//std::cout << temp << "yingle" << std::endl;
			return temp;
		}
		return 0;
	}
};
#endif