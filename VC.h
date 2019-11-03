#pragma once
/*#include"AI.h"
#include"Point.h"
#include"Role.h"
#include<vector>
struct cache {
	
};
struct debugCheckmate {
	int cacheCount = 0;
	int totalCount = 0;
	int cacheHit = 0;
};
class VC : public AI {
protected:
	int MAX_SCORE = Score::THREE;
	int MIN_SCORE = Score::FOUR;
	point lastMaxPoint;
public:
	std::vector<point> findMax(Role role, int score);
	std::vector<point> findMin(Role role, int score);
	std::vector<point> max_(Role role, int deep);//返回空vector表示假
	std::vector<point> min_(Role role, int deep);//返回空vector表示假，返回一个（-1，-1）表示真
	std::vector<point> cachev2(std::vector<point>& result, int deep);
};*/