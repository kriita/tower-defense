#ifndef TOWER_H
#define TOWER_H

/*
 *  Tower
*/
class Tower
{
public:
    Tower() = default;
    virtual ~Tower() = default;

    virtual void attack() = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual int getAngle() const = 0;

protected:
    int xPos {};
    int yPos {};
    int fireRate {};
    int attackPower {};
    int angle {};
};

/*
 *  Tower 1
*/
class Tower1 : public Tower
{
public:
    ~Tower1() = default;

    void attack();
    int getX() const;
    int getY() const;
    int getAngle() const;
};

#endif