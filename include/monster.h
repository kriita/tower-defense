#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>
#include <memory>

/* 
 * Monster
*/

class Monster
{
public:
    Monster() = default;
    Monster(Monster const&) = default;
    virtual ~Monster() = default;
    virtual void render(sf::RenderTarget &target) = 0;
    virtual void takeDamage() = 0;
    virtual void walk() = 0;
    virtual void defeat() = 0;     // Returns bounty
    virtual double getX() const = 0;
    virtual double getY() const = 0;
    
    void despawn();
    bool onCheckpoint() const;
    shptr<Tile> getNextTile();
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
    void render(sf::RenderTarget &target) override;
    void takeDamage() override;
    void walk() override;
    void defeat() override;
    double getX() const override;
    double getY() const override;
    std::string getType() const;
private:
    std::string monsterType {};
};


#endif
