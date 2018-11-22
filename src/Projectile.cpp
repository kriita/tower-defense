#include "Projectile.h"
#include "Monster.h"

/*
 *  Funktioner kvar att definiera:
 *  virtual void monsterHit()
    virtual void explodeAnim() // renders the explode animation
    void isOutsideMap()
    virtual Move()
    void renderMe()
 */

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

    //template<class T>
    bool Projectile::getTarget() // Returns false if Projectile has no target
    {
        if (target == nullptr)
        {
            return false;
        }
        else 
        return true;
        //return target;
    }

void Projectile::setTarget(shptr<Monster> newTarget)
{
    target = newTarget;
}