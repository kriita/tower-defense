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
using std::vector;
using sf::Clock;


/* 
 *  Monster
 */



Monster::Monster(shptr<Tile> tile)
{
    nextTile = tile;
    x = tile->getX();
    y = tile->getY();
}

Orc::Orc(shptr<Tile> tile, unsigned level)
    : Monster{tile}
{
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    monsterSprite = monsterSheet.get_sprite(0, 0);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
}

/*
Flash::Flash(shptr<Tile> tile, unsigned level)
    : Monster{tile} 

{
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    monsterSprite = monsterSheet.get_sprite(0, 0);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
}
*/
void Orc::setSprite()
{
    monsterSprite.setPosition(x, y);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
    if (xDir == 0)
    {
        if (yDir == 1)
            yOffset = 0;
        else
            yOffset = 3;
    }
    else 
    {
        if (xDir == 1)
            yOffset = 2;
        else 
            yOffset = 1;
    }
    if (animClock.getElapsedTime().asMilliseconds() > 100)
    {
        if (xOffset == 0 || xOffset == 2)
            xOffset = 1;
        else
            if (firstStep)
                xOffset = 0;
            else
                xOffset = 2;
        animClock.restart();
    }
}




void Monster::render(sf::RenderTarget &target)
{ 
    target.draw(monsterSprite);
}

void Orc::update()
{
    walk();
    setSprite();
    monsterSprite = monsterSheet.get_sprite(yOffset, xOffset);
    monsterSprite.setPosition(x, y);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
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
    if (health <= 0)
    {
        dead = true;
        getBounty = true;    
    }
}

void Monster::takePureDmg(double damage)  
{
    health -= damage;
    if (health <= 0)
    {
        dead = true;
        getBounty = true;    
    }
}

void Monster::takeSlowDmg(double dmg, double slow, double duration, bool pureDmg) // takes in 0-1 slow part
{
    if (pureDmg)
        takePureDmg(dmg);
    else
        takeDamage(dmg);
    speed = refSpeed*slow;
    slowClock.restart();
    slowTime = duration;
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
    if ((animClock.getElapsedTime()).asSeconds() > slowTime)
        speed = refSpeed;
    x += speed*xDir;
    y += speed*yDir;
}

void Monster::setNextTile()
{
    if (nextTile->getNextTile() != nullptr)
        nextTile = nextTile->getNextTile();
    else
    {
        dead = true;
//        loseHP = true;
    }
}
