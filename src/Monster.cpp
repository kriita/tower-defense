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

Monster::Monster(double xPos, double yPos)
    :   x{xPos}, y{yPos} {}

Monster::Monster(int x, int y)
    :   Monster {mapBorderOffset + tileWidth / 2 + tileWidth * x, 
               mapBorderOffset + tileWidth / 2 + tileWidth * y} {}


Monster1::Monster1(double x, double y)
    : Monster{x,y} 
{} 

Monster1::Monster1(int x, int y)
    : Monster1 {mapBorderOffset + tileWidth / 2 + tileWidth * x, 
              mapBorderOffset + tileWidth / 2 + tileWidth * y} {}

void Monster::render(sf::RenderTarget &target)
{ 
    float const r{10.0};
    sf::CircleShape circle { r };
    circle.setPosition (x,y);
    circle.setOrigin (r, r);
    circle.setFillColor (sf::Color::Green);
    target.draw(circle);
}


void Monster::update()
{
    walk();
}

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

void Monster::setXDir()
{

}

void Monster::setYDir()
{

}

string Monster1::getType() const
{
    return monsterType;
}

void Monster1::takeDamage(double damage)
{
    Monster::health =- damage*armour;               // lägg in skada funktionern för tornet
    if (health <= 0)
    {
        Monster::defeat();
        Monster::despawn();    
    }
}

void Monster::walk()
{

}

void Monster::loseLife()
{
    // Ändrar life i Economy/resourses till nuvarande minus 1 (standard)
}

void Monster1::loseLife()
{
    // Ändrar life i Economy/resourses till nuvarande minus lifeLoss
}

void Monster::defeat()
{
    // Ändrar pengar i economy till nuvarande + bounty
}

void Monster::setNextTile()
{
    nextTile = nextTile->getNextTile();
}


