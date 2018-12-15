#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "defs.h"
#include "Monster.h"
#include "Spritesheet.h"
#include "Effect.h"
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
    Projectile(double x, double y, double xDir, double yDir, double attackPower);
    Projectile(double x, double y, double dirByRadians, double attackPower);    // OBS! positive radians clockwise
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
    void setDirByRadians(double newAngle);
    double getSpeed();
    void setSpeed(double newSpeed);
    virtual void render(sf::RenderTarget &window);
    sf::FloatRect getBounds();
    virtual bool checkHit (shptr<Monster> &aMonster);
    double getRadius();


    protected:
    shptr<Monster> target {};
    double x {}; // Coordinates in pixels
    double y {};
    double speed {};
    double xDir {};
    double yDir {};    
    double damage {};

    //Spritesheet projectileSpritesheet {};
    sf::Sprite projectileSprite {};
    sf::Texture projectileTexture {};
    double radius {}; // radius in pixels
    void setAngle();
    
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
    minigunProjectile(double x, double y, double xDir, double yDir, double attackPower);
    minigunProjectile(double x, double y, double dirByRadians, double attackPower);
};

class MissileProjectile : public Projectile
{
    public:
    MissileProjectile(double x, double y, double dirByRadians, double attackPower, shptr<Monster> Monstertarget); // Sätt vinkel
    MissileProjectile(double x, double y, double xDir, double yDir, double attackPower); // Sätt vinkel
    MissileProjectile(double x, double y, double dirByRadians, double attackPower);
    //Spritesheet missileSheet {"resources/images/MissileProjectileSheet.png", 32, 32};
    void dealDamage(shptr<Monster> &aMonster) override;
    void update(std::vector<shptr<Monster>> &allMonsters) override;
    void explodeAnim() override;


    private:
    int currSprite {0}; // Where in the spriteSheet should we read
    shptr<MissileExplosion> ExplodeEffect {}; 

};

class LaserProjectile : public Projectile
{
    public:
    LaserProjectile(double x, double y, double dirByRadians, double attackPower, shptr<Monster> Monstertarget, double duration); // Sätt vinkel
    void update(std::vector<shptr<Monster>> &allMonsters) override;
    protected:
    void laserDamage(std::vector<shptr<Monster>> &allMonsters);
    double duration{};
    bool checkHit(shptr<Monster> &aMonster) override;
    sf::Clock laserClock{};
    void render(sf::RenderTarget &window);
    double transparency{0};
    int transparencyState{0};  
 };



#endif