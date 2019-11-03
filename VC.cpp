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

				// ע�⣬��һ�ֶ������
				// ���Բ���˭�������壬�ȷ�һ�¡�
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
	// �����壬��ֱ�ӷ���
	// ����ע�ⲻҪ��������ͷ��أ����ǰ���������ĵ㶼����һ�飬��Ȼ���ܳ����Լ�����ȴ���ر��˵�����
	if (fives.size()) return fives;
	//ע��Խ����������
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

	// ע����ģ���Ϊ��Ȼ���ĵķֱȻ��ĵͣ��������ķ������ȼ��Ǻͻ���һ���ߵģ��������Գ��ĵ��»�ʤ���߷�
	if (fours.size()) { concat(blockedfours, fours); return fours; }

	//ע��Խ����������
	//��Ϊfours���ܲ����ڣ���ʱ��Ҫ������ blockedfours
	concat(result,blockedfours);
	sort(result.begin(),result.end(),compare4);
	return result;
}

//���ؿ�vector��ʾ��
std::vector<point> VC::max_(Role role, int deep)
{
	//board.logSteps();
	if (deep <= 1) { vector<point> ret; ret.clear(); return ret; }

	vector<point> points = findMax(role, MAX_SCORE);
	if (points.size() && points[0].score >= Score::FOUR) { vector<point> ret; ret.push_back(points[0]); return ret; }//Ϊ�˼���һ�����������ľ����ˡ�
	if (points.size() == 0) { vector<point> ret; ret.clear(); return ret; }
	for (int i = 0; i < points.size(); i++) {
		point p = points[i];
		///ע��put�иĶ�
		put(p, role);
		// ����Ƿ��ض���ĳ��ģ���ô���ü�����
		///���ﲻһ��
		if (!(p.score <= -Score::FIVE)) lastMaxPoint = p;
		vector<point> m = min_(role.reverse(role.role), deep - 1);
		remove(p);
		if (m.size()) {
			if (m[0].x!=-1) {
				m.insert(m.begin(),p); //ע�� unshift �������ص��������鳤�ȣ������������鱾��
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
	if (points.size() && -1 * points[0].score >= Score::FOUR) { vector<point> ret; ret.clear(); return ret; } //Ϊ�˼���һ�����������ľ����ˡ�

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
			vector<point> ret; ret.clear(); return ret; //ֻҪ��һ���ܷ���ס
		}
	}
	srand(time(0));
	vector<point> result = cands[int(floor(cands.size()*(rand()%100/(double)101)))];  //�޷�����ס
	return result;

}
*/
