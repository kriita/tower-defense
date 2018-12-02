#include "Projectile.h"
#include "defs.h"
#include "Map.h"
#include "Monster.h"
#include <cmath>
#include <vector>
#include "complex"

#include <iostream>
/*
 *  Funktioner kvar att definiera:
    virtual void explodeAnim() // renders the explode animation
    void isOutsideMap() // Behövs inte om cleanup körs i Gamestate? 
 */


Projectile::Projectile(double x, double y, double xDir, double yDir)
: x {x}, y {y}, xDir {xDir}, yDir {yDir} {}

Projectile::Projectile(double x, double y, double dirByRadians)
: x {x}, y {y}, xDir {cos(dirByRadians)}, yDir {sin(dirByRadians)} {}

void Projectile::setx(double new_x)
{
    x = new_x;
}

void Projectile::sety(double new_y)
{
    y = new_y;
}

double Projectile::getX() // Coordinates in pixels
{
    return x;
}

double Projectile::getY()
{
    return y;
}

void Projectile::setxDir(double new_xDir)
{
    xDir = new_xDir;
}

void Projectile::setyDir(double new_yDir)
{
    yDir = new_yDir;
}

void Projectile::setDirByRadians(double angle)
{
    xDir = cos(angle);
    yDir = sin(angle);
}

double Projectile::getxDir()
{
    return xDir;
}

double Projectile::getyDir()
{
    return yDir;
}

double Projectile::getDirByRadians()
{
    if (xDir == 0)
    {
        if (yDir == 0)
        {
            throw ProjectileError("xDir = yDir = 0 does not provide a direction angle");
        }
        else return asin(yDir);
    }
    else return atan2(yDir, xDir);
}

double Projectile::getSpeed()
{
    return speed;
}

void Projectile::setSpeed(double newSpeed)
{
    speed = newSpeed;
}

// Returns nullptr (false) if Projectile has no target
shptr<Monster> Projectile::getTarget() 
{
   return target;

}

void Projectile::setTarget(shptr<Monster> newTarget)
{
    target = newTarget;
}

void Projectile::move()
{
    if (getTarget())    // Update coords. if Projectile has target
    {
        xDir = (x*x - (target->getX() * target->getX()))/
        abs(x*x + (target->getX() * target->getX()));
        yDir = (y*y - (target->getY() * target->getY()))/
        abs(y*y + (target->getY() * target->getY()));
    }
    x += xDir * speed;
    y += yDir * speed;
    projectileSprite.setPosition(x, y);
}

void Projectile::update(std::vector<shptr<Monster>> &allMonsters)
{
    move();
    targetHit();
    for (shptr<Monster> aMonster : allMonsters)
    {
        if (checkHit(aMonster))
        {
            dealDamage(aMonster);
        }
    }
}

void Projectile::dealDamage(shptr<Monster> &aMonster)
{
    aMonster->takeDamage(damage);
}

void Projectile::render(sf::RenderTarget &window)
{
    window.draw(projectileSprite);
}


void Projectile::targetHit()
{
    if (getTarget())
    {
        target->takeDamage(damage);
    }
}

sf::FloatRect Projectile::getBounds()
{
    return projectileSprite.getGlobalBounds();
}

bool Projectile::checkHit(shptr<Monster> &aMonster)
{
    if (abs(aMonster->getX() + aMonster->getY() - (x + y)) -
        (aMonster->getBounds().width/2 + getBounds().width)/2 < 0)
    {
        return true;
    }
    else return false;
}




Anvil::Anvil()
: Projectile {}
{
    projectileTexture.loadFromFile("resources/images/anvil_t.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setOrigin(16, 16);
    setSpeed(3);
    damage = 100;
}


Anvil::Anvil(double x, double y, double xDir, double yDir)
: Projectile {x, y, xDir, yDir}
{
    projectileTexture.loadFromFile("resources/images/anvil_t.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setOrigin(16, 16);
    projectileSprite.setPosition(x,y);
    speed = 10;
    damage = 100;
}

Anvil::Anvil(double x, double y, double xDir, double yDir, shptr<Monster> &target)
: Anvil {x, y, xDir, yDir}
{
    projectileTexture.loadFromFile("resources/images/anvil_t.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setOrigin(16, 16);
    projectileSprite.setPosition(x,y);
    setTarget(target);
}

minigunProjectile::minigunProjectile(double x, double y, double xDir, double yDir)
: Projectile(x, y, xDir, yDir)
{
    projectileTexture.loadFromFile("resources/images/minigunProjectile.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setOrigin(16, 16);
    projectileSprite.setPosition(x,y);
    speed = 5;
    damage = 1;
}

minigunProjectile::minigunProjectile(double x, double y, double dirByRadians)
: Projectile(x, y, dirByRadians)
{
    projectileTexture.loadFromFile("resources/images/minigunProjectile.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setOrigin(16, 16);
    projectileSprite.setPosition(x,y);
    speed = 5;
    damage = 1;
}