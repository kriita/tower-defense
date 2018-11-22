#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <string>
#include "Monster.h"
using std::string;

/* 
 *  Monster
 */

void Monster::despawn()
{
    
}

double Monster1::getX() const
{
    return x;
}

double Monster1::getY() const
{
    return y;
}

string Monster1::getType() const
{
    return monsterType;
}

void Monster1::takeDamage()
{
    health =- 1;               // lägg in skada funktionern för tornet
}

void Monster1::walk()
{

}

void Monster1::defeat()
{

}