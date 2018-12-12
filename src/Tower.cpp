#include "Tower.h"
#include "constants.h"
#include "Projectile.h"
#include <cmath>
#include <memory>
#include "defs.h"
#include <vector>

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
      /*  double x{target->getX() - xPos};
        double y{target->getY() - yPos};
        angle = atan2(y,x);         //använd setangle istället
        towerSprite.setRotation(angle / (2 * 3.1415926535897) * 360);
*/
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
        angle = atan2(y,x);         //använd setangle istället
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

void Tower::upgradeFireRate(int & cash)
{
    if (!fireRatePrice.empty() && cash >= fireRatePrice.front())
    {
        cash -= fireRatePrice.front();
        fireRatePrice.erase(fireRatePrice.begin());
        fireRate.erase(fireRate.begin());
    }
}

void Tower::upgradeRange(int & cash)
{
    if (!rangePrice.empty() && cash >= rangePrice.front())
    {
        cash -= rangePrice.front();
        rangePrice.erase(rangePrice.begin());
        range.erase(range.begin());
    }
}

void Tower::upgradeAttackPower(int & cash)
{
    if (!attackPowerPrice.empty() && cash >= attackPowerPrice.front())
    {
        cash -= attackPowerPrice.front();
        attackPowerPrice.erase(attackPowerPrice.begin());
        fireRate.erase(fireRate.begin());
    }
}

Tower::Tower(double x, double y)
    :   xPos{x}, yPos{y} {}

Tower::Tower(int x, int y)
    :   Tower {mapBorderOffset + tileWidth / 2 + tileWidth * x, 
               mapBorderOffset + tileWidth / 2 + tileWidth * y} {}

Tower::Tower(shptr<Tile> tile)
    :   Tower{tile->getX(), tile->getY()} {}

// Tower1

Tower1::Tower1(double x, double y)
    : Tower{x,y} 
{
    towerSprite = towerSpriteSheet.get_sprite(11, 0);
    towerSprite.setPosition (xPos,yPos);
    towerSprite.setOrigin (tileWidth/2, tileWidth/2);
} 

Tower1::Tower1(int x, int y)
    : Tower1 {mapBorderOffset + tileWidth / 2 + tileWidth * x, 
              mapBorderOffset + tileWidth / 2 + tileWidth * y} {}

Tower1::Tower1(shptr<Tile> tile)
    :   Tower1{tile->getX(), tile->getY()} {}

void Tower1::attack(std::vector<shptr<Projectile>> & projectiles) 
{
    target->takeDamage(attackPower.front());
}

int Tower1::getPrice() {return 420;}

// AnvilTower

AnvilTower::AnvilTower(double x, double y)
    : Tower{x,y} 
{
    towerSprite = towerSpriteSheet.get_sprite(11, 0);
    towerSprite.setPosition (xPos,yPos);
    towerSprite.setOrigin (tileWidth/2, tileWidth/2);
} 

AnvilTower::AnvilTower(int x, int y)
    : AnvilTower{mapBorderOffset + tileWidth / 2 + tileWidth * x, 
              mapBorderOffset + tileWidth / 2 + tileWidth * y} {}

AnvilTower::AnvilTower(shptr<Tile> tile)
    :   AnvilTower{tile->getX(), tile->getY()} {}

void AnvilTower::attack(std::vector<shptr<Projectile>> & projectiles) {}

int AnvilTower::getPrice() {return 9000;}

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
    attackPower = {1.0, 1.5, 2.0, 2.5, 3.0};
    attackPowerPrice = {100, 200, 300, 400};
    range = {70.0, 130.0, 180.0, 230.0, 270.0};
    rangePrice = {100, 200, 300, 400};
} 

MinigunTower::MinigunTower(int x, int y)
    : MinigunTower{mapBorderOffset + tileWidth / 2 + tileWidth * x, 
              mapBorderOffset + tileWidth / 2 + tileWidth * y} {}

MinigunTower::MinigunTower(shptr<Tile> tile)
    :   MinigunTower{tile->getX(), tile->getY()} {}

void MinigunTower::attack(std::vector<shptr<Projectile>> & projectiles) 
{
    projectiles.push_back(std::make_shared<minigunProjectile> (xPos + cos(angle) * 16, yPos + sin(angle) * 16, angle));
}

int MinigunTower::getPrice() {return 9000;}

void MinigunTower::setAngle()
{
        double x{target->getX() + target->getXDir() * target->getSpeed() * 7 - xPos};
        double y{target->getY() + target->getYDIr() * target->getSpeed() * 7 - yPos};
        angle = atan2(y,x);         //använd setangle istället
        towerSprite.setRotation(angle / (2 * 3.1415926535897) * 360);
}

// MissileTower

MissileTower::MissileTower(double x, double y)
    : Tower{x,y} 
{    
    texture.loadFromFile("resources/images/minigunTowerTemp.png");
    towerSprite = sf::Sprite{texture};    
    towerSprite.setPosition (xPos,yPos);
    towerSprite.setOrigin (tileWidth/2, tileWidth/2);
    fireRate = {2.5, 2, 1.5, 1.0, 0.5};   //Time in seconds between each attack.
    fireRatePrice = {100, 200, 300, 400};
    attackPower = {1.0, 1.5, 2.0, 2.5, 3.0};
    attackPowerPrice = {100, 200, 300, 400};
    range = {70.0, 130.0, 180.0, 230.0, 270.0};
    rangePrice = {100, 200, 300, 400};
} 

MissileTower::MissileTower(int x, int y)
    : MissileTower{mapBorderOffset + tileWidth / 2 + tileWidth * x, 
              mapBorderOffset + tileWidth / 2 + tileWidth * y} {}

MissileTower::MissileTower(shptr<Tile> tile)
    :   MissileTower{tile->getX(), tile->getY()} {}

void MissileTower::attack(std::vector<shptr<Projectile>> & projectiles) 
{
    projectiles.push_back(std::make_shared<minigunProjectile> (xPos + cos(angle) * 16, yPos + sin(angle) * 16, angle));
}

int MissileTower::getPrice() {return 9000;}

// SlowTower

SlowTower::SlowTower(double x, double y)
    : Tower{x,y} 
{    
    texture.loadFromFile("resources/images/minigunTowerTemp.png");
    towerSprite = sf::Sprite{texture};    
    towerSprite.setPosition (xPos,yPos);
    towerSprite.setOrigin (tileWidth/2, tileWidth/2);
} 

SlowTower::SlowTower(int x, int y)
    : SlowTower{mapBorderOffset + tileWidth / 2 + tileWidth * x, 
              mapBorderOffset + tileWidth / 2 + tileWidth * y} {}

SlowTower::SlowTower(shptr<Tile> tile)
    :   SlowTower{tile->getX(), tile->getY()} {}

void SlowTower::attack(std::vector<shptr<Projectile>> & projectiles) 
{
    target->takeSlowDmg(attackPower.front(),attackPower.front(),1,true);
}

int SlowTower::getPrice() {return 9000;}

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