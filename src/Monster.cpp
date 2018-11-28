#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <string>
#include "Monster.h"
#include "constants.h"
#include "defs.h"
using std::string;

/* 
 *  Monster
 */

void Monster::despawn()
{
    
}

double Monster::getX() const
{
    return x;
}

double Monster::getY() const
{
    return y;
}

string Monster1::getType() const
{
    return monsterType;
}

void Monster1::takeDamage(double damage)
{
    Monster::health =- damage;               // lägg in skada funktionern för tornet
    if (health <= 0)
    {
        if (nextTile = nextTile->getNextTile())
        {
            Monster::loseLife();
            Monster::despawn();
        }
        else
        {
            Monster::defeat();
            Monster::despawn();    
        }
    }
}

void Monster::walk()
{

}

void Monster::loseLife()
{
    // Ändrar life i GameState till nuvarande minus 1 (standard)
}

void Monster1::loseLife()
{
    // Ändrar life i GameState till nuvarande minus lifeLoss
}

void Monster1::defeat()
{
    // Ändrar pengar i economy till nuvarande + bounty
}

void Monster::setNextTile()
{
    nextTile = nextTile->getNextTile();
}


