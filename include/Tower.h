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
    Tower(Tower const&) = default;

    virtual ~Tower() = default;

    virtual void render(sf::RenderTarget &target);
    virtual void update(std::vector<shptr<Monster>> & monstervector, 
                std::vector<shptr<Projectile>> & projectiles);

    virtual void attack(std::vector<shptr<Projectile>> & projectiles) = 0;
    virtual int getPrice() = 0;
    double getX() const;      
    double getY() const;       
    double getFireRate() const;
    double getAttackPower() const;
    double getRange() const;
    void setTarget(shptr<Monster> newTarget);
    bool inRange(shptr<Monster> monster);
    void upgradeRange();
    void upgradeAttackPower();
    void upgradeFireRate();
    int getRangeUpgradePrice();
    int getAttackPowerUpgradePrice();
    int getFireRateUpgradePrice();
    void setPosition(double x, double y);
    
 

protected:
    double xPos{};
    double yPos{};
    double angle{}; //radians
    shptr<Monster> target{};
    std::vector<double> fireRate = {1, 0.08, 0.06, 0.04, 0.02};   //Time in seconds between each attack.
    std::vector<double> fireRatePrice = {100, 200, 300, 400};
    std::vector<double> attackPower = {0, 1.5, 2.0, 2.5, 3.0};
    std::vector<double> attackPowerPrice = {100, 200, 300, 400};
    std::vector<double> range = {70.0, 130.0, 180.0, 230.0, 270.0};
    std::vector<double> rangePrice = {100, 200, 300, 400};
    virtual void setAngle();

    sf::Clock attackClock{};

    

    sf::Texture texture {};

    Spritesheet towerSpriteSheet {"resources/images/spritesheet.png", 32, 32}; 
    sf::Sprite towerSprite {};
};


class MinigunTower : public Tower
{
public:
    MinigunTower(int x, int y);
    MinigunTower(double x, double y);
    MinigunTower(shptr<Tile> tile);
    void attack(std::vector<shptr<Projectile>> & projectiles) override;
    int getPrice() override;
    void setAngle() override;
};

class MissileTower : public Tower
{
public:
    MissileTower(int x, int y);
    MissileTower(double x, double y);
    MissileTower(shptr<Tile> tile);
    void attack(std::vector<shptr<Projectile>> & projectiles) override;
    int getPrice() override;
};

class SlowTower : public Tower
{
public:
    SlowTower(int x, int y);
    SlowTower(double x, double y);
    SlowTower(shptr<Tile> tile);
    bool slowAttack(std::vector<shptr<Monster>> & monstervector);
    void attack(std::vector<shptr<Projectile>> & projectiles) override;
    void update(std::vector<shptr<Monster>> & monstervector, 
            std::vector<shptr<Projectile>> & projectiles) override;
    void render(sf::RenderTarget &target) override;
    int getPrice() override;
    void upgradeDuration(int & cash);
    void upgradeSlow(int & cash);
    std::vector<double> duration{1.0, 5.0, 7.0};
    std::vector<double> durationPrice{100, 1000};
    std::vector<double> slow{0.4, 0.4, 0.2};
    std::vector<double> slowPrice{100, 1000};
    ptr<Slow> slowEffect {};
};


class LaserTower : public Tower
{
public:
    LaserTower(double x, double y);
    LaserTower(shptr<Tile> tile);
    void update(std::vector<shptr<Monster>> & monstervector, 
                std::vector<shptr<Projectile>> & projectiles) override;
    void attack(std::vector<shptr<Projectile>> & projectiles) override;
    int getPrice() override;  
    sf::Sprite laserSprite{};
    sf::Texture laserTexture{};

private:
    shptr<Projectile> laserBeam{};
    double duration{1};
};

#endif