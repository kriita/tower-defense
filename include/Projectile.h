#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Map.h"
//#include "Monster.h"
#include "Spritesheet.h"
#include "defs.h"

class Monster;

class Projectile
{
    public:
    Projectile() = default;
    virtual ~Projectile() = default;
    virtual void monsterHit();
    virtual void explodeAnim(); // renders the explode animation
    void isOutsideMap();
    virtual void move();
    //template<class T>
    bool getTarget(); // Returns false if Projectile has no target
    void setTarget(shptr<Monster> newTarget);
    int getX(); // Coordinates in pixels
    int getY();
    void setx(int new_x);
    void sety(int new_y);
    int getxDir();
    int getyDir();
    void setxDir(int new_xDir);
    void setyDir(int new_yDir);
    double getSpeed();
    void setSpeed(int newSpeed);
    void renderMe();


    private:
    int dmg {};
    shptr<Monster> target {};
    int x {}; // Coordinates in pixels
    int y {};
    int speed {};
    int xDir {};
    int yDir {};
    //Spritesheet projectileSpritesheet {};
    sf::Sprite projectileSprite {};
};

#endif