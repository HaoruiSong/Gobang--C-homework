//#include "pch.h"
#include "VC.h"
#include<vector>
#include<cmath>
#include<algorithm>
#include<random>
#include<time.h>
using namespace std;
/*
bool compare3(point& a, point& b) {
	return (b.score < a.score);
}
bool compare4(point& a, point& b) {
	return fabs(b.score) < fabs(a.score);
}
std::vector<point> VC::findMax(Role role, int score)
{
	vector<point> result;
	vector<point> fives;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j] == Role::empty) {
				point p(i, j);

				// 注意，防一手对面冲四
				// 所以不管谁能连成五，先防一下。
				if (humScore[p.x][p.y] >= Score::FIVE) {
					p.score = Score::FIVE;
					if (role.role == Role::com) p.score *= -1;
					fives.push_back(p);
				}
				else if (comScore[p.x][p.y] >= Score::FIVE) {
					p.score = Score::FIVE;
					if (role.role == Role::hum) p.score *= -1;
					fives.push_back(p);
				}
				else {

					if ((lastMaxPoint.x==-1 || (i == lastMaxPoint.x || j == lastMaxPoint.y || (fabs(i - lastMaxPoint.x) == fabs(j - lastMaxPoint.y))))) {
						int s = (role.role == Role::com ? comScore[p.x][p.y] : humScore[p.x][p.y]);
						p.score = s;
						if (s >= score) {
							result.push_back(p);
						}
					}
				}
			}
		}
	}
	// 能连五，则直接返回
	// 但是注意不要碰到连五就返回，而是把所有连五的点都考虑一遍，不然可能出现自己能连却防守别人的问题
	if (fives.size()) return fives;
	//注意对结果进行排序
	sort(result.begin(),result.end(),compare3);
	return result;
}

std::vector<point> VC::findMin(Role role, int score)
{
	vector<point> result;
	vector<point> fives;
	vector<point> fours;
	vector<point> blockedfours;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j] == Role::empty) {
				point p(i, j);

				int s1 = (role.role == Role::com ? comScore[p.x][p.y] : humScore[p.x][p.y]);
				int s2 = (role.role == Role::com ? humScore[p.x][p.y] : comScore[p.x][p.y]);
				if (s1 >= Score::FIVE) {
					p.score = -s1;
					vector<point> ret;
					ret.push_back(p);
					return ret;
				}

				if (s2 >= Score::FIVE) {
					p.score = s2;
					fives.push_back(p);
					continue;
				}

				if (s1 >= Score::FOUR) {
					p.score = -s1;
					fours.insert(fours.begin(),p);
					continue;
				}
				if (s2 >= Score::FOUR) {
					p.score = s2;
					fours.push_back(p);
					continue;
				}

				if (s1 >= Score::BLOCKED_FOUR) {
					p.score = -s1;
					blockedfours.insert(blockedfours.begin(), p);
					continue;
				}
				if (s2 >= Score::BLOCKED_FOUR) {
					p.score = s2;
					blockedfours.push_back(p);
					continue;
				}

				if (s1 >= score || s2 >= score) {
					p.x = i;
					p.y = j;
					p.score = s1;
					result.push_back(p);
				}
			}
		}
	}
	if (fives.size()) return fives;

	// 注意冲四，因为虽然冲四的分比活四低，但是他的防守优先级是和活四一样高的，否则会忽略冲四导致获胜的走法
	if (fours.size()) { concat(blockedfours, fours); return fours; }

	//注意对结果进行排序
	//因为fours可能不存在，这时候不要忽略了 blockedfours
	concat(result,blockedfours);
	sort(result.begin(),result.end(),compare4);
	return result;
}

//返回空vector表示假
std::vector<point> VC::max_(Role role, int deep)
{
	//board.logSteps();
	if (deep <= 1) { vector<point> ret; ret.clear(); return ret; }

	vector<point> points = findMax(role, MAX_SCORE);
	if (points.size() && points[0].score >= Score::FOUR) { vector<point> ret; ret.push_back(points[0]); return ret; }//为了减少一层搜索，活四就行了。
	if (points.size() == 0) { vector<point> ret; ret.clear(); return ret; }
	for (int i = 0; i < points.size(); i++) {
		point p = points[i];
		///注意put有改动
		put(p, role);
		// 如果是防守对面的冲四，那么不用记下来
		///这里不一样
		if (!(p.score <= -Score::FIVE)) lastMaxPoint = p;
		vector<point> m = min_(role.reverse(role.role), deep - 1);
		remove(p);
		if (m.size()) {
			if (m[0].x!=-1) {
				m.insert(m.begin(),p); //注意 unshift 方法返回的是新数组长度，而不是新数组本身
				return m;
			}
			else {
				vector<point> ret;
				ret.push_back(p);
				return ret;
			}
		}
	}
	vector<point> ret; ret.clear(); return ret;
}

std::vector<point> VC::min_(Role role, int deep)
{
	int w = win();
	//board.logSteps();
	if (w == role.role) { vector<point> ret; ret.clear(); return ret; }
	if (w == role.reverse(role.role)) { vector<point> ret; ret.push_back(point()); return ret; }
	if (deep <= 1) { vector<point> ret; ret.clear(); return ret; }
	vector<point> points = findMin(role, MIN_SCORE);
	if (points.size() == 0) { vector<point> ret; ret.clear(); return ret; }
	if (points.size() && -1 * points[0].score >= Score::FOUR) { vector<point> ret; ret.clear(); return ret; } //为了减少一层搜索，活四就行了。

	vector<vector<point>> cands;
	for (int i = 0; i < points.size(); i++) {
		point p = points[i];
		put(p, role);
		//lastMinPoint = p;
		vector<point> m = max_(role.reverse(role.role), deep - 1);
		remove(p);
		if (m.size()) {
			m.insert(m.begin(), p);
			cands.push_back(m);
			continue;
		}
		else {
			vector<point> ret; ret.clear(); return ret; //只要有一种能防守住
		}
	}
	srand(time(0));
	vector<point> result = cands[int(floor(cands.size()*(rand()%100/(double)101)))];  //无法防守住
	return result;

}
*/
