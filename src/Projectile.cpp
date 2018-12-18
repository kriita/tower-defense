#include "Projectile.h"
#include "defs.h"
#include "Monster.h"
#include "Effect.h"
#include <cmath>
#include <vector>
#include <memory>



Projectile::Projectile(double x, double y, double xDir, double yDir, double attackPower)
: x {x}, y {y}, xDir {xDir}, yDir {yDir}, damage {attackPower} {}

Projectile::Projectile(double x, double y, double dirByRadians, double attackPower)
: x {x}, y {y}, xDir {cos(dirByRadians)}, yDir {sin(dirByRadians)}, damage {attackPower} {}

void Projectile::setx(double const new_x)
{
    x = new_x;
}

void Projectile::sety(double const new_y)
{
    y = new_y;
}

double Projectile::getX() const // Coordinates in pixels
{
    return x;
}

double Projectile::getY() const
{
    return y;
}

void Projectile::setxDir(double const new_xDir)
{
    xDir = new_xDir;
}

void Projectile::setyDir(double const new_yDir)
{
    yDir = new_yDir;
}

void Projectile::setDirByRadians(double const newAngle)
{
    angle = newAngle;
    xDir = cos(angle);
    yDir = sin(angle);
    projectileSprite.setRotation(angle * 360 / (2 * 3.1415));
}

double Projectile::getxDir() const
{
    return xDir;
}

double Projectile::getyDir() const
{
    return yDir;
}

double Projectile::getDirByRadians() const
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

double Projectile::getSpeed() const
{
    return speed;
}

void Projectile::setSpeed(double const newSpeed)
{
    speed = newSpeed;
}

// Returns nullptr (false) if Projectile has no target
shptr<Monster> Projectile::getTarget() const
{
   return target;

}

void Projectile::setTarget(shptr<Monster> const &newTarget)
{
    target = newTarget;
}

