#include "Tower.h"
#include "constants.h"
#include "Projectile.h"
#include <cmath>
#include <memory>
#include "defs.h"
#include <vector>
#include "Effect.h"

#include <iostream>

void Tower::render(sf::RenderTarget &target)
{
    target.draw(towerSprite);
}

void Tower::update(std::vector<shptr<Monster>> & monstervector, 
                   std::vector<shptr<Projectile>> & projectiles)
{
    if (target == nullptr)
    {
        towerSprite.setRotation(towerSprite.getRotation() + 0);
        if (!monstervector.empty()) 
        {
            for (auto & monster : monstervector)
            {
                if (inRange(monster))
                {
                target = monster;
                break;
                }
            }
        }
    }
    else if (inRange(target) && !(target->isDead()))
    {
        setAngle();
        if (attackClock.getElapsedTime().asSeconds() > fireRate.front())
        {
            attack(projectiles);
            attackClock.restart();
        }
    }
    else
        target = nullptr;
}

void Tower::setAngle()
{
        double x{target->getX() - xPos};
        double y{target->getY() - yPos};
        angle = atan2(y,x);         
        towerSprite.setRotation(angle / (2 * 3.1415926535897) * 360);
}

double Tower::getX() const
{
    return xPos;
}

double Tower::getY() const
{
    return yPos;
}

double Tower::getFireRate() const
{
    return fireRate.front();
}

double Tower::getAttackPower() const
{
    return attackPower.front();
}

double Tower::getRange() const
{
    return range.front();
}

void Tower::setTarget(shptr<Monster> newTarget)
{
    target = newTarget;
}

bool Tower::inRange(shptr<Monster> monster)
{
    return pow((monster->getX() - xPos),2) + pow((monster->getY() - yPos),2) <= pow(range.front(),2);
}

void Tower::upgradeFireRate()
{
    fireRatePrice.erase(fireRatePrice.begin());
    fireRate.erase(fireRate.begin());
}

void Tower::upgradeRange()
{
    rangePrice.erase(rangePrice.begin());
    range.erase(range.begin());
}

void Tower::upgradeAttackPower()
{
    attackPowerPrice.erase(attackPowerPrice.begin());
    fireRate.erase(fireRate.begin());
}

int Tower::getRangeUpgradePrice()
{
    if (rangePrice.empty())
    {
        return 0;
    }
    else
    {
        return rangePrice.front();
    }
}

int Tower::getAttackPowerUpgradePrice()
{
    if (attackPowerPrice.empty())
    {
        return 0;
    }
    else
    {
        return attackPowerPrice.front();
    }
}

int Tower::getFireRateUpgradePrice()
{
    if (fireRatePrice.empty())
    {
        return 0;
    }
    else
    {
        return fireRatePrice.front();
    }
}

void Tower::setPosition(double x, double y)
{
    xPos = x;
    yPos = y;
    towerSprite.setPosition(xPos,yPos);
}

Tower::Tower(double x, double y)
    :   xPos{x}, yPos{y} {}

Tower::Tower(int x, int y)
    :   Tower {mapBorderOffset + tileWidth / 2 + tileWidth * x, 
               mapBorderOffset + tileWidth / 2 + tileWidth * y} {}

Tower::Tower(shptr<Tile> tile)
    :   Tower{tile->getX(), tile->getY()} {}

// MinigunTower

MinigunTower::MinigunTower(double x, double y)
    : Tower{x,y} 
{
    texture.loadFromFile("resources/images/minigunTowerTemp.png");
    towerSprite = sf::Sprite{texture};    
    towerSprite.setPosition (xPos,yPos);
    towerSprite.setOrigin (tileWidth/2, tileWidth/2);
    fireRate = {0.1, 0.08, 0.06, 0.04, 0.02};   //Time in seconds between each attack.
    fireRatePrice = {100, 200, 300, 400};
    attackPower = {4, 8, 12, 16, 20};
    attackPowerPrice = {100, 200, 300, 400};
    range = {100.0, 130.0, 180.0, 230.0, 270.0};
    rangePrice = {100, 200, 300, 400};
} 

MinigunTower::MinigunTower(int x, int y)
    : MinigunTower{mapBorderOffset + tileWidth / 2 + tileWidth * x, 
              mapBorderOffset + tileWidth / 2 + tileWidth * y} {}

MinigunTower::MinigunTower(shptr<Tile> tile)
    :   MinigunTower{tile->getX(), tile->getY()} {}

void MinigunTower::attack(std::vector<shptr<Projectile>> & projectiles) 
{
    projectiles.push_back(std::make_shared<minigunProjectile> (xPos + cos(angle) * 16, yPos + sin(angle) * 16, angle, attackPower.front()));
}

int MinigunTower::getPrice() {return 100;}

void MinigunTower::setAngle()
{
        double x{target->getX() + target->getXDir() * target->getSpeed() * 7 - xPos};
        double y{target->getY() + target->getYDIr() * target->getSpeed() * 7 - yPos};
        angle = atan2(y,x);         
        towerSprite.setRotation(angle / (2 * 3.1415926535897) * 360);
}

// MissileTower

MissileTower::MissileTower(double x, double y)
    : Tower{x,y} 
{    
    texture.loadFromFile("resources/images/missileTower.png");
    towerSprite = sf::Sprite{texture};    
    towerSprite.setPosition (xPos,yPos);
    towerSprite.setOrigin (tileWidth/2, tileWidth/2);
    fireRate = {1, 2, 1.5, 1.0, 0.5};   //Time in seconds between each attack.
    fireRatePrice = {100, 200, 300, 400};
    attackPower = {30, 50, 100, 200, 400};
    attackPowerPrice = {100, 200, 400, 800};
    range = {100.0, 130.0, 180.0, 230.0, 270.0};
    rangePrice = {100, 200, 300, 400};
} 

