#pragma once
#include<random>
#include<ctime>
#include"Point.h"
#include"Role.h"
class Zobrist {
public:
	unsigned com[15 * 15];
	unsigned hum[15 * 15];
	unsigned code;
	Zobrist();
		/*{
			for (int i = 0; i < 15*15; i++) {
				com[i] = _rand();
				hum[i] = _rand();
			}
			code = _rand();
		}*/
	void init();
		/*{
			for (int i = 0; i < 15 * 15; i++) {
				com[i] = _rand();
				hum[i] = _rand();
			}
			code = _rand();
		}*/
		/*unsigned _rand()
		{
			std::default_random_engine engine(static_cast<unsigned int>(time(0)));
			std::uniform_int_distribution<unsigned int> randomInt(1, 1000000000);
			return randomInt(engine);
		}*/
	unsigned go(point p, Role r);
	/*{
		int index = 15 * p.x + p.y;
		code ^= (r.role == Role::com ? com[index] : hum[index]);
		return code;
	}*/
};