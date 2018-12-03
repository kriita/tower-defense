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
    Monster(shptr<Tile> tile, int level);     //provide spawnpoint and level
    Monster(Monster const&) = delete;
    Monster(int x, int y);
    Monster(double x, double y);    
    Monster& operator=(Monster const& other) = delete;
    virtual void setSprite(sf::Sprite sprite) = 0;
    virtual ~Monster() = default;    
    virtual void takeDamage(double damage);
    virtual void takePureDmg(double damage);    
    virtual void takeSlowDmg(double damage, double slow, double duration, bool pureDmg);
    virtual void walk();  
    virtual std::complex<double> getHealth() {return health;};
    virtual void loseHP() {};        // Decreases game HP
    virtual void defeat() {};          // Returns bounty
    void render(sf::RenderTarget &target);
    virtual void update() = 0;
    double getX() const {return x;};
    double getY() const {return y;};
    void setDir();                 // -1/1 positiv riktning till höger och nedåt
    bool onCheckpoint() const;
    void setNextTile();
    bool isDead() {return dead;};

    sf::FloatRect getBounds();

protected:
    shptr<Tile> nextTile {};
    sf::Sprite monsterSprite {};
    sf::Texture monsterTexture {};

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
    unsigned xOffset {};
    unsigned yOffset {};
};

class Orc : public Monster
{
public:
    Orc(shptr<Tile>, int level);          //provide spawnpoint and level
    Orc(Orc const&) = default;
    Orc(int x, int y);
    Orc(double x, double y);
    std::string getType() const {return monsterType;};
    void setSprite(sf::Sprite sprite) override;
    void loseHP() override;
    void defeat() override;
    void update() override;
    void Orc::setTileSprite(sf::Sprite sprite)
//    void render(sf::RenderTarget &target) override;
private:
    std::string monsterType {"Orc"};
    int level{};  
    std::vector<std::complex<double>> healths {50, 100, 250, 500, 1000};
    std::vector<double> armours {1, 3, 5, 10, 20};
    std::vector<double> speeds {1, 1.5, 2, 2.5, 2.5};
    std::vector<double> bountys {20, 50, 100, 250, 500};
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
