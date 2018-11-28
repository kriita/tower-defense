#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>
#include <memory>
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
    virtual void takeDamage(double damage) = 0;
    void walk();    
    double getX() const;
    double getY() const;
    void setDir();                 // -1/1 positiv riktning till höger och nedåt

    void despawn();                 // Removes monster
    virtual void loseLife();        // Decreases game life
    virtual void defeat();          // Returns bounty
    bool onCheckpoint() const;
    void setNextTile();
    bool isDead() {return dead;};

    Monster& operator=(Monster const& other);

protected:
    double health{};
    double speed{3};

    shptr<Tile> nextTile {};
    int xDir{0};
    int yDir{1};
    double y{};                     // Position in pixels
    double x{};
    double timeStamp{};
    bool dead{false};
};

class Monster1 : public Monster
{
public:
    Monster1(shptr<Tile>);          //provide spawnpoint
    Monster1(Monster1 const&) = default;
    Monster1(int x, int y);
    Monster1(double x, double y);
    void takeDamage(double damage) override;
    std::string getType() const;
    void loseLife() override;
private:
    std::string monsterType {"Monster1"};
    double armour{0.5};
    int bounty{420};
    int lifeLoss{1};
};


#endif
