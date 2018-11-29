#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <string>
#include "Monster.h"
#include "constants.h"
#include "defs.h"
#include <math.h>
#include <stdlib.h>
#include "Resources.h"

using std::string;

/* 
 *  Monster
 */

Monster::Monster(shptr<Tile> tile)
    : x{tile->getX()}, y{tile->getY()}
{
    nextTile = tile;
}

Monster::Monster(double xPos, double yPos)
    :   x{xPos}, y{yPos} {}

Monster::Monster(int x, int y)
    :   Monster {mapBorderOffset + tileWidth / 2 + tileWidth * x, 
               mapBorderOffset + tileWidth / 2 + tileWidth * y} {}

Monster1::Monster1(shptr<Tile> tile)
    : Monster{tile}
{
}

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



void Monster::setDir()
{
    xDir = nextTile->getX() - x;
    if (!(xDir == 0))
        xDir /= abs(xDir);
    
    yDir = nextTile->getY() - y;
    if (!(yDir == 0))
        yDir /= abs(yDir);
}

string Monster1::getType() const
{
    return monsterType;
}

void Monster::takeDamage(double damage)           // Returns if it's dead
{
    health -= damage;               // lägg in skada funktionern för tornet
    if (health <= 0)
    {
        defeat();
        dead = true;    
    }
}


double Monster::getHealth()
{
    return health;
}

void Monster::walk()
{
    double tolerance{speed};
    if (   (pow((nextTile->getX() - x), 2) <= tolerance)
        && (pow((nextTile->getY() - y), 2) <= tolerance))
    {
        x = nextTile->getX();
        y = nextTile->getY();
        Monster::setNextTile();
        Monster::setDir();
    }
    x += speed*xDir;
    y += speed*yDir;
}

void Monster::loseHP()
{
//   resources::changeHP(int const& -1);
}

void Monster1::loseHP()
{
//    resources::changeHP(int const& -HPLoss);
}


void Monster1::defeat()
{
//    resources::changeMoney(int const bounty);
}

void Monster::setNextTile()
{
    if (nextTile->getNextTile() != nullptr)
        nextTile = nextTile->getNextTile();
    else
    {
        dead = true;
        loseHP();
    }
}


