#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "defs.h"
#include "Monster.h"
#include "Spritesheet.h"
#include "Effect.h"
#include <vector>

/* The purpose of a Projectile is to be ceated by a Tower and damage a Monster
 * if the Monster is hit, thus Projectile needs knowledge of the class Monster
 * but not of Tower. Some Projectiles have an Effect when exploading.
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
    virtual void targetHit() const;   // Checks if the target has been hit, deals damage if true
    virtual void explodeAnim() const {}; // renders the explode animation
    virtual void move();
    virtual void update(std::vector<shptr<Monster>> &allMonsters);
    virtual void dealDamage (shptr<Monster> &aMonster) const;
    virtual void removeProjectile();
    shptr<Monster> getTarget() const; // Returns nullptr (false) if Projectile has no target
    void setTarget(shptr<Monster> const &newTarget);
    double getX() const; // Coordinates in pixels
    double getY() const;
    void setx(double const new_x);
    void sety(double const new_y);
    double getxDir() const;
    double getyDir() const;
    double getDirByRadians() const;
    void setxDir(double const new_xDir);
    void setyDir(double const new_yDir);
    void setDirByRadians(double const newAngle);
    double getSpeed() const;
    void setSpeed(double const newSpeed);
    virtual void render(sf::RenderTarget &window) const;
    sf::FloatRect getBounds() const;
    virtual bool checkHit (shptr<Monster> const &aMonster) const;
    double getRadius() const;


    protected:
    shptr<Monster> target {};
    double x {}; // Coordinates in pixels
    double y {};
    double speed {};
    double xDir {};
    double yDir {};    
    double damage {};

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
    void dealDamage(shptr<Monster> &aMonster) const override;
};

// MissileProjectile is a guided projectile
class MissileProjectile : public Projectile
{
    public:
    MissileProjectile(double x, double y, double dirByRadians, double attackPower, shptr<Monster> Monstertarget); // Sätt vinkel
    MissileProjectile(double x, double y, double xDir, double yDir, double attackPower);
    MissileProjectile(double x, double y, double dirByRadians, double attackPower);
    void dealDamage(shptr<Monster> &aMonster) const override;
    void update(std::vector<shptr<Monster>> &allMonsters) override;
    void explodeAnim() const override;
    void render(sf::RenderTarget &window) const;

    private:
    shptr<MissileExplosion> explodeEffect {}; 
};

class LaserProjectile : public Projectile
{
    public:
    LaserProjectile(double x, double y, double dirByRadians, double attackPower, shptr<Monster> Monstertarget, double duration); // Sätt vinkel
    void update(std::vector<shptr<Monster>> &allMonsters) override;
    protected:
    void laserDamage(std::vector<shptr<Monster>> &allMonsters) const;
    double duration{};
    bool checkHit(shptr<Monster> const &aMonster) const override;
    sf::Clock laserClock{};
    void render(sf::RenderTarget &window) const;
    double transparency{0};
    int transparencyState{0};  
 };



#endif