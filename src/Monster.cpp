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
    monsterSprite = monsterSheet.get_sprite(0, 0);
    monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
    frozenSprite = frozenSheet.get_sprite(0, 0);
    frozenSprite.setOrigin(tileWidth/2, tileWidth/2);
}

BrownRabbit::BrownRabbit(shptr<Tile> tile, unsigned lvl)
    : Monster{tile}
{
    healths = {55, 100, 250, 500, 750, 1000, 1500, 2000, 3000, 5000};
    armours = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
    speeds = {1, 1, 1.5, 1.5, 2, 2, 2, 2, 2, 2};
    bountys = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};    
    level = lvl;
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraXOffset = 6;
    monsterType = "BrownRabbit";
}

Squirrel::Squirrel(shptr<Tile> tile, unsigned lvl)
    : Monster{tile} 

{
    healths = {50, 50, 75, 100, 200, 250, 400, 500, 750, 1000};
    armours = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 6};
    speeds = {1.3, 1.5, 2, 2, 2, 2.5, 2.5, 2.5, 2.5, 3};
    bountys = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};    
    level = lvl;
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    monsterType = "Squirrel";
}

Fox::Fox(shptr<Tile> tile, unsigned lvl)
    : Monster{tile} 

{
    healths = {75, 150, 200, 250, 300, 400, 800, 2000, 3000, 5000};
    armours = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 6};
    speeds  = {1, 1, 1.5, 1.5, 2, 2, 2, 2, 2, 2};
    bountys = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    level = lvl;
    health = healths[level];
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraXOffset = 9;
    extraYOffset = 4;
    monsterType = "Fox";
}

WhiteRabbit::WhiteRabbit(shptr<Tile> tile, unsigned lvl)
    : Monster{tile}

{
    healths = {1, 1000, 3000, 5000, 10000, 25000, 50000, 100000, 500000, 1000000};
    armours = {20, 50, 100, 250, 500, 750, 1000, 2000, 3000, 5000};
    speeds = {1, 1, 1, 1, 1, 0.5, 0.5, 0.5, 0.5, 0.5};
    bountys = {70, 100, 100, 100, 100, 100, 100, 100, 100, 100};
    double regeneration [10] {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}; 
    level = lvl;
    health = healths[level] + regeneration[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraXOffset = 9;
    monsterType = "WhiteRabbit";
    HPLoss = 5;
}

void WhiteRabbit::regenerate()
{
    if ((bleedingClock.getElapsedTime()).asSeconds() >= 1)
    {
        health += regeneration [level];
        bleedingClock.restart();
    }
}

Hamster::Hamster(shptr<Tile> tile, unsigned lvl)
    : Monster{tile} 

{
    healths = {25, 250, 350, 400, 500, 1000, 1500, 2000, 3000, 5000};
    armours = {2, 2, 2, 2.5, 3, 3.5, 4, 4.5, 5, 6};
    speeds  = {1.3, 1.3, 1.53, 1.53, 2.3, 2.3, 2.3, 2.3, 2.3, 2.3};
    bountys = {1, 25, 25, 25, 25, 25, 25, 25, 25, 25};
    level = lvl;
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraXOffset = 3;
    monsterType = "Hamster";
}

GrayRacoon::GrayRacoon(shptr<Tile> tile, unsigned lvl)
    : Monster{tile} 

{
    healths = {50, 100, 250, 500, 750, 1000, 1500, 2000, 3000, 5000};
    armours = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 6};
    speeds = {1, 1, 1.5, 1.5, 2, 2, 2, 2, 2, 2};
    bountys = {1, 50, 100, 250, 500, 750, 1000, 2000, 3000, 5000};
    level = lvl;
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraXOffset = 3;
    extraYOffset = 4;
    monsterType = "GrayRaccon";
}

Hedgehog::Hedgehog(shptr<Tile> tile, unsigned lvl)
    : Monster{tile} 

{
    healths = {50, 100, 250, 500, 750, 1000, 1500, 2000, 3000, 5000};
    armours = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 6};
    speeds  = {1, 1, 1.5, 1.5, 2, 2, 2, 2, 2, 2};
    bountys = {0, 20, 20, 20, 20, 20, 20, 20, 20, 20};
    level = lvl;
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraYOffset = 4;
    monsterType = "Hedgehog";
}

