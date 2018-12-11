#pragma once

/*
 * Resources.h
 * 
 * Header file for Resources.cpp.
 */

#include "Monster.h"
#include "Tower.h"
#include <stdexcept>

class ResourcesError : public std::logic_error
{
	using std::logic_error::logic_error;
};

class Resources
{
public:
	Resources(int initHitpoints, int initMoney);
	~Resources() = default;

	int getMoney();
	int getHP();
	int getCurrentWave();
	void setFocus(Tower const & tower1);
	void setFocus(Monster const & monster1);
	void changeMoney(int const diff);
	void changeHP(int const diff);
	void changeCurrentWave(int const diff);

protected:
	int hitpoints{30};
	int money{100};
	int currentWave{0};
};