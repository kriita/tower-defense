/*
 * Resources.cpp
 * 
 * The purpose of this file is to define the behavior of game resources.
 * A resource class is created with initial hitpoints and money values, that
 * can later be retrieved and changed with public functions.
 * Example: if a monster makes it through the path, changeHP(-1) will be used.
 * Functions: getMoney, getHP, changeMoney, changeHP
 */

#include "Monster.h"
#include "Resources.h"
#include "Tower.h"

Resources::Resources(int initHitpoints, int initMoney)
: hitpoints {initHitpoints}, money {initMoney} {}

int Resources::getMoney()
{
	return money;
}

int Resources::getHP()
{
	return hitpoints;
}

int Resources::getCurrentWave()
{
	return currentWave;
}

void Resources::setFocus(shptr<Tower> const & tower)
{

}

void Resources::setFocus(shptr<Monster> const & monster)
{

}

void Resources::changeMoney(int const diff)
{
	money = money + diff;
}

void Resources::changeHP(int const diff)
{
	hitpoints = hitpoints + diff;
}

void Resources::changeCurrentWave(int const diff)
{
	currentWave = currentWave + diff;
}

void Resources::switchBuildMode()
{
	buildMode = !buildMode;
}