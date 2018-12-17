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
    float getRadius() const {return radius;};
    bool shallLoseHP() const {return loseHP;};
    std::string getType() const {return monsterType;};
    void setLevel(unsigned const& lvl);
    bool isBleeding() {return bleeding;};
protected:
    shptr<Tile> nextTile{};
    sf::Sprite monsterSprite{};
    Spritesheet monsterSheet{"resources/images/monsters.png", 32, 32};
    sf::Sprite frozenSprite {};
    Spritesheet frozenSheet{"resources/images/frozenMonsters.png", 32, 32};
    std::string monsterType{};
    float radius{};
    double y{};                     // Position in pixels
    double x{};
    double stunDuration{};
    double refSpeed{};
    double slow{};          // current slowEffect
    double healths [10] {};
    double armours [10] {};
    double speeds [10] {};
    double bountys [10] {};
    double health{};
    double armour{};
    double speed{};
    double bounty{};
    int HPLoss{1};
    int xDir{};
    int yDir{};
    unsigned level{};
    unsigned xOffset {};
    unsigned yOffset {};
    unsigned extraXOffset{};
    unsigned extraYOffset{};
    sf::Clock animClock {};         // Clock for animation
    sf::Clock slowClock {};             // Time for sloweffect
    sf::Clock stunClock {};
    sf::Clock bleedingClock {};
    bool dead{false};
    bool firstStep {true};
    bool loseHP{false};             // Decrase HP with lifeLoss when true
    bool bleeding{false};
};

class BrownRabbit : public Monster      // Tanky unit
{
public:
    BrownRabbit(shptr<Tile>, unsigned level);          //provide spawnpoint and level
};

class Squirrel : public Monster         // Fast unit
{
public:
    Squirrel(shptr<Tile>, unsigned level);          //provide spawnpoint and level
};

class Fox : public Monster
{
public:
    Fox(shptr<Tile>, unsigned level);          //provide spawnpoint and level
};

class WhiteRabbit : public Monster              // Boss
{
public:
    WhiteRabbit(shptr<Tile>, unsigned level);          //provide spawnpoint and level
private:

};

class Hamster : public Monster
{
public:
    Hamster(shptr<Tile>, unsigned level);          //provide spawnpoint and level
};

class GrayRacoon : public Monster
{
public:
    GrayRacoon(shptr<Tile>, unsigned level);          //provide spawnpoint and level
private:

};

class Hedgehog : public Monster
{
public:
    Hedgehog(shptr<Tile>, unsigned level);          //provide spawnpoint and level
};

class BrownRacoon : public Monster
{
public:
    BrownRacoon(shptr<Tile>, unsigned level);        //provide spawnpoint and level
};

#endif
