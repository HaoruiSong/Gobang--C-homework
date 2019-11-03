//#include"pch.h"
#include<iostream>
#include<vector>
#include<array>
#include<cmath>
#include<algorithm>
#include"Score.h"
#include"AI.h"
#include"statistic.h"
#include"Config.h"
using namespace std;

bool equal(double a, double b = 0.01) 
{
	if (b == 0)
		b = 0.01;
	return b >= 0 ? ((a >= b / 1.15) && (a <= b * 1.15))
		: ((a >= b * 1.15) && (a <= b / 1.15));
}
bool greatThan(double a, double b) {
	return b >= 0 ? (a >= (b + 0.1) * 1.15) : (a >= (b + 0.1) / 1.15); // 注意处理b为0的情况，通过加一个0.1 做简单的处理
}
bool greatOrEqualThan(double a, double b) {
	return equal(a, b) || greatThan(a, b);
}
bool littleThan(double a, double b) {
	return b >= 0 ? (a <= (b - 0.1) / 1.15) : (a <= (b - 0.1) * 1.15);
}
bool littleOrEqualThan(double a, double b) {
	return equal(a, b) || littleThan(a, b);
}

bool containPoint(vector<point>& vec, point p) 
{
	for (int i = 0; i < vec.size(); i++) 
	{
		point a = vec[i];
		if (a.x == p.x && a.y == p.y) return true;
	}
	return false;
}

bool pointEqual(const point &a, const point &b) 
{
	return a.x == b.x && a.y == b.y;
}

int round(int score) 
{
	int neg = score < 0 ? -1 : 1;
	int abs = fabs(score);
	if (abs <= Score::ONE / 2) 
		return 0;
	if (abs <= Score::TWO / 2 && abs > Score::ONE / 2) 
		return neg * Score::ONE;
	if (abs <= Score::THREE / 2 && abs > Score::TWO / 2) 
		return neg * Score::TWO;
	if (abs <= Score::THREE * 1.5 && abs > Score::THREE / 2) 
		return neg * Score::THREE;
	if (abs <= Score::FOUR / 2 && abs > Score::THREE * 1.5) 
		return neg * Score::THREE * 2;
	if (abs <= Score::FIVE / 2 && abs > Score::FOUR / 2) 
		return neg * Score::FOUR;
	return neg * Score::FIVE;
}


void AI::concat(std::vector<point>& v1, std::vector<point>& v2, std::vector<point>& ret)
{
	ret.insert(ret.end(), v1.begin(), v1.end());
	ret.insert(ret.end(), v2.begin(), v2.end());
}

void AI::concat(std::vector<point>& v1, std::vector<point>& ret)
{
	ret.insert(ret.end(), v1.begin(), v1.end());
}

bool AI::compare(point & a, point & b)
{
	return (a.score > b.score);
}

