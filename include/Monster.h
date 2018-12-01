#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Tile.h"
#include "defs.h"
#include "complex"
#include "cmath"
#include "Spritesheet.h"

/* 
 * Monster
*/

class Monster
{
public:
    Monster(shptr<Tile> tile);     //provide spawnpoint
    Monster(Monster const&) = delete;
    Monster(int x, int y);
    Monster(Spritesheet & sheet, double x, double y);
    virtual ~Monster() = default;
    void render(sf::RenderTarget &target);
    void update();
    virtual void takeDamage(double damage);
    virtual void takePureDmg(double damage);
    void virtual takeSlowDmg(double damage, double slow, double duration, bool pureDmg);
    virtual void walk();  
    double getX() const {return x;};
    double getY() const {return y;};
    void setDir();                 // -1/1 positiv riktning till höger och nedåt
    virtual std::complex<double> getHealth() {return health;};
    void despawn();                 // Removes monster
    virtual void loseHP() {};        // Decreases game HP
    virtual void defeat() {};          // Returns bounty
    bool onCheckpoint() const;
    void setNextTile();
    bool isDead() {return dead;};
    Monster& operator=(Monster const& other) = delete;

protected:
    shptr<Tile> nextTile {};
    sf::Sprite monsterSprite {};
    int xDir{};
    int yDir{};
    double y{};                     // Position in pixels
    double x{};
    double slowClock{0};             // Time for sloweffect
    bool dead{false};
    std::complex<double> health{};
    double armour{};
    double refSpeed{};
    double speed{};
    int HPLoss{1};
    double bounty{};
};

class Orc : public Monster
{
public:
    Orc(shptr<Tile>);          //provide spawnpoint
    Orc(Orc const&) = default;
    Orc(int x, int y);
    Orc(Spritesheet & sheet, double x, double y);
    std::string getType() const {return monsterType;};
    void loseHP() override;
    void defeat() override;
private:
    std::string monsterType {"Orc"};
};

/*
class Flash : public Monster
{
public:
    Flash(shptr<Tile>);          //provide spawnpoint
    Flash(Flash const&) = default;
    Flash(int x, int y);
    Flash(double x, double y);
    std::string getType() const {return monsterType;};
    void loseHP() override;
    void defeat() override;
    double getHealth() override {return health;};
private:
    std::string monsterType {"Flash"};
};
*/

class Complexus : public Monster 
{
public:
    Complexus(shptr<Tile>);          //provide spawnpoint
    Complexus(Complexus const&) = default;
    Complexus(int x, int y);
    Complexus(double x, double y);
    std::string getType() const {return monsterType;};
    void loseHP() override;
    void defeat() override;
private:
    std::string monsterType {"Complexus"};
};

#endif
