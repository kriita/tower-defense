#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Tile.h"
#include "defs.h"

/* 
 * Monster
*/

class Monster
{
public:
    Monster(shptr<Tile> tile);     //provide spawnpoint
    Monster(Monster const&) = delete;
    Monster(int x, int y);
    Monster(double x, double y);
    virtual ~Monster() = default;
    void render(sf::RenderTarget &target);
    void update();
    virtual void takeDamage(double damage);
    void walk();    
    double getX() const;
    double getY() const;
    void setDir();                 // -1/1 positiv riktning till höger och nedåt
    virtual double getHealth() = 0;
    void despawn();                 // Removes monster
    virtual void loseHP();        // Decreases game HP
    virtual void defeat() {};          // Returns bounty
    bool onCheckpoint() const;
    void setNextTile();
    bool isDead() {return dead;};
    void kill() {dead = true;};

    Monster& operator=(Monster const& other);

protected:
    double health{50};
    double speed{3};
    double armour{1};
    shptr<Tile> nextTile {};
    int xDir{0};
    int yDir{1};
    double y{};                     // Position in pixels
    double x{};
    double timeStamp{};
    bool dead{false};
};

class Orc : public Monster
{
public:
    Orc(shptr<Tile>);          //provide spawnpoint
    Orc(Orc const&) = default;
    Orc(int x, int y);
    Orc(double x, double y);
    std::string getType() const;
    void loseHP() override;
    void defeat() override;
    double getHealth() override {return health;};
private:
    std::string monsterType {"Orc"};
    double health{100};
    double armour{1};
    int bounty{420};
    int HPLoss{1};
};




#endif