int AI::scorePoint(point p, Role role, int dir)
{
	int result = 0;
	int empty = 0;
	int cnt = 0, block = 0, secondCount = 0;
	if (dir == -1 || dir == 0) 
	{
		reset(cnt, block, empty, secondCount);
		// -
		for (int i = p.y + 1; true; i++) 
		{
			if (i >= 15) 
			{
				block++;//block就是有没有被堵上
				break;
			}
			int t = board[p.x][i];
			if (t == Role::empty) {
				if (empty == -1 && i < 15 - 1 && board[p.x][i + 1] == role.role) 
				{
					empty = cnt;
					continue;
				}
				else 
				{
					break;
				}
			}
			if (t == role.role) 
			{
				cnt++;
				continue;
			}
			else 
			{
				block++;
				break;
			}
		}

		for (int i = p.y - 1; true; i--) 
		{
			if (i < 0) 
			{
				block++;
				break;
			}
			int t = board[p.x][i];
			if (t == Role::empty) 
			{
				if (empty == -1 && i > 0 && board[p.x][i - 1] == role.role) 
				{
					empty = 0; //注意这里是0，因为是从右往左走的
					continue;
				}
				else 
				{
					break;
				}
			}
			if (t == role.role) 
			{
				secondCount++;
				empty != -1 && empty++; //注意这里，如果左边又多了己方棋子，那么empty的位置就变大了
				continue;
			}
			else 
			{
				block++;
				break;
			}
		}

		cnt += secondCount;
		scoreCache[role.role][0][p.x][p.y] = countToScore(cnt, block, empty);
	}
	result += scoreCache[role.role][0][p.x][p.y];

	if (dir == -1 || dir == 1) 
	{
		// |
		reset(cnt, block, empty, secondCount);

		for (int i = p.x + 1; true; i++) 
		{
			if (i >= 15) 
			{
				block++;
				break;
			}
			int t = board[i][p.y];
			if (t == Role::empty) 
			{
				if (empty == -1 && i < 15 - 1 && board[i + 1][p.y] == role.role) 
				{
					empty = cnt;
					continue;
				}
				else 
				{
					break;
				}
			}
			if (t == role.role) 
			{
				cnt++;
				continue;
			}
			else 
			{
				block++;
				break;
			}
		}

		for (int i = p.x - 1; true; i--) 
		
		{
			if (i < 0) {
				block++;
				break;
			}
			int t = board[i][p.y];
			if (t == Role::empty) 
			{
				if (empty == -1 && i > 0 && board[i - 1][p.y] == role.role) 
				{
					empty = 0;
					continue;
				}
				else 
				{
					break;
				}
			}
			if (t == role.role) 
			{
				secondCount++;
				empty != -1 && empty++;  //注意这里，如果左边又多了己方棋子，那么empty的位置就变大了
				continue;
			}
			else 
			{
				block++;
				break;
			}
		}

		cnt += secondCount;

		scoreCache[role.role][1][p.x][p.y] = countToScore(cnt, block, empty);
	}
	result += scoreCache[role.role][1][p.x][p.y];

	// \

	if (dir == -1 || dir == 2) 
	{
		reset(cnt, block, empty, secondCount);

		for (int i = 1; true; i++) 
		{
			int x = p.x + i, y = p.y + i;
			if (x >= 15 || y >= 15) 
			{
				block++;
				break;
			}
			int t = board[x][y];
			if (t == Role::empty) 
			{
				if (empty == -1 && (x < 15 - 1 && y < 15 - 1) && board[x + 1][y + 1] == role.role) 
				{
					empty = cnt;
					continue;
				}
				else 
				{
					break;
				}
			}
			if (t == role.role) 
			{
				cnt++;
				continue;
			}
			else 
			{
				block++;
				break;
			}
		}

		for (int i = 1; true; i++) 
		{
			int x = p.x - i, y = p.y - i;
			if (x < 0 || y < 0) 
			{
				block++;
				break;
			}
			int t = board[x][y];
			if (t == Role::empty) 
			{
				if (empty == -1 && (x > 0 && y > 0) && board[x - 1][y - 1] == role.role) 
				{
					empty = 0;
					continue;
				}
				else 
				{
					break;
				}
			}
			if (t == role.role) 
			{
				secondCount++;
				empty != -1 && empty++;  //注意这里，如果左边又多了己方棋子，那么empty的位置就变大了
				continue;
			}
			else 
			{
				block++;
				break;
			}
		}

		cnt += secondCount;
		scoreCache[role.role][2][p.x][p.y] = countToScore(cnt, block, empty);
	}
	result += scoreCache[role.role][2][p.x][p.y];

	// /
	if (dir == -1 || dir == 3) 
	{
		reset(cnt, block, empty, secondCount);

		for (int i = 1; true; i++) 
		{
			int x = p.x + i, y = p.y - i;
			if (x < 0 || y < 0 || x >= 15 || y >= 15) 
			{
				block++;
				break;
			}
			int t = board[x][y];
			if (t == Role::empty) 
			{
				if (empty == -1 && (x < 15 - 1 && y < 15 - 1) && (y > 0) && board[x + 1][y - 1] == role.role) 
				{
					empty = cnt;
					continue;
				}
				else 
				{
					break;
				}
			}
			if (t == role.role) 
			{
				cnt++;
				continue;
			}
			else 
			{
				block++;
				break;
			}
		}

		for (int i = 1; true; i++) 
		{
			int x = p.x - i, y = p.y + i;
			if (x < 0 || y < 0 || x >= 15 || y >= 15) 
			{
				block++;
				break;
			}
			int t = board[x][y];
			if (t == Role::empty) 
			{
				if (empty == -1 && (x > 0 && y > 0) && (x - 1) > 0 && (x - 1) < 15 && (y + 1) > 0 && (y + 1) < 15 && board[x - 1][y + 1] == role.role) {
					empty = 0;
					continue;
				}
				else 
				{
					break;
				}
			}
			if (t == role.role) 
			{
				secondCount++;
				empty != -1 && empty++;  //注意这里，如果左边又多了己方棋子，那么empty的位置就变大了
				continue;
			}
			else 
			{
				block++;
				break;
			}
		}

		cnt += secondCount;

		scoreCache[role.role][3][p.x][p.y] = countToScore(cnt, block, empty);///这里我没有加进C++里
	}
	result += scoreCache[role.role][3][p.x][p.y];
	return result;
}

