#pragma once
#ifndef STATISTIC_H
#define STATISTIC_H
#include<array>
class Statistic 
{
private:
	std::array<std::array<int, 15>, 15> table;
public:
	Statistic() 
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				table[i][j] = 0;
			}
		}
	}
	
};

#endif // !STATISTIC_H
