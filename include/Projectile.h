#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "defs.h"
#include "Monster.h"
#include "Spritesheet.h"
#include <vector>

// Note: Not using reference to vector with all monsters! But it works anyway...
// ...because of pointers? Hmmm... Yeah that makes sense! :)

/* The purpose of a Projectile is to be ceated by a Tower and damage a Monster
 * if the Monster is hit, thus Projectile needs knowledge of the class Monster
 * but not of Tower.
 */

class ProjectileError : public std::logic_error
{
    using std::logic_error::logic_error;
};

class Projectile
{
    public:
    Projectile() = default;
    Projectile(double x, double y, double xDir, double yDir);
    Projectile(double x, double y, double dirByRadians);    // OBS! positive radians clockwise
    virtual ~Projectile() = default;
    virtual void targetHit();   // Checks if the target has been hit, deals damgae if true
    virtual void explodeAnim() {}; // renders the explode animation
    virtual void move();
    virtual void update(std::vector<shptr<Monster>> &allMonsters);
    virtual void dealDamage (shptr<Monster> &aMonster);
    virtual void removeProjectile();
    bool isOutsideMap();
    shptr<Monster> getTarget(); // Returns nullptr (false) if Projectile has no target
    void setTarget(shptr<Monster> newTarget);
    double getX(); // Coordinates in pixels
    double getY();
    void setx(double new_x);
    void sety(double new_y);
    double getxDir();
    double getyDir();
    double getDirByRadians();
    void setxDir(double new_xDir);
    void setyDir(double new_yDir);
    void setDirByRadians(double angle);
    double getSpeed();
    void setSpeed(double newSpeed);
    void render(sf::RenderTarget &window);
    sf::FloatRect getBounds();
    bool checkHit (shptr<Monster> &aMonster);
    double getRadius();


    protected:
    double damage {};
    shptr<Monster> target {};
    double x {}; // Coordinates in pixels
    double y {};
    double speed {};
    double xDir {};
    double yDir {};
    //Spritesheet projectileSpritesheet {};
    sf::Sprite projectileSprite {};
    sf::Texture projectileTexture {};
    double radius {}; // radius in pixels
    virtual void setAngle();
    double angle {};

};


class Anvil : public Projectile
{
    public:
    Anvil();
    Anvil(double x, double y, double xDir, double yDir);
    Anvil(double x, double y, double xDir, double yDir, shptr<Monster> &target);
};

// minigunProjectile is a non-guided projectile
class minigunProjectile : public Projectile
{
    public:
    minigunProjectile(double x, double y, double xDir, double yDir);
    minigunProjectile(double x, double y, double dirByRadians);
};

class MissileProjectile : public Projectile
{
    public:
    MissileProjectile(double x, double y, double dirByRadians, shptr<Monster> Monstertarget); // Sätt vinkel
    MissileProjectile(double x, double y, double xDir, double yDir); // Sätt vinkel
    MissileProjectile(double x, double y, double dirByRadians);
    Spritesheet missileSheet {"resources/images/MissileProjectileSheet.png", 32, 32};
    void dealDamage(shptr<Monster> &aMonster) override;
    void update(std::vector<shptr<Monster>> &allMonsters) override;


    private:
    int currSprite {0}; // Where in the spriteSheet should we read

};
#endif