void Projectile::move()
{
    if (getTarget() != nullptr)     // Update coordinates.
                                    // If Projectile has target, then setAngle()
    {
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

void Projectile::dealDamage(shptr<Monster> &aMonster) const
{
    aMonster->takeDamage(damage);
}

// Set the projectile's cordinates to outside of the map so that
// cleanUp() removes it in gameState
void Projectile::removeProjectile()
{
    speed = 0;
    projectileSprite.setPosition(-100,-100);
    projectileSprite.setRotation(0);
}

void Projectile::render(sf::RenderTarget &window) const
{
    window.draw(projectileSprite);
}


void Projectile::targetHit() const
{
    if (getTarget())
    {
        target->takeDamage(damage);
    }
}

sf::FloatRect Projectile::getBounds() const
{
    return projectileSprite.getGlobalBounds();
}

bool Projectile::checkHit(shptr<Monster> const &aMonster) const
{
    if (sqrt( pow( aMonster->getX() - x, 2 ) + pow( aMonster->getY() - y, 2 ) ) -
        (aMonster->getRadius() + radius) < 0)
    {
        return true;
    }
    else return false;
}

double Projectile::getRadius() const
{
    return radius;
}


void Projectile::setAngle()
{
        if (target != nullptr && !target->isDead())
        {
        double xPos{target->getX() - x};
        double yPos{target->getY() - y};
        angle = atan2(yPos,xPos);         
        projectileSprite.setRotation(angle / (2 * 3.1415926535897) * 360);
        xDir = cos(angle);
        yDir = sin(angle);
        }
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

minigunProjectile::minigunProjectile(double x, double y, double xDir, double yDir, double attackPower)
: Projectile(x, y, xDir, yDir, attackPower)
{
    projectileTexture.loadFromFile("resources/images/minigunProjectile.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setOrigin(16, 16);
    projectileSprite.setPosition(x,y);
    speed = 4;
    radius = 2.5;
}

minigunProjectile::minigunProjectile(double x, double y, double dirByRadians, double attackPower)
: Projectile(x, y, dirByRadians, attackPower)
{
    projectileTexture.loadFromFile("resources/images/minigunProjectile.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setOrigin(16, 16);
    projectileSprite.setPosition(x,y);
    speed = 4;
    radius = 2.5;
}

//  MissileProjectil

MissileProjectile::MissileProjectile(double x, double y, double dirByRadians, double attackPower, shptr<Monster> Monstertarget)
: Projectile(x, y, dirByRadians, attackPower)
{
    target = Monstertarget;
    projectileTexture.loadFromFile("resources/images/missileProjectile.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setOrigin(16, 16);
    projectileSprite.setPosition(x,y);
    projectileSprite.setRotation(+ dirByRadians * 360 / (2 * 3.1415));
    speed = 4;
    radius = 8;
}


MissileProjectile::MissileProjectile(double x, double y, double xDir, double yDir, double attackPower)
:Projectile(x, y, xDir, yDir, attackPower)
{
    projectileTexture.loadFromFile("resources/images/missileProjectile.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setOrigin(16, 16);
    projectileSprite.setPosition(x,y);
    projectileSprite.setRotation(atan2(yDir,xDir));
    speed = 4;
    radius = 8;
}

MissileProjectile::MissileProjectile(double x, double y, double dirByRadians, double attackPower)
:Projectile(x, y, dirByRadians, attackPower)
{
    projectileTexture.loadFromFile("resources/images/missileProjectile.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setOrigin(16, 16);
    projectileSprite.setPosition(x,y);
    projectileSprite.setRotation(dirByRadians * 360 / (2 * 3.1415));
    speed = 4;
    radius = 8;
}

// Deals damage too all Monsters within a circle of 20 pixels of the missile when it hits
void MissileProjectile::dealDamage(shptr<Monster> &aMonster) const
{
    if (pow(aMonster->getX() - getX(), 2) + pow(aMonster->getY() - getY(), 2) < 400)
    {
        aMonster->takeStunDmg(damage, 3, 30, false);
    }                           // 3 sec stun with 30 % change
}

void MissileProjectile::update(std::vector<shptr<Monster>> &allMonsters)
{
    if (explodeEffect) // checking if projectile is exploding
    {
        explodeAnim();
        explodeEffect->update();
        if(explodeEffect->checkRemove())
        {
            removeProjectile(); // Removes the projectile (and indirectly the effect)
        }
    
        return void();
    }
    else
    {
        move();

        for (shptr<Monster> aMonster : allMonsters)
        {
            if (checkHit(aMonster))
            {
                for (shptr<Monster> anotherMonster : allMonsters)
                {
                    dealDamage(anotherMonster);
                }
                // Make an effect for the explosion
            explodeEffect = std::make_shared<MissileExplosion>(aMonster->getX(),
                                                               aMonster->getY());
                return void();
            }
        }
    }
}

void MissileProjectile::render(sf::RenderTarget &window) const
{
    if (explodeEffect)
    {
        explodeEffect->render(window);
    }
    else window.draw(projectileSprite);
}

void MissileProjectile::explodeAnim() const
{
    if (explodeEffect)
    {
        explodeEffect->changeSprite(); // changeSprite() updates effectSprite if enough
        explodeEffect->update();       // time has passed
    }                                                         
}


// LaserProjectile

LaserProjectile::LaserProjectile(double x, double y, double dirByRadians, double attackPower, shptr<Monster> Monstertarget, double newduration)
:Projectile(x, y, dirByRadians, attackPower), duration{newduration}
{
    target = Monstertarget;
    projectileTexture.loadFromFile("resources/images/laserBeam.png");
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setPosition(x,y);
    projectileSprite.setOrigin(0,4.5);
    setDirByRadians(dirByRadians);
    speed = 0;
    damage = attackPower;
}

void LaserProjectile::update(std::vector<shptr<Monster>> &allMonsters)
{
    if (laserClock.getElapsedTime().asSeconds() > duration) { removeProjectile(); }

  
    if (transparencyState == 0)
    {
        transparency += 255 / duration / 15;
        if (transparency >= 255) 
            transparencyState += 1;
    }
    else if (transparencyState == 1 && laserClock.getElapsedTime().asSeconds() > (duration * 3 / 4))
        transparencyState += 1;
    else if (transparencyState == 2)
        transparency -= 255 / duration / 15;
    projectileSprite.setColor(sf::Color(255, 255, 255, transparency)); 

/*
    for (shptr<Monster> aMonster : allMonsters)
    {
        if (checkHit(aMonster))
        {
            for (shptr<Monster> anotherMonster : allMonsters)
            {
                dealDamage(anotherMonster);
            }
        }
    }*/
    
    laserDamage(allMonsters);
}

void LaserProjectile::laserDamage(std::vector<shptr<Monster>> &allMonsters) const
{
    for (shptr<Monster> aMonster : allMonsters)
    {
        if (checkHit(aMonster)) {aMonster->takeDamage(damage);}
    }
}


bool LaserProjectile::checkHit(shptr<Monster> const &aMonster) const
{
    if (getBounds().intersects( aMonster->getBounds() ))
    {   
        double xTest{x};
        double yTest{y};
        double testRadius{5};
        double monsterRadius{aMonster->getRadius()};
        double monsterX{aMonster->getX()};
        double monsterY{aMonster->getY()};

  
        while (0 < xTest && xTest < 32*20 && 0 < yTest && yTest < 32*20)
        {
            if ( pow((monsterX - xTest),2) + pow((monsterY - yTest),2) <= pow(testRadius + monsterRadius,2))
                return true;
            xTest += cos(angle) * testRadius;
            yTest += sin(angle) * testRadius;
        }
        return false;
    }
    return false;
}

void LaserProjectile::render(sf::RenderTarget &window) const
{
    window.draw(projectileSprite);
  /*  sf::FloatRect rect1(projectileSprite.getGlobalBounds());
    window.draw( sf::Rect{rect1.left(), rect1.top(), rect1.width(), rect1.height()} );*/
}