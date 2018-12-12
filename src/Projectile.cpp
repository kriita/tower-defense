#include "Projectile.h"
#include "defs.h"
#include "Monster.h"
#include <cmath>
#include <vector>
#include "constants.h"

#include <iostream>
/*
 *  Funktioner kvar att definiera:
    virtual void explodeAnim() // renders the explode animation
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
    if (getTarget() != nullptr)    // Update coords. if Projectile has target
    {
/*
        double PMx = -(x*x - (target->getX() * target->getX()));
        double PMy = -(y*y - (target->getY() * target->getY()));

        xDir = PMx/abs(PMx);
        yDir = PMy/abs(PMy);
        
        double PMx = -(x*x - (target->getX() * target->getX()));

        
        double PMy = -(y*y - (target->getY() * target->getY()));
        
        xDir = PMx/abs(PMx);
        yDir = PMx/abs(PMy);
        x += xDir * speed / abs(PMx);
        y += yDir * speed / abs(PMy);
        */
        projectileSprite.setRotation(getDirByRadians() * 360 / (2 * 3.1415));
        setAngle();
    }
    x += xDir * speed;
    y += yDir * speed;
    projectileSprite.setPosition(x, y);
    
}

void Projectile::update(std::vector<shptr<Monster>> &allMonsters)
{
    move();
    if (getTarget())
    {
        if (checkHit(target))
        {
            targetHit();
            removeProjectile();
            return void();
        }
    }

    for (shptr<Monster> aMonster : allMonsters)
    {
        if (checkHit(aMonster))
        {
            dealDamage(aMonster);
            removeProjectile();
            return void();
        }
    }
}

void Projectile::dealDamage(shptr<Monster> &aMonster)
{
    aMonster->takePushBackDmg(damage, 10, true);
}

// Set the projectile's cordinates to outside of the map so that
// cleanUp() removes it in gameState
void Projectile::removeProjectile()
{
    speed = 0;
    projectileSprite.setPosition(-100,-100);
    y = -100;
}

void Projectile::render(sf::RenderTarget &window)
{
    window.draw(projectileSprite);
}


void Projectile::targetHit()
{
    if (getTarget())
    {
        target->takePushBackDmg(damage, 10, true);
    }
}

sf::FloatRect Projectile::getBounds()
{
    return projectileSprite.getGlobalBounds();
}

bool Projectile::checkHit(shptr<Monster> &aMonster)
{
    if (sqrt( pow( aMonster->getX() - x, 2 ) + pow( aMonster->getY() - y, 2 ) ) -
        (aMonster->getRadius() + radius) < 0)
    {
        return true;
    }
    else return false;
}

double Projectile::getRadius()
{
    return radius;
}


void Projectile::setAngle()
{
        double xPos{target->getX() - x};
        double yPos{target->getY() - y};
        angle = atan2(yPos,xPos);         
        projectileSprite.setRotation(angle / (2 * 3.1415926535897) * 360);
        xDir = cos(angle);
        yDir = sin(angle);
}

//Anvil



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
    speed = 4;
    damage = 4;
    radius = 2.5;
}

minigunProjectile::minigunProjectile(double x, double y, double dirByRadians)
: Projectile(x, y, dirByRadians)
{
    projectileTexture.loadFromFile("resources/images/minigunProjectile.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setOrigin(16, 16);
    projectileSprite.setPosition(x,y);
    speed = 4;
    damage = 4;
    radius = 2.5;
}

MissileProjectile::MissileProjectile(double x, double y, double dirByRadians, shptr<Monster> Monstertarget)
: Projectile(x, y, dirByRadians)
{
    target = Monstertarget;
    projectileTexture.loadFromFile("resources/images/missileProjectile.png");
    projectileSprite.setTexture(projectileTexture);
    //projectileSprite = missileSheet.get_sprite(0, 0);
    projectileSprite.setOrigin(16, 16);
    projectileSprite.setPosition(x,y);
    projectileSprite.setRotation(+ dirByRadians * 360 / (2 * 3.1415));
    speed = 4;
    damage = 30;
    radius = 8;
}


MissileProjectile::MissileProjectile(double x, double y, double xDir, double yDir)
:Projectile(x, y , xDir, yDir)
{
    projectileTexture.loadFromFile("resources/images/missileProjectile.png");
    projectileSprite.setTexture(projectileTexture);
    //projectileSprite = missileSheet.get_sprite(0, 0);
    projectileSprite.setOrigin(16, 16);
    projectileSprite.setPosition(x,y);
    projectileSprite.setRotation(atan2(yDir,xDir));
    speed = 4;
    damage = 30;
    radius = 8;
}

MissileProjectile::MissileProjectile(double x, double y, double dirByRadians)
:Projectile(x, y, dirByRadians)
{
    projectileTexture.loadFromFile("resources/images/missileProjectile.png");
    projectileSprite.setTexture(projectileTexture);
    //projectileSprite = missileSheet.get_sprite(0, 0);
    projectileSprite.setOrigin(16, 16);
    projectileSprite.setPosition(x,y);
    projectileSprite.setRotation(dirByRadians * 360 / (2 * 3.1415));
    speed = 4;
    damage = 30;
    radius = 8;
}

// Deals damage too all Monsters within a circle of 20 pixels of the missile when it hits
void MissileProjectile::dealDamage(shptr<Monster> &aMonster)
{
    if (pow(aMonster->getX() - getX(), 2) + pow(aMonster->getY() - getY(), 2) < 400)
    {
        aMonster->takeDamage(damage);
    }
}

void MissileProjectile::update(std::vector<shptr<Monster>> &allMonsters)
{
   if (currSprite > 0)
    {
        if (currSprite > 3)
        {
            //projectileSprite = missileSheet.get_sprite(0, currSprite);
            removeProjectile();
            return void();
        }
        
        
            currSprite = currSprite + 1;
            return void();
        
    }
    move();
    for (shptr<Monster> aMonster : allMonsters)
    {
        if (checkHit(aMonster))
        {
            for (shptr<Monster> anotherMonster : allMonsters)
            {
                dealDamage(anotherMonster);
            }
            currSprite = currSprite + 1;
            return void();
        }
    }
}