#include "Projectile.h"
#include "defs.h"
#include "Map.h"
#include "Monster.h"

/*
 *  Funktioner kvar att definiera:
 *  virtual void monsterHit()
    virtual void explodeAnim() // renders the explode animation
    void isOutsideMap()
    virtual Move()
 */


Projectile::Projectile(int x, int y, int xDir, int yDir)
: x {x}, y {y}, xDir {xDir}, yDir {yDir} {}


void Projectile::setx(int new_x)
{
    x = new_x;
}

void Projectile::sety(int new_y)
{
    y = new_y;
}

int Projectile::getX() // Coordinates in pixels
{
    return x;
}

int Projectile::getY()
{
    return y;
}

void Projectile::setxDir(int new_xDir)
{
    xDir = new_xDir;
}

void Projectile::setyDir(int new_yDir)
{
    yDir = new_yDir;
}

int Projectile::getxDir()
{
    return xDir;
}

int Projectile::getyDir()
{
    return yDir;
}

double Projectile::getSpeed()
{
    return speed;
}

void Projectile::setSpeed(int newSpeed)
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
}


void Projectile::render(sf::RenderTarget &window)
{
    window.draw(projectileSprite);
}




/*
void Projectile::targetHit()
{
    if (getTarget())
    {
        target->takeDmg
    }
}
*/

Anvil::Anvil()
: Projectile {}
{
    projectileTexture.loadFromFile("resources/images/anvil_t.png");
    projectileSprite.setTexture(projectileTexture);
}


Anvil::Anvil(int x, int y, int xDir, int yDir)
: Projectile {x, y, xDir, yDir}
{
    projectileTexture.loadFromFile("resources/images/anvil_t.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setOrigin(512, 512);
    projectileSprite.setPosition(x,y);
}
