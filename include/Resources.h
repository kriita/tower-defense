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
	void setFocus(shptr<Tower> const & tower);
	void setFocus(shptr<Monster> const & monster);
	void changeMoney(int const diff);
	void changeHP(int const diff);
	void changeCurrentWave(int const diff);
	void setHP(int HP) {hitpoints = HP;};
	void setMoney(int cash) {money = cash;};
	void setWave(int waveNr) {currentWave = waveNr;};

protected:
	int hitpoints{30};
	int money{100};
	int currentWave{0};
};