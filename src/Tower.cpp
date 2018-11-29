#include "Tower.h"
#include "constants.h"
#include <cmath>

void Tower::render(sf::RenderTarget &target)
{
    target.draw(towerSprite);
}

void Tower::update(std::vector<shptr<Monster>> & monstervector)
{
    if (target == nullptr)
    {
        towerSprite.setRotation(towerSprite.getRotation() + 20);
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
        double x{target->getX() - xPos};
        double y{target->getY() - yPos};
        towerSprite.setRotation(atan2(y,x) / (2 * 3.1415926535897) * 360 + 90);
        attack();
    }
    else
        target = nullptr;
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
    return attackPower;
}

void Tower::setTarget(shptr<Monster> newTarget)
{
    target = newTarget;
}

bool Tower::inRange(shptr<Monster> monster)
{
    return pow((monster->getX() - xPos),2) + pow((monster->getY() - yPos),2) <= pow(range,2);
}


Tower::Tower(double x, double y)
    :   xPos{x}, yPos{y} 
    {
        //attackPower = 1;
        range = 100;
    }

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

void Tower1::attack() 
{
    target->takeDamage(attackPower);
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

void AnvilTower::attack() {}

int AnvilTower::getPrice() {return 9000;}
