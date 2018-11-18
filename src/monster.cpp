#include <SFML/Graphics.hpp>
#include "tile.h"
#include <string>
#include "monster.h"
using std::string;

/* 
 *  Monster
 */

int Monster1::getX() const
{
    return xPosTile;
}

int Monster1::getY() const
{
    return yPosTile;
}

double Monster1::getFineX() const
{
    return xPosTile;
}

double Monster1::getFineY() const
{
    return yPosTile;
}

string Monster1::getType() const
{
    return monsterType;
}

void Monster1::takeDamage()
{
    health =- 1;               // lägg in skada funktionern för tornet
}


