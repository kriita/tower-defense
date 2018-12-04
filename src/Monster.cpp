#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <string>
#include "Monster.h"
#include "constants.h"
#include "Spritesheet.h"
#include "defs.h"
#include <math.h>
#include <stdlib.h>
#include "Resources.h"
#include <random>           // Lägga till critChance?
#include <SFML/Graphics/Export.hpp>

using std::string;
using namespace std::complex_literals;
using sf::Color;
using std::vector;
using std::complex;


/* 
 *  Monster
 */

Monster::Monster(shptr<Tile> tile, int level)
    : x{tile->getX()}, y{tile->getY()}
{
    nextTile = tile;
}

Monster::Monster(double xPos, double yPos)
    :   x{xPos}, y{yPos} {}

Monster::Monster(int x, int y)
    :   Monster {mapBorderOffset + tileWidth / 2 + tileWidth * x, 
               mapBorderOffset + tileWidth / 2 + tileWidth * y} {}




Orc::Orc(shptr<Tile> tile, int level)
    : Monster{tile, level}
{
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    monsterSprite = monsterSheet.get_sprite(0, 0);
//    monsterTexture.loadFromFile("resources/images/monster.png");
//    monsterSprite.setTexture(monsterTexture);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
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
/*
Complexus::Complexus(shptr<Tile> tile)
    : Monster{tile}
{
    health = 50;
    armour = 3;
    speed = 2;
    refSpeed = 2;
    bounty = 20;
}

Complexus::Complexus(double x, double y)
    : Monster{x,y} 
{} 

Complexus::Complexus(int x, int y)
    : Complexus {mapBorderOffset + tileWidth / 2 + tileWidth * x, 
              mapBorderOffset + tileWidth / 2 + tileWidth * y} {}

*/

void Orc::setSprite(sf::Sprite sprite)
{
    monsterSprite = sprite;
    monsterSprite.setPosition(x, y);
}




void Monster::render(sf::RenderTarget &target)
{ 
    target.draw(monsterSprite);
}

void Orc::update()
{
    walk();
    setSprite(monsterSprite);
}



sf::FloatRect Monster::getBounds()
{
    return monsterSprite.getGlobalBounds();     // Verkar inte fungera
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
    if (real(health) <= 0 &&
        imag(health) <= 0)
    {
        defeat();
        dead = true;    
    }
}

void Monster::takePureDmg(double damage)  
{
    health -= damage;
    if (real(health) <= 0 &&
        imag(health) <=0)
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
