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

/*
void Monster::setMonsterSprite(sf::Sprite sprite)
{
    tileSprite = sprite;
    tileSprite.setPosition (mapBorderOffset + tileWidth / 2 + tileWidth * xTile,
                            mapBorderOffset + tileWidth / 2 + tileWidth * yTile);
    tileSprite.setOrigin (tileWidth/2, tileWidth/2);
}
*/
Orc::Orc(shptr<Tile> tile)
    : Monster{tile}
{
    health = 50;
    armour = 3;
    speed = 2;
    refSpeed = 2;
    bounty = 20;
}

Orc::Orc(double x, double y)
    : Monster{x,y} 
{} 

Orc::Orc(int x, int y)
    : Orc {mapBorderOffset + tileWidth / 2 + tileWidth * x, 
              mapBorderOffset + tileWidth / 2 + tileWidth * y} {}



/*
Flash::Flash(shptr<Tile> tile)
    : Monster{tile}
{
    health = 5000;
    armour = 3;
    speed = 1;
    refSpeed = 10;
    bounty = 20;
}

Flash::Flash(double x, double y)
    : Monster{x,y} 
{} 

Flash::Flash(int x, int y)
    : Flash {mapBorderOffset + tileWidth / 2 + tileWidth * x, 
              mapBorderOffset + tileWidth / 2 + tileWidth * y} {}
*/

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

void Monster::setDir()
{
    xDir = nextTile->getX() - x;
    if (!(xDir == 0))
        xDir /= abs(xDir);
    
    yDir = nextTile->getY() - y;
    if (!(yDir == 0))
        yDir /= abs(yDir);
}


void Monster::takeDamage(double damage)  
{
    health -= damage/armour;
    if (health <= 0)
    {
        defeat();
        dead = true;    
    }
}

void Monster::takePureDmg(double damage)  
{
    health -= damage;
    if (health <= 0)
    {
        defeat();
        dead = true;    
    }
}

void Monster::takeSlowDmg(double dmg, double slow, double duration, bool pureDmg) // takes in 0-1 slow part
{
    if (pureDmg)
        takePureDmg(dmg);
    else
        takeDamage(dmg);
    speed = refSpeed*slow;
    slowClock = duration;        // set slow duration in renderings.
}

void Monster::walk()
{
    double tolerance{10*speed};
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
    if (slowClock == 0)
        speed = refSpeed;
    else 
        slowClock -= 1;
}

void Orc::loseHP()
{
//    resources::changeHP(int const& -HPLoss);
}


void Orc::defeat()
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
