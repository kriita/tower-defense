#ifndef TOWER_H
#define TOWER_H

#include "Spritesheet.h"
#include <SFML/Graphics.hpp>

/*
 *  Tower
 */
class Tower
{
public:
    Tower(int x, int y);
    virtual ~Tower() = default;

    void render(sf::RenderTarget &target);
    void update();

    virtual void attack() = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual int getAngle() const = 0;
    virtual int getFireRate() const = 0;
    virtual int getAttackPower() const = 0;

protected:
    int xPos {};
    int yPos {};
    float angle {30};
    int fireRate {};
    int attackPower {};

    Spritesheet towerSpriteSheet {"resources/images/spritesheet.png", 32, 32}; //temporär
    sf::Sprite towerSprite {};
};

/*
 *  Tower 1
 */
class Tower1 : public Tower
{
public:
    Tower1(int x, int y);
    void attack() override;
    int getX() const override;
    int getY() const override;
    int getAngle() const override;
    int getFireRate() const override;
    int getAttackPower() const override;
};

#endif