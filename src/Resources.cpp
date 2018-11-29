#pragma once

/*
 * resources.cpp
 * 
 * The purpose of this file is to define the behavior of game resources.
 * A resource class is created with initial hitpoints and money values, that
 * can later be retrieved and changed with public functions.
 * Example: if a monster makes it through the path, changeHP(-1) will be used.
 * Functions: getMoney, getHP, changeMoney, changeHP
 */

#include "Resources.h"

resources::resources(int initHitpoints, int initMoney)
: hitpoints {initHitpoints}, money {initMoney} {}

int resources::getMoney()
{
	return money;
}

int resources::getHP()
{
	return HP;
}

void resources::changeMoney(int const diff)
{
	money = money + diff;
}

void resources::changeHP(int const diff)
{
	hitpoints = hitpoints + diff;
}