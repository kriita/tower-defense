#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Map.h"
#include "defs.h"
#include "Monster.h"
#include "Spritesheet.h"
#include <vector>

// Note: Not using reference to vector with all monsters!

class ProjectileError : public std::logic_error
{
    using std::logic_error::logic_error;
};

class Projectile
{
    public:
    Projectile() = default;
    Projectile(double x, double y, double xDir, double yDir);
    Projectile(double x, double y, double dirByRadians);
    virtual ~Projectile() = default;
    virtual void monsterHit(std::vector<shptr<Monster>> allMonsters);
    virtual void targetHit();
    virtual void explodeAnim() {}; // renders the explode animation
    virtual void move();
    virtual void update(std::vector<shptr<Monster>> allMonsters);
    void isOutsideMap();
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
};


class Anvil : public Projectile
{
    public:
    Anvil();
    Anvil(double x, double y, double xDir, double yDir);
    Anvil(double x, double y, double xDir, double yDir, shptr<Monster> &target);
    void monsterHit(std::vector<shptr<Monster>> allMonsters) override;
};

// minigunProjectile is a non-guided projectile
class minigunProjectile : Projectile
{
    public:
    minigunProjectile(double x, double y, double xDir, double yDir);
    minigunProjectile(double x, double y, double dirByRadians);
};

#endif