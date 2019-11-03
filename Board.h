#pragma once
#ifndef BOARD_H
#define BOARD_H
#include"Point.h"
#include"Zobrist.h"
#include<vector>
#include<array>
#include<string>
#include"Timer.h"
class Board 
{
protected:
	
	time_clock timer;
	int counter;
	int count = 0;
	int total = 0;
	std::array<std::array<int, 15>, 15> comScore;
	std::array<std::array<int, 15>, 15> humScore;
	std::array<std::array<int, 15>, 15> board;
	int scoreCache[3][4][15][15];
	std::array<std::array<int, 15>, 15> statistic;
	Zobrist zobrist;

public:
	///init
	Board():zobrist() 
	{			///checked
		count = 0;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				comScore[i][j] = 0;
				humScore[i][j] = 0;
				statistic[i][j] = 0;
				board[i][j] = 0;
			}
		}
		total = 0;
		memset(scoreCache, 0, sizeof scoreCache);
	}
	void init() 
	{
		zobrist.init();
		count = 0;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				comScore[i][j] = 0;
				humScore[i][j] = 0;
				statistic[i][j] = 0;
				board[i][j] = 0;
			}
		}
		total = 0;
		memset(scoreCache, 0, sizeof scoreCache);
	}
	bool hasNeighbor(point p, int distance, int count);///checked
	///no need to check
	std::string toString() 
	{ 
		std::string s = "";
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				s += board[i][j];
			}
		}
		return s;
	} 

	void increment();
	void decrement();
	void resetTime();
	int getCounter();
	long getTime();


};



#endif // !BOARD_H
