#ifndef TOWER_H
#define TOWER_H

#include "Spritesheet.h"
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Monster.h"
#include "defs.h"


/*
 *  Tower
 */
class Tower
{
public:
    Tower(int x, int y);
    Tower(double x, double y);
    Tower(shptr<Tile> tile);

    virtual ~Tower() = default;

    void render(sf::RenderTarget &target);
    void update(std::vector<shptr<Monster>> & monstervector);

    virtual void attack() = 0;
    virtual int getPrice() = 0;
    double getX() const;       //behövs dessa ens?
    double getY() const;       //
    double getFireRate() const;
    double getAttackPower() const;
    void setTarget(shptr<Monster> newTarget);
    bool inRange(shptr<Monster> monster);

protected:
    double xPos{};
    double yPos{};
    double fireRate{};
    double attackPower{};
    double range{};
    shptr<Monster> target{};

    

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
    Tower1(double x, double y);
    Tower1(shptr<Tile> tile);
    void attack() override;
    int getPrice() override;
};

#endif