MissileTower::MissileTower(int x, int y)
    : MissileTower{mapBorderOffset + tileWidth / 2 + tileWidth * x, 
              mapBorderOffset + tileWidth / 2 + tileWidth * y} {}

MissileTower::MissileTower(shptr<Tile> tile)
    :   MissileTower{tile->getX(), tile->getY()} {}

void MissileTower::attack(std::vector<shptr<Projectile>> & projectiles) 
{
    projectiles.push_back(std::make_shared<MissileProjectile> (xPos + cos(angle) * 16, yPos + sin(angle) * 16, angle, attackPower.front(), target));
}

int MissileTower::getPrice() {return 500;}

// SlowTower

SlowTower::SlowTower(double x, double y)
    : Tower{x,y} 
{    
    texture.loadFromFile("resources/images/snowman.png");
    towerSprite = sf::Sprite{texture};    
    towerSprite.setPosition (xPos,yPos);
    towerSprite.setOrigin (tileWidth/2, tileWidth/2);
} 

SlowTower::SlowTower(int x, int y)
    : SlowTower{mapBorderOffset + tileWidth / 2 + tileWidth * x, 
              mapBorderOffset + tileWidth / 2 + tileWidth * y} {}

SlowTower::SlowTower(shptr<Tile> tile)
    :   SlowTower{tile->getX(), tile->getY()} {}



int SlowTower::getPrice() {return 500;}

void SlowTower::upgradeSlow(int & cash)
{
        if (!slowPrice.empty() && cash >= slowPrice.front())
    {
        cash -= slowPrice.front();
        slowPrice.erase(slowPrice.begin());
        slow.erase(slow.begin());
    }
}

void SlowTower::upgradeDuration(int & cash)
{
        if (!durationPrice.empty() && cash >= durationPrice.front())
    {
        cash -= durationPrice.front();
        durationPrice.erase(durationPrice.begin());
        duration.erase(duration.begin());
    }
}


void SlowTower::update(std::vector<shptr<Monster>> & monstervector, 
                   std::vector<shptr<Projectile>> & projectiles)
{
    if (slowAttack(monstervector))
    {
        if (slowEffect == nullptr)
            slowEffect = std::make_unique<Slow> (static_cast<float>(xPos), static_cast<float>(yPos), static_cast<float>(range.front()));
    }
    else if (slowEffect != nullptr)
    {
        if (slowEffect->checkRemove())
            slowEffect.reset();
        else
            slowEffect->update();
    }
}

bool SlowTower::slowAttack(std::vector<shptr<Monster>> & monstervector)
{
    bool active {false};

    for (auto & monster : monstervector)
    {
        if (inRange(monster))
        {
            active = true;
            monster->takeSlowDmg(attackPower.front(), slow.front(), duration.front(), true);
        }
    }

    return active;
}

void SlowTower::render(sf::RenderTarget &target)
{    
    if (slowEffect != nullptr)
        slowEffect->render(target);
    target.draw(towerSprite);
}

void SlowTower::attack(std::vector<shptr<Projectile>> & projectiles) 
{}


// Lasertower

LaserTower::LaserTower(double x, double y)
    : Tower{x,y} 
{    
    texture.loadFromFile("resources/images/laserTower.png");
    towerSprite = sf::Sprite{texture};    
    towerSprite.setPosition (xPos,yPos);
    towerSprite.setOrigin (tileWidth/2, tileWidth/2);
    laserTexture.loadFromFile("resources/images/laserBeam.png");
    laserSprite = sf::Sprite{laserTexture};
    laserSprite.setPosition(xPos,yPos);
    laserSprite.setColor(sf::Color(255, 255, 255, 0));
    fireRate = {2.5, 2, 1.5, 1.0, 0.5};   //Time in seconds between each attack.
    fireRatePrice = {100, 200, 300, 400};
    attackPower = {1, 1.5, 2.0, 2.5, 3.0};
    attackPowerPrice = {100, 200, 300, 400};
    range = {100.0, 130.0, 180.0, 230.0, 270.0};
    rangePrice = {100, 200, 300, 400};
}


LaserTower::LaserTower(shptr<Tile> tile)
    :   LaserTower{tile->getX(), tile->getY()} {}

void LaserTower::attack(std::vector<shptr<Projectile>> & projectiles) 
{
    laserBeam = std::make_shared<LaserProjectile> (xPos, yPos, angle, attackPower.front(), target, duration);
    projectiles.push_back(laserBeam);

}




int LaserTower::getPrice() {return 1000;}

void LaserTower::update(std::vector<shptr<Monster>> & monstervector, 
                   std::vector<shptr<Projectile>> & projectiles)
{
    if (laserBeam != nullptr) { laserBeam->setDirByRadians(angle); }


    if (target == nullptr)
    {
        towerSprite.setRotation(towerSprite.getRotation() + 0);
        if (!monstervector.empty()) 
        {
            for (auto & monster : monstervector)
            {
                if (inRange(monster))
                {
                target = monster;
                break;
                }
            }
        }
    }
    else if (inRange(target) && !(target->isDead()))
    {
        setAngle();
        if (attackClock.getElapsedTime().asSeconds() > fireRate.front())
        {
            attack(projectiles);
            attackClock.restart();
        }
        else if (laserBeam != nullptr)
        {}
    }
    else
        target = nullptr;
}

