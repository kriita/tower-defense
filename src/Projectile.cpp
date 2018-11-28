#include "Projectile.h"
#include "defs.h"
#include "Map.h"
#include "Monster.h"
#include <cmath>

/*
 *  Funktioner kvar att definiera:
 *  virtual void monsterHit()
    virtual void explodeAnim() // renders the explode animation
    void isOutsideMap()
 */


Projectile::Projectile(double x, double y, double xDir, double yDir)
: x {x}, y {y}, xDir {xDir}, yDir {yDir} {}


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
    //double tmpAngle = angle;
    //while (tmpAngle % (2*acos(-1)) > 0)
    //{
    //tmpAngle -= tmpAngle/(2*acos(-1));
    //}
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
        else return yDir/abs(yDir);
    }
    else if (yDir/xDir > 0)
    {
        return atan(yDir/xDir);
    }
    else return atan(yDir/xDir);
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

void Projectile::update()
{
    move();
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


Anvil::Anvil()
: Projectile {}
{
    projectileTexture.loadFromFile("resources/images/anvil_t.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setOrigin(512, 512);
    projectileSprite.setScale(0.05, 0.05);
}


Anvil::Anvil(double x, double y, double xDir, double yDir)
: Projectile {x, y, xDir, yDir}
{
    projectileTexture.loadFromFile("resources/images/anvil_t.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setOrigin(512, 512);
    projectileSprite.setScale(0.04, 0.04);
    projectileSprite.setPosition(x,y);
}

Anvil::Anvil(double x, double y, double xDir, double yDir, shptr<Monster> &target)
: Projectile {x, y, xDir, yDir}
{
    projectileTexture.loadFromFile("resources/images/anvil_t.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setOrigin(512, 512);
    projectileSprite.setScale(0.04, 0.04);
    projectileSprite.setPosition(x,y);
    setTarget(target);
}