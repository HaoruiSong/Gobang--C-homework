#include"Zobrist.h"

Zobrist::Zobrist()
{
	std::default_random_engine engine(static_cast<unsigned int>(time(0)));
	std::uniform_int_distribution<unsigned int> randomInt(1, 1000000000);
	for (int i = 0; i < 15 * 15; i++) 
	{
		com[i] = randomInt(engine);
		hum[i] = randomInt(engine);
	}
	code = randomInt(engine);
}

void Zobrist::init()
{
	std::default_random_engine engine(static_cast<unsigned int>(time(0)));
	std::uniform_int_distribution<unsigned int> randomInt(1, 1000000000);
	for (int i = 0; i < 15 * 15; i++) 
	{
		com[i] = randomInt(engine);
		hum[i] = randomInt(engine);
	}
	
	code=randomInt(engine);
	
}



unsigned Zobrist::go(point p, Role r)
{
	int index = 15 * p.x + p.y;
	code ^= (r.role == Role::com ? com[index] : hum[index]);
	return code;
}