BrownRacoon::BrownRacoon(shptr<Tile> tile, unsigned lvl)
    : Monster{tile} 

{
    healths = {50, 100, 250, 500, 750, 1000, 1500, 2000, 3000, 5000};
    armours = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 6};
    speeds  = {1, 1, 1.5, 1.5, 2, 2, 2, 2, 2, 2};
    bountys = {1, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    level = lvl;
    health = healths[level];
    armour = armours[level];
    speed = speeds[level];
    refSpeed = speeds[level];
    bounty = bountys[level];
    extraXOffset = 6;
    extraYOffset = 4;
    monsterType = "BrownRaccon";
    HPLoss = 2;
}

void Monster::setLevel(unsigned const& lvl)
{
    level = lvl;
    health = healths[lvl];
    armour = armours[lvl];
    speed = speeds[lvl];
    refSpeed = speeds[lvl];
    bounty = bountys[lvl];
}

void Monster::setSprite()
{
    if (speed < refSpeed && speed != 0)
    {
        frozenSprite.setPosition(x, y);
        frozenSprite.setOrigin(tileWidth/2, tileWidth/2);
    }
    else 
    {
        monsterSprite.setPosition(x, y);
        monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
    }
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
    if (speed != 0)
    { 
        if (animClock.getElapsedTime().asMilliseconds() > 300/speed)
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
}

void Monster::render(sf::RenderTarget &target)
{ 
    if (speed < refSpeed && speed != 0)
        target.draw(frozenSprite);
    else 
        target.draw(monsterSprite);
}

void Monster::update()
{
    walk();
    setSprite();
    monsterSprite = monsterSheet.get_sprite(yOffset + extraYOffset,
                                            xOffset + extraXOffset);
    frozenSprite = frozenSheet.get_sprite(yOffset + extraYOffset,
                                            xOffset + extraXOffset);
    if (speed < refSpeed && speed != 0)
    {
        frozenSprite.setPosition(x, y);
        frozenSprite.setOrigin(tileWidth/2, tileWidth/2);
    }
    else
    {
        monsterSprite.setPosition(x, y);
        monsterSprite.setOrigin(tileWidth/2, tileWidth/2);
    }
}

sf::FloatRect Monster::getBounds()
{
    return monsterSprite.getGlobalBounds();
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
void Monster::takeSlowDmg(double const& dmg, double const& slowing, 
                          double const& duration, bool pureDmg) // takes in 0-1 slow part
{
    helpDamage(dmg, pureDmg);
    speed = refSpeed*slow;
    slowClock.restart();
    slowTime = duration;
    slow = slowing;
    slowed = true;
}

void Monster::takeCritDamage(double const& damage, 
                unsigned const& critChance, bool pureDmg)
{
    for (unsigned i = 1; i<= critChance; i++)
    {
        if ((rand() % 100) > 95)
        {
            helpDamage(damage, pureDmg);
            bleeding = true;
            bleedingClock.restart();
        }
    }
    helpDamage(damage, pureDmg);
}

void Monster::takeStunDmg(double const& damage, int const& duration, 
                          double const& percentage, bool pureDmg)    
{
    helpDamage(damage, pureDmg);
    if ((rand() % 100) > percentage)
    {
        speed = 0;
        stunClock.restart();
        stunDuration = duration;
        stunned = true;
    }
}

void Monster::walk()
{
    double tolerance{10*speed};
    if (   (pow((nextTile->getX() - x), 2) <= tolerance)
        && (pow((nextTile->getY() - y), 2) <= tolerance))
    {
        x = nextTile->getX();
        y = nextTile->getY();
        setNextTile();
        setDir();
    }

    if ((bleedingClock.getElapsedTime()).asSeconds() > 3)
        bleeding = false;
    
    if ((stunClock.getElapsedTime()).asSeconds() > stunDuration)
        stunned = false;

    if ((slowClock.getElapsedTime()).asSeconds() > slowTime)
        slowed = false;

    if (!slowed && !stunned)
        speed = refSpeed;
    
    if (slowed && !stunned)
        speed = slow;
    
    x += speed * xDir;
    y += speed * yDir;
}

void WhiteRabbit::walk()
{
    Monster::walk();
    regenerate();
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
