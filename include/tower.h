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
    virtual int getFireRate() const = 0;
    virtual int getAttackPower() const = 0;

protected:
    int xPos {};
    int yPos {};
    int angle {};
    int fireRate {};
    int attackPower {};
};

/*
 *  Tower 1
 */
class Tower1 : public Tower
{
public:
    ~Tower1() = default;

    void attack();
    int getX() const override;
    int getY() const override;
    int getAngle() const override;
    int getFireRate() const override;
    int getAttackPower() const override;
};

#endif