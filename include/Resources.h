#pragma once

/*
 * Resources.h
 * 
 * Header file for Resources.cpp.
 */

class resources
{
public:
	resources(int initHitpoints, int initMoney);
	~resources() = default;

	int getMoney();
	int getHP();
	void changeMoney(int const diff);
	void changeHP(int const diff);

protected:
	int hitpoints;
	int money;
};