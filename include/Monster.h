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
    virtual ~Monster() = default;
    void update(); 
    void render(sf::RenderTarget &target);   
    void takeDamage(double const& damage);
    // slow between 0 and 1. new speed = slow * speed    
    void takeSlowDmg(double const& damage, double const& slow, 
                     double const& duration, bool pureDmg);
    void takeCritDamage(double const& damage, unsigned const& critChance,
                        bool pureDmg);
    void takeStunDmg(double const& damage, int const& duration, 
                     double const& percentage, bool pureDmg);
    void setLevel(unsigned const& lvl);
    int getXDir() const {return xDir;};
    int getYDIr() const {return yDir;};
    double getHealth() const {return health;};
    double getSpeed() const {return speed;};
    double getX() const {return x;};
    double getY() const {return y;};
    double getBounty() const {return bounty;};
    double getHPLoss() const {return HPLoss;};
    float getRadius() const {return radius;};
    bool shallLoseHP() const {return loseHP;};
    bool onCheckpoint() const;
    bool isDead() const {return dead;};
    bool isBleeding() {return bleeding;};
    sf::FloatRect getBounds();
    std::string getType() const {return monsterType;};
protected:
    virtual void walk(); 
    void helpDamage(double const& dmg, bool pureDmg);   // these are helpfunktions
    void takePureDmg(double const& damage);             // for other takeDamage functions
    void setSprite();
    void setDir();                 // -1/1 positiv riktning till höger och nedåt
    void setNextTile();
    shptr<Tile> nextTile{};
    sf::Sprite monsterSprite{};
    sf::Sprite frozenSprite {};
    Spritesheet monsterSheet{"resources/images/monsters.png", 32, 32};
    Spritesheet frozenSheet{"resources/images/frozenMonsters.png", 32, 32};
    std::string monsterType{};
    float radius{};
    double y{};                     // Position in pixels
    double x{};
    double stunDuration{};
    double refSpeed{};              // Uneffected monster speed
    double slow{};                  // current slowEffectSpeed
    std::vector<double> healths {};
    std::vector<double> armours {};
    std::vector<double> speeds {};
    std::vector<double> bountys {};
    double health{};
    double armour{};
    double speed{};
    double bounty{};
    int HPLoss{1};                  // how much HP player losses when monster reaches goal
    int xDir{};                     // direction -1/1 pos right
    int yDir{};                     // direction -1/1 pos down
    unsigned level{};
    unsigned xOffset {};            // offset for animation
    unsigned yOffset {};
    unsigned extraXOffset{};        // offset to select monster
    unsigned extraYOffset{};
    unsigned slowTime {};
    sf::Clock animClock {};         // Clock for animation
    sf::Clock slowClock {};         // Clock for sloweffect
    sf::Clock stunClock {};         // Clock for stuneffect
    sf::Clock bleedingClock {};     // Clock for bleedrendering
    bool stunned {false};
    bool slowed {false};    
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

class WhiteRabbit : public Monster              // a Boss can regenerate
{
public:
    WhiteRabbit(shptr<Tile>, unsigned level);          //provide spawnpoint and level
private:
    void walk() override;  
    void regenerate();
    double regeneration [10];
    sf::Clock regenerateClock {};    
};

class Hamster : public Monster
{
public:
    Hamster(shptr<Tile>, unsigned level);          //provide spawnpoint and level
};

class GrayRaccoon : public Monster
{
public:
    GrayRaccoon(shptr<Tile>, unsigned level);          //provide spawnpoint and level

};

class Hedgehog : public Monster
{
public:
    Hedgehog(shptr<Tile>, unsigned level);          //provide spawnpoint and level
};

class BrownRaccoon : public Monster
{
public:
    BrownRaccoon(shptr<Tile>, unsigned level);        //provide spawnpoint and level
};

#endif