int AI::countToScore(int cnt, int block, int empty)
{

	//没有空位
	if (empty <= 0) 
	{
		if (cnt >= 5) return Score::FIVE;
		if (block == 0) 
		{
			switch (cnt) 
			{
			case 1: return Score::ONE;
			case 2: return Score::TWO;
			case 3: return Score::THREE;
			case 4: return Score::FOUR;
			}
		}

		if (block == 1) 
		{
			switch (cnt) 
			{
			case 1: return Score::BLOCKED_ONE;
			case 2: return Score::BLOCKED_TWO;
			case 3: return Score::BLOCKED_THREE;
			case 4: return Score::BLOCKED_FOUR;
			}
		}

	}
	else if (empty == 1 || empty == cnt - 1) 
	{
		//第1个是空位
		if (cnt >= 6) 
		{
			return Score::FIVE;
		}
		if (block == 0) 
		{
			switch (cnt) 
			{
			case 2: return Score::TWO / 2;
			case 3: return Score::THREE;
			case 4: return Score::BLOCKED_FOUR;
			case 5: return Score::FOUR;
			}
		}

		if (block == 1) 
		{
			switch (cnt) 
			{
			case 2: return Score::BLOCKED_TWO;
			case 3: return Score::BLOCKED_THREE;
			case 4: return Score::BLOCKED_FOUR;
			case 5: return Score::BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 2 || empty == cnt - 2) 
	{
		//第二个是空位
		if (cnt >= 7) 
		{
			return Score::FIVE;
		}
		if (block == 0) 
		{
			switch (cnt) 
			{
			case 3: return Score::THREE;
			case 4:
			case 5: return Score::BLOCKED_FOUR;
			case 6: return Score::FOUR;
			}
		}

		if (block == 1) 
		{
			switch (cnt) 
			{
			case 3: return Score::BLOCKED_THREE;
			case 4: return Score::BLOCKED_FOUR;
			case 5: return Score::BLOCKED_FOUR;
			case 6: return Score::FOUR;
			}
		}

		if (block == 2) 
		{
			switch (cnt) 
			{
			case 4:
			case 5:
			case 6: return Score::BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 3 || empty == cnt - 3) 
	{
		if (cnt >= 8) 
		{
			return Score::FIVE;
		}
		if (block == 0) 
		{
			switch (cnt) 
			{
			case 4:
			case 5: return Score::THREE;
			case 6: return Score::BLOCKED_FOUR;
			case 7: return Score::FOUR;
			}
		}

		if (block == 1) 
		{
			switch (cnt) 
			{
			case 4:
			case 5:
			case 6: return Score::BLOCKED_FOUR;
			case 7: return Score::FOUR;
			}
		}

		if (block == 2) 
		{
			switch (cnt) 
			{
			case 4:
			case 5:
			case 6:
			case 7: return Score::BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 4 || empty == cnt - 4) 
	{
		if (cnt >= 9) 
		{
			return Score::FIVE;
		}
		if (block == 0) 
		{
			switch (cnt) 
			{
			case 5:
			case 6:
			case 7:
			case 8: return Score::FOUR;
			}
		}

		if (block == 1) 
		{
			switch (cnt) 
			{
			case 4:
			case 5:
			case 6:
			case 7: return Score::BLOCKED_FOUR;
			case 8: return Score::FOUR;
			}
		}

		if (block == 2) 
		{
			switch (cnt) 
			{
			case 5:
			case 6:
			case 7:
			case 8: return Score::BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 5 || empty == cnt - 5) 
	{
		return Score::FIVE;
	}

	return 0;
}

void AI::reset(int &cnt, int &block, int &empty, int &secondCount)
{
	cnt = 1;
	block = 0;
	empty = -1;
	secondCount = 0;  //另一个方向的count
}

void AI::initScore()
{
	//board是数组
	for (int i = 0; i < 15; i++) 
	{
		for (int j = 0; j < 15; j++) 
		{
			// 空位，对双方都打分
			if (board[i][j] == Role::empty) 
			{
				if (hasNeighbor(point(i, j), 2, 2)) 
				{ //必须是有邻居的才行
					int cs = scorePoint(point(i, j), Role(Role::com));
					int hs = scorePoint(point(i, j), Role(Role::hum));
					comScore[i][j] = cs;
					humScore[i][j] = hs;
				}

			}
			else if (board[i][j] == Role::com) 
			{ // 对电脑打分，玩家此位置分数为0
				comScore[i][j] = scorePoint(point(i, j), Role(Role::com));
				humScore[i][j] = 0;
			}
			else if (board[i][j] == Role::hum) 
			{ // 对玩家打分，电脑位置分数为0
				humScore[i][j] = scorePoint(point(i, j), Role(Role::hum));
				comScore[i][j] = 0;
			}
		}
	}
}

void AI::update(point p, int dir)
{
	int role = board[p.x][p.y];
	if (role != Role::hum) 
	{
		int cs = scorePoint(p, Role(Role::com), dir);
		comScore[p.x][p.y] = cs;
		statistic[p.x][p.y] += cs;
	}
	else comScore[p.x][p.y] = 0;
	if (role != Role::com) 
	{
		int hs = scorePoint(p, Role(Role::hum), dir);
		humScore[p.x][p.y] = hs;
		statistic[p.x][p.y] += hs;
	}
	else humScore[p.x][p.y] = 0;

}

void AI::updateScore(point p)
{
	int radius = 6;  /// 6
	// 无论是不是空位 都需要更新
	// -
	for (int i = -radius; i <= radius; i++) 
	{
		int x = p.x, y = p.y + i;
		if (y < 0) continue;
		if (y >= 15) break;
		update(point(x, y), 0);
	}

	// |
	for (int i = -radius; i <= radius; i++) 
	{
		int x = p.x + i, y = p.y;
		if (x < 0) continue;
		if (x >= 15) break;
		update(point(x, y), 1);
	}

	//  \

	for (int i = -radius; i <= radius; i++) 
	{
		int x = p.x + i, y = p.y + i;
		if (x < 0 || y < 0) continue;
		if (x >= 15 || y >= 15) break;
		update(point(x, y), 2);
	}

	// /
	for (int i = -radius; i <= radius; i++) 
	{
		int x = p.x + i, y = p.y - i;
		if (x < 0 || y < 0) continue;
		if (x >= 15 || y >= 15) continue;
		update(point(x, y), 3);
	}

}


void AI::put(point p, Role r, bool record)
{
	if (Config::debug) 
	{
		//cout << "put [" << p.x << ", " << p.y << "]  " << r.role << endl;
	}
	p.role = r;		///??
	board[p.x][p.y] = r.role;
	zobrist.go(p, r);
	if (record) steps.push_back(p);	///这里改了一下
	updateScore(p);
	allSteps.push_back(p);
	///currentSteps.push_back(p);
	///stepsTail.clear();
	///count++;

}

point AI::last(Role r)
{
	for (int i = allSteps.size() - 1; i >= 0; i--) 
	{
		point p = allSteps[i];
		if (board[p.x][p.y] == r.role) return p;
	}
	return point(-1, -1);
}

void AI::remove(point p) 
{
	int r = board[p.x][p.y];
	if (Config::debug) 
	{
		//cout << "remove [" << p.x << ", " << p.y << "] " << r << endl;
	}
	zobrist.go(p, Role(r));
	board[p.x][p.y] = Role::empty;
	updateScore(p);
	allSteps.pop_back();
	///currentSteps.pop_back();
	///count--;
}

void AI::back() 
{
	if (allSteps.size() < 2) return;

	point s = steps[steps.size() - 1];
	steps.pop_back();
	zobrist.go(s, board[s.x][s.y]);
	board[s.x][s.y] = Role::empty;
	updateScore(s);
	allSteps.pop_back();

	point s_ = steps[steps.size() - 1];
	steps.pop_back();
	zobrist.go(s_, board[s_.x][s_.y]);
	board[s_.x][s_.y] = Role::empty;
	updateScore(s);
	allSteps.pop_back();

	
}


int AI::evaluate(Role r) 
{
	comMaxScore = 0;
	humMaxScore = 0;

	for (int i = 0; i < 15; i++) 
	{
		for (int j = 0; j < 15; j++) 
		{
			if (board[i][j] == Role::com) 
			{
				comMaxScore += fixScore(comScore[i][j]);
			}
			else if (board[i][j] == Role::hum) {
				humMaxScore += fixScore(humScore[i][j]);
			}
		}
	}
	int result = (r.role == Role::com ? 1 : -1) * (comMaxScore - humMaxScore);

	return result;

}


int AI::fixScore(int type) 
{
	if (type < Score::FOUR && type >= Score::BLOCKED_FOUR) 
	{

		if (type >= Score::BLOCKED_FOUR && type < (Score::BLOCKED_FOUR + Score::THREE)) 
		{
			//单独冲四，意义不大
			return Score::THREE;
		}
		else if (type >= Score::BLOCKED_FOUR + Score::THREE && type < Score::BLOCKED_FOUR * 2) 
		{
			return Score::FOUR;  //冲四活三，比双三分高，相当于自己形成活四
		}
		else 
		{
			//双冲四 比活四分数也高
			return Score::FOUR * 2;
		}
	}
	return type;
}

vector<point> AI::gen(Role role, bool onlyThrees, bool starSpread) 
{
	fives.clear();
	comfours.clear();
	humfours.clear();
	comblockedfours.clear();
	humblockedfours.clear();
	comtwothrees.clear();
	humtwothrees.clear();
	comthrees.clear();
	humthrees.clear();
	comtwos.clear();
	humtwos.clear();
	neighbors.clear();
	point lastPoint1, lastPoint2;
	int startI = 0, startJ = 0, endI = board.size() - 1, endJ = board.size() - 1;
	if (starSpread && Config::star) 
	{

		int i = allSteps.size() - 1;
		while (lastPoint1.x != -1 && i >= 0) 
		{
			point p = allSteps[i];
			if (p.role.role != role.role && p.attack.role != role.role) lastPoint1 = p;
			i -= 2;
		}

		if (lastPoint1.x != -1) 
		{
			lastPoint1 = allSteps[0].role.role != role.role ? allSteps[0] : allSteps[1];
		}

		i = allSteps.size() - 2;
		while (lastPoint2.x != -1 && i >= 0) 
		{
			point p = allSteps[i];
			if (p.attack.role == role.role) lastPoint2 = p;
			i -= 2;
		}

		if (lastPoint2.x != -1) 
		{
			lastPoint2 = allSteps[0].role.role == role.role ? allSteps[0] : allSteps[1];
		}
		startI = min(lastPoint1.x - 5, lastPoint2.x - 5);
		startJ = min(lastPoint1.y - 5, lastPoint2.y - 5);
		startI = max(0, startI);
		startJ = max(0, startJ);
		endI = max(lastPoint1.x + 5, lastPoint2.x + 5);
		endJ = max(lastPoint1.y + 5, lastPoint2.y + 5);
		endI = min(14, endI);
		endJ = min(14, endJ);
	}



	for (int i = startI; i <= endI; i++) 
	{
		for (int j = startJ; j <= endJ; j++) 
		{
			if (board[i][j] == Role::empty) 
			{

				if (allSteps.size() < 6) 
				{
					if (!hasNeighbor(point(i, j), 1, 1)) continue;
				}
				else if (!hasNeighbor(point(i, j), 2, 2)) continue;
				point p;
				p.x = i; p.y = j;
				int scoreHum = p.scoreHum = humScore[i][j];
				int scoreCom = p.scoreCom = comScore[i][j];
				int maxScore = max(scoreCom, scoreHum);
				p.score = maxScore;
				p.role.role = role.role;

				if (scoreCom >= scoreHum) p.attack.role = Role::com; // 进攻点
				else p.attack.role = Role::hum; // 防守点

				total++;
				if (starSpread && Config::star) 
				{

					if ((fabs(i - lastPoint1.x) > 5 || fabs(j - lastPoint1.y) > 5) && 
						(fabs(i - lastPoint2.x) > 5 || fabs(j - lastPoint2.y) > 5)) 
					{
						count++;
						continue;
					}
					if (
						maxScore >= Score::FIVE ||
						(i == lastPoint1.x || j == lastPoint1.y || (fabs(i - lastPoint1.x) == fabs(j - lastPoint1.y)))
						|| (i == lastPoint2.x || j == lastPoint2.y || (fabs(i - lastPoint2.x) == fabs(j - lastPoint2.y)))) 
					{

					}
					else {
						count++;
						continue;
					}
				}

				if (scoreCom >= Score::FIVE) 
				{
					fives.push_back(p);
				}
				else if (scoreHum >= Score::FIVE) 
				{
					fives.push_back(p);
				}
				else if (scoreCom >= Score::FOUR) 
				{
					comfours.push_back(p);
				}
				else if (scoreHum >= Score::FOUR) 
				{
					humfours.push_back(p);
				}
				else if (scoreCom >= Score::BLOCKED_FOUR) 
				{
					comblockedfours.push_back(p);
				}
				else if (scoreHum >= Score::BLOCKED_FOUR) 
				{
					humblockedfours.push_back(p);
				}
				else if (scoreCom >= 2 * Score::THREE) 
				{
					//能成双三也行
					comtwothrees.push_back(p);
				}
				else if (scoreHum >= 2 * Score::THREE) 
				{
					humtwothrees.push_back(p);
				}
				else if (scoreCom >= Score::THREE) 
				{
					comthrees.push_back(p);
				}
				else if (scoreHum >= Score::THREE) 
				{
					humthrees.push_back(p);
				}
				else if (scoreCom >= Score::TWO) 
				{
					comtwos.insert(comtwos.begin(), p);
				}
				else if (scoreHum >= Score::TWO) 
				{
					humtwos.insert(humtwos.begin(), p);
				}
				else 
				{
					neighbors.push_back(p);
				}
			}
		}
	}

	if (fives.size()) return fives;

	if (role.role == Role::com && comfours.size()) return comfours;
	if (role.role == Role::hum && humfours.size()) return humfours;

	if (role.role == Role::com && humfours.size() && !comblockedfours.size()) return humfours;
	if (role.role == Role::hum && comfours.size() && !humblockedfours.size()) return comfours;

	vector<point> fours;
	role.role == Role::com ? concat(comfours, humfours, fours) : concat(humfours, comfours, fours);
	vector<point> blockedfours;
	role.role == Role::com ? concat(comblockedfours, humblockedfours, blockedfours) : 
		concat(humblockedfours, comblockedfours, blockedfours);
	if (fours.size()) 
	{
		vector<point> ret;
		concat(fours, blockedfours, ret);
		return ret;
	}

	vector<point> result;
	if (role.role == Role::com) 
	{
		concat(comtwothrees, humtwothrees, result);
		concat(comblockedfours, result);
		concat(humblockedfours, result);
		concat(comthrees, result);
		concat(humthrees, result);
	}
	if (role.role == Role::hum) 
	{
		concat(humtwothrees, comtwothrees, result);
		concat(humblockedfours, result);
		concat(comblockedfours, result);
		concat(humthrees, result);
		concat(comthrees, result);
	}

	if (comtwothrees.size() || humtwothrees.size()) 
	{
		return result;
	}


	if (onlyThrees) 
	{
		return result;
	}


	vector<point> twos;
	if (role.role == Role::com) 
		concat(comtwos, humtwos, twos);
	else 
		concat(humtwos, comtwos, twos);

	sort(twos.begin(), twos.end(), compare);
	concat(twos.size() ? twos : neighbors, result);
	int countLimit = 20;
	if (result.size() > countLimit) 
	{
		result.erase(result.begin() + countLimit, result.end());
	}

	return result;

}

void AI::cache(int deep, node& score)
{
	if (!Config::cache) 
		return;
	if (score.abcut) 
		return;
	object obj;
	obj.deep = deep;
	obj.score.score = score.score;
	obj.score.step = score.step;
	obj.score.steps = score.steps;
	obj.b = toString();

	Cache[zobrist.code] = obj;
	// config.debug && console.log('add cache[' + board.zobrist.code + ']', obj)
	static int cacheCount = 0;
	cacheCount++;

}

node AI::r(int deep, int alpha, int beta, Role role, int step, vector<point>& steps, int spread)
{

	if (Config::cache) 
	{

		if (Cache.count(zobrist.code)) 
		{
			object c = Cache[zobrist.code];
			if (c.deep >= deep) 
			{
				cacheGet++;
				node ret;
				ret.score = c.score.score;
				ret.steps = c.steps;
				ret.step = c.step;///+c.score.step???
				return ret;
			}
			else 
			{
				///这里和原来不一样
				if (greatOrEqualThan(c.score.score, Score::FOUR) || littleOrEqualThan(c.score.score, -Score::FOUR)) {
					cacheGet++;
					return c.score;
				}
			}
		}
	}

	int _e = evaluate(role);

	node leaf;
	leaf.score = _e;
	leaf.step = step;
	leaf.steps = steps;

	count++;
	// 搜索到底 或者已经胜利
	// 注意这里是小于0，而不是1，因为本次直接返回结果并没有下一步棋
	if (deep <= 0 || greatOrEqualThan(_e, Score::FIVE) || littleOrEqualThan(_e, -Score::FIVE)) 
	{
		return leaf;
	}

	node best;
	best.score = MIN;
	best.step = step;
	best.steps = steps;
	///2 4
	vector<point> points = gen(role, step > 4, step > 4);

	if (!points.size()) return leaf;

	for (int i = 0; i < points.size(); i++) 
	{
		put(points[i], role);

		int _deep = deep - 1;

		int _spread = spread;

		if (_spread < Config::spreadLimit) 
		{
			// 冲四延伸
			if ((role.role == Role::com && points[i].scoreHum >= Score::FIVE) || (role.role == Role::hum && points[i].scoreCom >= Score::FIVE)) {
				// _deep = deep+1
				_deep += 2;
				_spread++;
			}
		}

		vector<point>  _steps = steps;
		_steps.push_back(points[i]);
		node v = r(_deep, -beta, -alpha, role.reverse(role.role), step + 1, _steps, _spread);
		v.score *= -1;
		remove(points[i]);


		if (v.score > best.score) 
		{
			best = v;
		}
		alpha = max(best.score, alpha);
		if (greatOrEqualThan(v.score, beta)) 
		{
			if (Config::debug) { cout << "AB Cut [" << points[i].x << ',' << points[i].y << ']' << v.score << ' >= ' << beta << endl; }
			ABcut++;
			v.score = MAX - 1;
			v.abcut = 1;
			return v;
		}
	}

	cache(deep, best);

	return best;
}

int AI::negamax(vector<point> &candidates, int deep, int alpha, int beta) 
{
	count = 0;
	ABcut = 0;
	PVcut = 0;
	for (int i = 0; i < candidates.size(); i++) {
		point p = candidates[i];
		put(p, Role::com);
		vector<point> steps;
		steps.push_back(p);
		node v = r(deep - 1, -beta, -alpha, Role::hum, 1, steps, 0);
		v.score *= -1;
		alpha = max(alpha, v.score);
		remove(p);
		candidates[i].score = v.score;
		candidates[i].steps = v.steps;
	}
	if (Config::debug) cout << "迭代完成，deep = " << deep << endl;
	return alpha;
}

bool compare2(point& a, point& b) 
{
	if (equal(a.score, b.score)) 
	{
		if (a.score >= 0) 
		{
			if (a.step != b.step) return a.step < b.step;
			else return b.score < a.score;
		}
		else 
		{
			if (a.step != b.step) return b.step < a.step;
			else return b.score < a.score;
		}
	}
	else return (b.score < a.score);
}
point AI::deeping(int deep)
{
	vector<point> candidates = gen(Role::com);
	deep = deep == -1 ? Config::searchDeep : deep;
	Cache.clear();
	///point result;
	int bestScore;
	for (int i = 2; i <= deep; i += 2) 
	{
		bestScore = negamax(candidates, i, MIN, MAX);
		if (greatOrEqualThan(bestScore, Score::FIVE)) break;// 能赢了
	}


	// 排序
	sort(candidates.begin(), candidates.end(), compare2);

	point result = candidates[0];
	if (Config::debug) 
	{
		cout << "选择节点：" << candidates[0].x << " " << candidates[0].y << ", 分数:" << result.score << ", 步数:" << result.step << endl;
		cout << "搜索节点数:" << count << ",AB剪枝次数:" << ABcut << ", PV剪枝次数:" << PVcut << endl;
	}
	return result;

}

point AI::huayue() 
{
	vector<point> s = steps;
	point ret;
	if (pointEqual(point(6, 7), s[1])) 
	{
		if (s.size() == 2) { ret.x = 6; ret.y = 8; return ret; }
	}
	if (pointEqual(s[1], point(7, 6))) 
	{
		if (s.size() == 2) { ret.x = 6; ret.y = 6; return ret; }// 6 6
	}
	if (pointEqual(s[1], point(8, 7))) 
	{
		if (s.size() == 2) { ret.x = 8; ret.y = 6; return ret; }// 8 6
	}
	if (pointEqual(s[1], point(7, 8))) 
	{
		if (s.size() == 2) { ret.x = 8; ret.y = 8; return ret; }// 8 8
	}
}

point AI::puyue() {
	vector<point> s = steps;
	point ret;
	if (pointEqual(point(6, 6), s[1])) 
	{
		if (s.size() == 2) { ret.x = 6; ret.y = 8; return ret; }
	}
	if (pointEqual(s[1], point(8, 6))) 
	{
		if (s.size() == 2) { ret.x = 6; ret.y = 6; return ret; }// 6 6
	}
	if (pointEqual(s[1], point(8, 8))) 
	{
		if (s.size() == 2) { ret.x = 8; ret.y = 6; return ret; }// 8 6
	}
	if (pointEqual(s[1], point(6, 8))) 
	{
		if (s.size() == 2) { ret.x = 8; ret.y = 8; return ret; }// 8 8
	}
}

point AI::match() {
	vector<point> s = steps;
	if (board[s[0].x][s[0].y] != 1) 
		return point(-1, -1);
	if (s.size() > 2) 
		return point(-1, -1);
	vector<point> vec1;
	vec1.push_back(point(6, 7));
	vec1.push_back(point(7, 6));
	vec1.push_back(point(8, 7));
	vec1.push_back(point(7, 8));
	if (containPoint(vec1, s[1])) 
		return huayue();
	vector<point> vec2;
	vec2.push_back(point(6, 6));
	vec2.push_back(point(8, 8));
	vec2.push_back(point(8, 6));
	vec2.push_back(point(6, 8));
	if (containPoint(vec2, s[1])) 
		return puyue();
	return point(-1, -1);
}

bool AI::isfive(const point &p, Role role)
{
	int len = 15;
	int cnt = 1;
	for (int i = p.y + 1; true; i++) 
	{
		if (i >= len) 
			break;
		int t = board[p.x][i];
		if (t != role.role)
			break;
		cnt++;
	}


	for (int i = p.y - 1; true; i--) 
	{
		if (i < 0) 
			break;
		int t = board[p.x][i];
		if (t != role.role) 
			break;
		cnt++;
	}

	if (cnt >= 5) 
		return true;

	//纵向
	cnt = 1;

	for (int i = p.x + 1; true; i++) 
	{
		if (i >= len) {
			break;
		}
		int t = board[i][p.y];
		if (t != role.role) 
			break;
		cnt++;
	}

	for (int i = p.x - 1; true; i--) 
	{
		if (i < 0) {
			break;
		}
		int t = board[i][p.y];
		if (t != role.role) 
			break;
		cnt++;
	}


	if (cnt >= 5) 
		return true;
	// \\

	cnt = 1;

	for (int i = 1; true; i++) 
	{
		int x = p.x + i, y = p.y + i;
		if (x >= len || y >= len) 
		{
			break;
		}
		int t = board[x][y];
		if (t != role.role) 
			break;

		cnt++;
	}

	for (int i = 1; true; i++) 
	{
		int x = p.x - i, y = p.y - i;
		if (x < 0 || y < 0) 
		{
			break;
		}
		int t = board[x][y];
		if (t != role.role) 
			break;
		cnt++;
	}

	if (cnt >= 5) 
		return true;

	// \/
	cnt = 1;

	for (int i = 1; true; i++) 
	{
		int x = p.x + i, y = p.y - i;
		if (x < 0 || y < 0 || x >= len || y >= len) 
		{
			break;
		}
		int t = board[x][y];
		if (t != role.role) 
			break;
		cnt++;
	}

	for (int i = 1; true; i++) 
	{
		int x = p.x - i, y = p.y + i;
		if (x < 0 || y < 0 || x >= len || y >= len) 
		{
			break;
		}
		int t = board[x][y];
		if (t != role.role) 
			break;
		cnt++;
	}

	if (cnt >= 5) 
		return true;

	return false;
}

int AI::win()
{
	
	for (int i = 0; i < 15; i++) 
	{
		for (int j = 0; j < 15; j++) 
		{
			int t = board[i][j];
			if (t != Role::empty) 
			{
				if (isfive(point(i, j), t)) 
				{ 
					return t; 
				}
			}
		}
	}
	return false;
}
