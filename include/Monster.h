#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Tile.h"
#include "defs.h"
#include "Spritesheet.h"

/* 
 * Monster
*/

class Monster
{
protected:
    double radius{};
public:
    Monster(shptr<Tile> tile);     //provide spawnpoint and level
    Monster(Monster const&) = default;
    Monster& operator=(Monster const& other) = default;
    virtual void setSprite();
    virtual ~Monster() = default;
    virtual void update();    
    void takeDamage(double damage);
    void takePureDmg(double damage);    
    void takeSlowDmg(double damage, double slow, double duration, bool pureDmg);
    void takeCritDamge(double damage, unsigned critChance, bool pureDmg);
    void helpDamage(double dmg, bool pureDmg);
    void takePushBackDmg(double damage, int pushBack, bool pureDmg);
    void walk();  
    double getHealth() {return health;};
    void render(sf::RenderTarget &target);
    double getSpeed() {return speed;};
    int getXDir() {return xDir;};
    int getYDIr() {return yDir;};
    double getX() const {return x;};
    double getY() const {return y;};
    double getBounty() {return bounty;};
    double getHPLoss() {return HPLoss;};
    void setDir();                 // -1/1 positiv riktning till höger och nedåt
    bool onCheckpoint() const;
    void setNextTile();
    bool isDead() {return dead;};
    unsigned slowTime {};
    sf::FloatRect getBounds();
    double getRadius() {return radius;};
    bool shallLoseHP() {return loseHP;};
    std::string getType() const {return monsterType;};
protected:
    shptr<Tile> nextTile {};
    shptr<Tile> prevTile {};
    sf::Sprite monsterSprite {};
    Spritesheet monsterSheet {"resources/images/monsters.png", 32, 32};
    std::string monsterType {"Kevin"};

    int xDir{};
    int yDir{};
    double y{};                     // Position in pixels
    double x{};
    sf::Clock slowClock {};             // Time for sloweffect
    bool dead{false};
    double health{};
    double armour{};
    double refSpeed{};
    double speed{};
    int HPLoss{1};
    double bounty{1};
    unsigned xOffset {};
    bool firstStep {true};
    unsigned yOffset {};
    unsigned extraXOffset{};
    unsigned extraYOffset{};
    sf::Clock animClock {};         // Clock for animation
    bool loseHP{false};             // Decrase HP with lifeLoss when true
};

class Orc : public Monster
{
public:
    Orc(shptr<Tile>, unsigned level);          //provide spawnpoint and level
private:
    unsigned level{};
    std::vector<double> healths {50, 120, 250, 500, 1000};
    std::vector<double> armours {1, 3, 5, 10, 20};
    std::vector<double> speeds {1, 1, 2, 2.5, 2.5};
    std::vector<double> bountys {20, 50, 100, 250, 500};
};

class Flash : public Monster
{
public:
    Flash(shptr<Tile>, unsigned level);          //provide spawnpoint and level
private:
    std::string monsterType {"Flash"};
    unsigned level{};
    std::vector<double> healths {50, 100, 250, 500, 1000};
    std::vector<double> armours {1, 3, 5, 10, 20};
    std::vector<double> speeds {1, 1.5, 2, 2.5, 2.5};
    std::vector<double> bountys {20, 50, 100, 250, 500};
};

class Tank : public Monster
{
public:
    Tank(shptr<Tile>, unsigned level);          //provide spawnpoint and level
private:
    unsigned level{};
    std::vector<double> healths {50, 100, 250, 500, 1000};
    std::vector<double> armours {10, 30, 50, 100, 250};
    std::vector<double> speeds {1, 2, 2, 2.5, 2.5};
    std::vector<double> bountys {20, 50, 100, 250, 500};
};

class Derp : public Monster
{
public:
    Derp(shptr<Tile>, unsigned level);          //provide spawnpoint and level
private:
    unsigned level{};
    std::vector<double> healths {50, 100, 250, 500, 1000};
    std::vector<double> armours {10, 30, 50, 100, 250};
    std::vector<double> speeds {1, 3, 2, 2.5, 2.5};
    std::vector<double> bountys {20, 50, 100, 250, 500};
};


#endif
