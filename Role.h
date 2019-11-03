#pragma once
#ifndef ROLE_H
#define ROLE_H
class Role{
public:
	const int static com = 1;
	const int static hum = 2;
	const int static empty = 0;
	int role;
	int reverse(int role_) 
	{
		return role_ == 1 ? 2 : 1;
	}
	Role(int r=empty):role(r)
	{
		
	}
};

#endif // !ROLE_H
