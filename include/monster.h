#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>

/* 
 * Monster
*/

class Monster
{
public:
    Monster();
    Monster(Monster const&) = default;
    virtual ~Monster() = default;
    virtual void takeDamage() = 0;
    virtual void walk() = 0;
    virtual double die() = 0;           // Returns bounty


    Tile* getNextTile();
    Monster& operator=(Monster const& other);

protected:
    double health;
    double speed;

    Tile* nextTile {};
    double distNextTile;
    bool onNextTile;
    char xdir;
    char ydir;
    int xPosTile {};            // Tilecoordinates
    int yPosTile {};
    double fineXpos {};         // Position in pixels
    double fineYpos {};
    double timeStamp;
};

class Monster1 : public Monster
{
public:
    Monster1();
    Monster1(Monster1 const&) = default;
    Monster1(double health,double speed);
    void takeDamage() override;
    void walk() override;
    double die() override;

};


#endif
