#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Map.h"
#include "defs.h"
//#include "Monster.h"
#include "Spritesheet.h"

// Class Monster below is only used in testcases (until Monster.h is done)
/*
class Monster
{
    public:
    Monster() = default;
    int getX() {return 0;};
    int getY() {return 0;};
};
*/
class Monster;

class Projectile
{
    public:
    Projectile() = default;
    Projectile (int x, int y, int xDir, int yDir);
    virtual ~Projectile() = default;
    virtual void monsterHit() {};
    virtual void targetHit() {};
    virtual void explodeAnim() {}; // renders the explode animation
    void isOutsideMap();
    virtual void move();
    shptr<Monster> getTarget(); // Returns nullptr (false) if Projectile has no target
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

    protected:
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

/*
class Anvil : Projectile
{
    Anvil();
    Anvil(int x, int y, int xDir, int yDir);
    private:
    sf::Texture anvil_Texture {}
};
*/
#endif