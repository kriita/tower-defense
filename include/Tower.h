#ifndef TOWER_H
#define TOWER_H

#include "Spritesheet.h"
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Monster.h"
#include "defs.h"
#include "Projectile.h"

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
    void update(std::vector<shptr<Monster>> & monstervector, 
                std::vector<shptr<Projectile>> & projectiles);

    virtual void attack(std::vector<shptr<Projectile>> & projectiles) = 0;
    virtual int getPrice() = 0;
    double getX() const;       //behövs dessa ens?
    double getY() const;       //
    double getFireRate() const;
    double getAttackPower() const;
    double getRange() const;
    void setTarget(shptr<Monster> newTarget);
    bool inRange(shptr<Monster> monster);
    void upgradeRange(int & cash);                      //Takes the player's cash as argument to subtract the upgrade price if there's sufficient funds to upgrade.
    void upgradeAttackPower(int & cash);
    void upgradeFireRate(int & cash);
    

protected:
    double xPos{};
    double yPos{};
    double angle{}; //radians
    shptr<Monster> target{};
    std::vector<double> fireRate = {0.1, 0.08, 0.06, 0.04, 0.02};   //Time in seconds between each attack.
    std::vector<double> fireRatePrice = {100, 200, 300, 400};
    std::vector<double> attackPower = {1.0, 1.5, 2.0, 2.5, 3.0};
    std::vector<double> attackPowerPrice = {100, 200, 300, 400};
    std::vector<double> range = {70.0, 130.0, 180.0, 230.0, 270.0};
    std::vector<double> rangePrice = {100, 200, 300, 400};

    sf::Clock attackClock{};

    

    sf::Texture texture;

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
    void attack(std::vector<shptr<Projectile>> & projectiles) override;
    int getPrice() override;
};

class AnvilTower : public Tower
{
public:
    AnvilTower(int x, int y);
    AnvilTower(double x, double y);
    AnvilTower(shptr<Tile> tile);
    void attack(std::vector<shptr<Projectile>> & projectiles) override;
    int getPrice() override;
};

class MinigunTower : public Tower
{
public:
    MinigunTower(int x, int y);
    MinigunTower(double x, double y);
    MinigunTower(shptr<Tile> tile);
    void attack(std::vector<shptr<Projectile>> & projectiles) override;
    int getPrice() override;
};


#endif