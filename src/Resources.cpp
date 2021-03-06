/*
 * Resources.cpp
 * 
 * The purpose of this file is to define the behavior of game resources.
 * A resource class is created with initial hitpoints and money values, that
 * can later be retrieved and changed with public functions.
 * Example: if a monster makes it through the path, changeHP(-1) can be used.
 */

#include "Monster.h"
#include "Resources.h"
#include "Tower.h"
#include <iostream>

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

bool Resources::getBuildMode()
{
	return buildMode;
}

shptr<Tower> Resources::getFocusTower()
{
	return focusTower;
}

// The focused tower is the tower who's information
// is displayed in the focus window
void Resources::setFocus(shptr<Tower> const & tower)
{
	focusTower = tower;
	focusMonster = nullptr;
}

// Focus monster was never used, but was intended to work like focusTower and
// display a monsters current hitpoints
void Resources::setFocus(shptr<Monster> const & monster)
{
	focusMonster = monster;
	focusTower = nullptr;
}

void Resources::deselect()
{
	focusMonster = nullptr;
	focusTower = nullptr;
	buildMode = false;
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
	currentWave = diff;
}

void Resources::switchBuildMode()
{
	buildMode = !buildMode;
}
