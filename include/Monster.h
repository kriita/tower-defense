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
    Monster() = default;
    Monster(Monster const&) = default;
    virtual ~Monster() = default;
    void render(sf::RenderTarget &target) {};
    virtual void takeDamage(double damage) = 0;
    void walk();    
    double getX() const;
    double getY() const;
    
    void despawn();                 // Removes monster
    virtual void loseLife();    // Decreases game life
    virtual void defeat();  // Returns bounty
    bool onCheckpoint() const;
    void setNextTile();
    Monster& operator=(Monster const& other);

protected:
    double health;
    double speed;

    shptr<Tile> nextTile {};
    int xDir;
    int yDir;
    double y {};         // Position in pixels
    double x {};
    double timeStamp;
};

class Monster1 : public Monster
{
public:
    Monster1();
    Monster1(double health, double speed);
    Monster1(Monster1 const&) = default;
    void takeDamage(double damage) override;
    std::string getType() const;
    void loseLife() override;
private:
    std::string monsterType {};
    double armour;
    int bounty;
    int lifeLoss;
};


#endif
