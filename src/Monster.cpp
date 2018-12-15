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

BrownRabbit::BrownRabbit(shptr<Tile> tile, unsigned lvl)
    : Monster{tile}
{
    level = lvl;
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraXOffset = 6;
    monsterType = "BrownRabbit";

    monsterSprite = monsterSheet.get_sprite(0, 0);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
}


Squirrel::Squirrel(shptr<Tile> tile, unsigned lvl)
    : Monster{tile} 

{
    level = lvl;
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    monsterType = "Squirrel";
    monsterSprite = monsterSheet.get_sprite(0, 0);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
  
}


Fox::Fox(shptr<Tile> tile, unsigned lvl)
    : Monster{tile} 

{
    level = lvl;
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraXOffset = 9;
    extraYOffset = 4;
    monsterType = "Fox";

    monsterSprite = monsterSheet.get_sprite(0, 0);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
}



WhiteRabbit::WhiteRabbit(shptr<Tile> tile, unsigned lvl)
    : Monster{tile} 

{
    level = lvl;
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraXOffset = 9;
    monsterType = "WhiteRabbit";

    monsterSprite = monsterSheet.get_sprite(0, 0);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
}

Hamster::Hamster(shptr<Tile> tile, unsigned lvl)
    : Monster{tile} 

{
    level = lvl;
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraXOffset = 3;
    monsterType = "Hamster";

    monsterSprite = monsterSheet.get_sprite(0, 0);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
}

GrayRacoon::GrayRacoon(shptr<Tile> tile, unsigned lvl)
    : Monster{tile} 

{
    level = lvl;
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraXOffset = 3;
    extraYOffset = 4;
    monsterType = "GrayRaccon";

    monsterSprite = monsterSheet.get_sprite(0, 0);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
}


Hedgehog::Hedgehog(shptr<Tile> tile, unsigned lvl)
    : Monster{tile} 

{
    level = lvl;
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraYOffset = 4;
    monsterType = "Hedgehog";

    monsterSprite = monsterSheet.get_sprite(0, 0);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
}

BrownRacoon::BrownRacoon(shptr<Tile> tile, unsigned lvl)
    : Monster{tile} 

{
    level = lvl;
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraXOffset = 6;
    extraYOffset = 4;
    monsterType = "BrownRaccon";

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
    sf::Vector2i position(x - radius, y - radius);
    sf::Vector2i size(2.0 * radius, 2.0 * radius);


    return sf::FloatRect{x - radius, y - radius, 2 * radius, 2 * radius};     // Verkar inte fungera
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

void Monster::helpDamage(double const& dmg, bool pureDmg)
{
    if (pureDmg)
        takePureDmg(dmg);
    else
        takeDamage(dmg);    
}

void Monster::takeDamage(double const& damage)  
{
    health -= damage/armour;
    if (health <= 0)
    {
        dead = true;
    }
}

void Monster::takePureDmg(double const& damage)  
{
    health -= damage;
    if (health <= 0)
    {
        dead = true;
    }
}
void Monster::takeSlowDmg(double const& dmg, double const& slow, double const& duration, bool pureDmg) // takes in 0-1 slow part
{
    helpDamage(dmg, pureDmg);
    speed = refSpeed*slow;
    slowClock.restart();
    slowTime = duration;
}

void Monster::takeCritDamge(double const& damage, unsigned const& critChance, bool pureDmg)
{
    for (unsigned i = 1; i>= critChance; i++)
    {
        if ((rand() % 100) > 95)
        {
            helpDamage(damage, pureDmg);
            bleeding = true;
            bleedingClock.restart();
        }
        helpDamage(damage, pureDmg);
    }
}

void Monster::takePushBackDmg(double const& damage, int const& pushBack, bool pureDmg)     // pushBack percentage to push back
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
    if ((bleedingClock.getElapsedTime()).asSeconds() > 1)
        bleeding = false;
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
