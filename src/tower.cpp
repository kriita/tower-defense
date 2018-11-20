#include "tower.h"
#include "constants.h"

#include <random>

void Tower::render(sf::RenderTarget &target)
{

    target.draw(towerSprite);
}

void Tower::update()
{
    angle += 3;
    towerSprite.setRotation(angle);
}

Tower::Tower(int x, int y)
: xPos {x}, yPos {y} {}

Tower1::Tower1(int x, int y)
: Tower {x, y}
{
    towerSprite = towerSpriteSheet.get_sprite(11, 0);

    towerSprite.setPosition (mapBorderOffset + tileWidth / 2 + tileWidth * xPos,
                            mapBorderOffset + tileWidth / 2 + tileWidth * yPos);
    towerSprite.setOrigin (tileWidth/2, tileWidth/2);
}

void Tower1::attack()
{}

int Tower1::getX() const
{
    return xPos;
}

int Tower1::getY() const
{
    return yPos;
}

int Tower1::getAngle() const
{
    return angle;
}

int Tower1::getFireRate() const
{
    return fireRate;
}

int Tower1::getAttackPower() const
{
    return attackPower;
}