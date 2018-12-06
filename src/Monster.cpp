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
    radius = 8;
}

Orc::Orc(shptr<Tile> tile, unsigned level)
    : Monster{tile}
{
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraXOffset = 6;

    monsterSprite = monsterSheet.get_sprite(0, 0);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
}


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


Tank::Tank(shptr<Tile> tile, unsigned level)
    : Monster{tile} 

{
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraXOffset = 9;
    extraYOffset = 4;
    monsterSprite = monsterSheet.get_sprite(0, 0);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
}

Derp::Derp(shptr<Tile> tile, unsigned level)
    : Monster{tile} 

{
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraXOffset = 3;
    extraYOffset = 4;
    monsterSprite = monsterSheet.get_sprite(0, 0);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
}

void Monster::setSprite()
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

void Monster::update()
{
    walk();
    setSprite();
    monsterSprite = monsterSheet.get_sprite(yOffset + extraYOffset,
                                            xOffset + extraXOffset);
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

void Monster::helpDamage(double dmg, bool pureDmg)
{
    if (pureDmg)
        takePureDmg(dmg);
    else
        takeDamage(dmg);    
}

void Monster::takeDamage(double damage)  
{
    health -= damage/armour;
    if (health <= 0)
    {
        dead = true;
        giveBounty = true;
    }
}

void Monster::takePureDmg(double damage)  
{
    health -= damage;
    if (health <= 0)
    {
        dead = true;
        giveBounty = true;    
    }
}
void Monster::takeSlowDmg(double dmg, double slow, double duration, bool pureDmg) // takes in 0-1 slow part
{
    helpDamage(dmg, pureDmg);
    speed = refSpeed*slow;
    slowClock.restart();
    slowTime = duration;
}

void Monster::takeCritDamge(double damage, unsigned critChance, bool pureDmg)
{
    for (unsigned i = 1; i>= critChance; i++)
    {
        if ((rand() % 100) > 95)
        {
            helpDamage(damage, pureDmg);
        }
        helpDamage(damage, pureDmg);
    }
}

void Monster::takePushBackDmg(double damage, int pushBack, bool pureDmg)     // pushBack percentage to push back
{
    helpDamage(damage, pureDmg);
    if ((rand() % 100) > (100 - pushBack))
    {
        nextTile = prevTile;
        x = nextTile->getX();
        y = nextTile->getY();
        walk();
    }
}

void Monster::walk()
{
    double tolerance{10*speed};
    if (   (pow((nextTile->getX() - x), 2) <= tolerance)
        && (pow((nextTile->getY() - y), 2) <= tolerance))
    {
        prevTile = nextTile;
        x = nextTile->getX();
        y = nextTile->getY();
        Monster::setNextTile();
        Monster::setDir();
    }
    if ((slowClock.getElapsedTime()).asSeconds() > slowTime)
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
        loseHP = true;
    }
}
