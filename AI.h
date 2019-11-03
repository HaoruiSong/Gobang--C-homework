#pragma once
#ifndef AI_H
#define AI_H
#include"Board.h"
#include"Role.h"
#include"Point.h"
#include"Score.h"
#include<vector>
#include<map>
#include"Config.h"
class AI : public Board 
{
protected:
	point _last;
	std::vector<point> currentSteps;
	std::vector<point> allSteps;
	int cacheGet;
	int comMaxScore;
	int humMaxScore;
	int ABcut;
	int PVcut;
	const static int MAX = Score::FIVE;
	const static int MIN = (-1)*Score::FIVE;
	std::map<unsigned, object> Cache;
	std::vector<point> fives;
	std::vector<point> comfours;
	std::vector<point> humfours;
	std::vector<point> comblockedfours;
	std::vector<point> humblockedfours;
	std::vector<point> comtwothrees;
	std::vector<point> humtwothrees;
	std::vector<point> comthrees;
	std::vector<point> humthrees;
	std::vector<point> comtwos;
	std::vector<point> humtwos;
	std::vector<point> neighbors;

public:
	std::vector<point> steps;
	AI():Board() 
	{
		_last.x = -1;
		_last.y = -1;
		cacheGet = 0;
		initScore();
		comMaxScore = 0;
		humMaxScore = 0;
		currentSteps.clear();
		allSteps.clear();
		///stepsTail.clear();
		steps.clear();
	}
	void init() 
	{
		cacheGet = 0;
		Board::init();
		_last.x = -1;
		_last.y = -1;
		initScore();
		comMaxScore = 0;
		humMaxScore = 0;
		currentSteps.clear();
		allSteps.clear();
		///stepsTail.clear();
		steps.clear();
	}
	static void concat(std::vector<point>& v1, std::vector<point>& v2, std::vector<point>& v3);
	static void concat(std::vector<point>& v1, std::vector<point>& v2);
	static bool compare(point& a, point& b);
	int scorePoint(point p, Role role, int dir = -1);	///not fully checked
	int countToScore(int, int, int); ///almost fully checked
	void reset(int&, int&, int&, int&);///checked
	void initScore();	 ///checked
	void updateScore(point p);	///checked
	void update(point, int dir = -1);	///checked
	void put(point p, Role r, bool record = false);///checked
	point last(Role r);	///checked
	void remove(point p);///checked
	void back();	///checked
	///void forward();
	int evaluate(Role);		///checked
	int fixScore(int);		///checked
	std::vector<point> gen(Role, bool=false, bool=false);///checked
	void cache(int, node&);///checked attention
	///void cache(int, rr&);
	node r(int deep, int alpha, int beta, Role role, int step, std::vector<point> &steps, int spread);///checked attention
	int negamax(std::vector<point> &candidate, int deep, int alpha, int beta);///checked attention
	point deeping(int deep=-1); ///checked attention
	point huayue();
	point puyue();
	point match();//(-1, -1)±Ì æfalse°£
	bool isfive(const point& p, Role role);///not fully checked
	int win();///checked
};

#endif // !AI_H 
