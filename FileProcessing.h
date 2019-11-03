#pragma once
#ifndef FILE_PROCESSING_H
#define FILE_PROCESSING_H
#include"RANK.h"
#include<fstream>
#include <iostream>
#include <string>

extern void initialize_list(std::string fileName)
{
	std::ofstream outlist(fileName, std::ios::out | std::ios::binary);
	if (!outlist)
	{
		//cerr << "Fail to creat a list" << endl;
		//exit(EXIT_FAILURE);
	}

	ranklist blank;
	int counter = 10;
	while (1)
	{
		outlist.write(reinterpret_cast<const char *>(&blank),
			sizeof(ranklist));
		counter--;
		if (counter < 1)
			break;
	}
}

extern ranklist read_one(int rank, std::string fileName)
{
	ranklist container;
	std::ifstream inlist(fileName, std::ios::in | std::ios::binary);
	if (!inlist)
	{
		//cerr << "Fail to read the file." << endl;
		//exit(EXIT_FAILURE);
	}
	inlist.seekg((rank - 1) * sizeof(ranklist));
	inlist.read(reinterpret_cast<char *>(&container),
		sizeof(container));

	return container;
}

extern bool decide_write(int move, long time, std::string fileName)
{
	int buttom_move = read_one(10, fileName).getmove();
	//cout << "The 10th move is " << buttom_move << endl;

	if (buttom_move == 0)
		return true;

	if (move < buttom_move)
		return true;

	if (move == buttom_move)
	{
		long buttom_time = read_one(10, fileName).gettime();
		if (time < buttom_time)
			return true;
	}

	return false;
}

#endif // !FILE_PROCESSING_H

