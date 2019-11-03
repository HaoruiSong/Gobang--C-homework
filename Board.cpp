#include<iostream>
#include"Board.h"
#include"Point.h"
#include"Role.h"
//#include"pch.h"
#include"AI.h"
using namespace std;


bool Board::hasNeighbor(point p, int distance, int cnt) 
{
	int startX = p.x - distance;
	int endX = p.x + distance;
	int startY = p.y - distance;
	int endY = p.y + distance;
	for (int i = startX; i <= endX; i++) 
	{
		if (i < 0 || i >= 15) continue;
		for (int j = startY; j <= endY; j++) 
		{
			if (j < 0 || j >= 15) continue;
			if (i == p.x && j == p.y) continue;
					if (board[i][j] != Role::empty) 
					{
						cnt--;
						if (cnt <= 0) return true;
					}
		}
	}
	return false;
}


void Board::increment()
{
	++counter;
}

void Board::decrement()
{
	--counter;
}

void Board::resetTime()
{
	timer.resetTime();
}

int Board::getCounter()
{
	return counter;
}

long Board::getTime()
{
	return timer.getPlayTime();
}
