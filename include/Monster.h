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
    void takeDamage(double const& damage);
    void takePureDmg(double const& damage);    
    void takeSlowDmg(double const& damage, double const& slow, double const& duration, bool pureDmg);
    void takeCritDamge(double const& damage, unsigned const& critChance, bool pureDmg);
    void helpDamage(double const& dmg, bool pureDmg);
    void takePushBackDmg(double const& damage, int const& duration, bool pureDmg);
    void walk();  
    void render(sf::RenderTarget &target);
    double getHealth() const {return health;};
    double getSpeed() const {return speed;};
    int getXDir() const {return xDir;};
    int getYDIr() const {return yDir;};
    double getX() const {return x;};
    double getY() const {return y;};
    double getBounty() const {return bounty;};
    double getHPLoss() const {return HPLoss;};
    void setDir();                 // -1/1 positiv riktning till höger och nedåt
    bool onCheckpoint() const;
    void setNextTile();
    bool isDead() const {return dead;};
    unsigned slowTime {};
    sf::FloatRect getBounds();
    double getRadius() const {return radius;};
    bool shallLoseHP() const {return loseHP;};
    std::string getType() const {return monsterType;};
    void setLevel(unsigned const& lvl) {level = lvl;};
    bool isBleeding() {return bleeding;};
protected:
    shptr<Tile> nextTile{};
    sf::Sprite monsterSprite{};
    Spritesheet monsterSheet{"resources/images/monsters.png", 32, 32};
    sf::Texture frozenTexture{};
    sf::Sprite frozenSprite {};
    std::string monsterType{};
    unsigned level{};
    int xDir{};
    int yDir{};
    double y{};                     // Position in pixels
    double x{};
    double stunDuration{};
    bool dead{false};
    double health{};
    double armour{};
    double refSpeed{};
    double slow{};          // current slowEffect
    double speed{};
    int HPLoss{1};
    double bounty{1};
    unsigned xOffset {};
    bool firstStep {true};
    unsigned yOffset {};
    unsigned extraXOffset{};
    unsigned extraYOffset{};
    sf::Clock animClock {};         // Clock for animation
    sf::Clock slowClock {};             // Time for sloweffect
    sf::Clock stunClock {};
    sf::Clock bleedingClock {};
    bool loseHP{false};             // Decrase HP with lifeLoss when true
    bool bleeding{false};
};

class BrownRabbit : public Monster      // Tanky unit
{
public:
    BrownRabbit(shptr<Tile>, unsigned level);          //provide spawnpoint and level
private:
    double healths [10] = {50, 100, 250, 500, 750, 1000, 1500, 2000, 3000, 5000};
    double armours [10] = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 6};
    double speeds [10]  = {1, 1, 1.5, 1.5, 2, 2, 2, 2, 2, 2};
    double bountys [10] = {20, 50, 100, 250, 500, 750, 1000, 2000, 3000, 5000};
};

class Squirrel : public Monster         // Fast unit
{
public:
    Squirrel(shptr<Tile>, unsigned level);          //provide spawnpoint and level
private:
    double healths [10] = {20, 50, 75, 100, 200, 250, 400, 500, 750, 1000};
    double armours [10] = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 6};
    double speeds [10]  = {1, 1, 1.5, 1.5, 2, 2, 2, 2, 2, 2};
    double bountys [10] = {20, 50, 100, 250, 500, 750, 1000, 2000, 3000, 5000};
};

class Fox : public Monster
{
public:
    Fox(shptr<Tile>, unsigned level);          //provide spawnpoint and level
private:
    double healths [10] = {50, 100, 250, 500, 750, 1000, 1500, 2000, 3000, 5000};
    double armours [10] = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 6};
    double speeds [10]  = {1, 1, 1.5, 1.5, 2, 2, 2, 2, 2, 2};
    double bountys [10] = {20, 50, 100, 250, 500, 750, 1000, 2000, 3000, 5000};
};

class WhiteRabbit : public Monster              // Boss
{
public:
    WhiteRabbit(shptr<Tile>, unsigned level);          //provide spawnpoint and level
private:
    double healths [10] = {500, 1000, 3000, 5000, 10000, 25000, 50000, 100000, 500000, 1000000};
    double armours [10] = {20, 50, 100, 250, 500, 750, 1000, 2000, 3000, 5000};
    double speeds [10] = {1, 1, 1, 1, 1, 0.5, 0.5, 0.5, 0.5, 0.5};
    double bountys [10] = {200, 500, 1000, 2500, 5000, 7500, 10000, 20000, 30000, 50000};
};

class Hamster : public Monster
{
public:
    Hamster(shptr<Tile>, unsigned level);          //provide spawnpoint and level
private:
    double healths [10] = {50, 100, 250, 500, 750, 1000, 1500, 2000, 3000, 5000};
    double armours [10] = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 6};
    double speeds [10]  = {1, 1, 1.5, 1.5, 2, 2, 2, 2, 2, 2};
    double bountys [10] = {20, 50, 100, 250, 500, 750, 1000, 2000, 3000, 5000};
};

class GrayRacoon : public Monster
{
public:
    GrayRacoon(shptr<Tile>, unsigned level);          //provide spawnpoint and level
private:
    double healths [10] = {50, 100, 250, 500, 750, 1000, 1500, 2000, 3000, 5000};
    double armours [10] = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 6};
    double speeds [10]  = {1, 1, 1.5, 1.5, 2, 2, 2, 2, 2, 2};
    double bountys [10] = {20, 50, 100, 250, 500, 750, 1000, 2000, 3000, 5000};
};

class Hedgehog : public Monster
{
public:
    Hedgehog(shptr<Tile>, unsigned level);          //provide spawnpoint and level
private:
    double healths [10] = {50, 100, 250, 500, 750, 1000, 1500, 2000, 3000, 5000};
    double armours [10] = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 6};
    double speeds [10]  = {1, 1, 1.5, 1.5, 2, 2, 2, 2, 2, 2};
    double bountys [10] = {20, 50, 100, 250, 500, 750, 1000, 2000, 3000, 5000};
};

class BrownRacoon : public Monster
{
public:
    BrownRacoon(shptr<Tile>, unsigned level);        //provide spawnpoint and level
private:
    double healths [10] = {50, 100, 250, 500, 750, 1000, 1500, 2000, 3000, 5000};
    double armours [10] = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 6};
    double speeds [10]  = {1, 1, 1.5, 1.5, 2, 2, 2, 2, 2, 2};
    double bountys [10] = {20, 50, 100, 250, 500, 750, 1000, 2000, 3000, 5000};
};

#endif
