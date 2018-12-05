#ifndef EFFECT_H
#define EFFECT_H

#include "Spritesheet.h"
#include <SFML/Graphics.hpp>

/*
 *  Effect
 */
class Effect
{
public:
    Effect(float x, float y);
    virtual ~Effect() = default;

    void render(sf::RenderTarget &target);
    void update();
    bool checkRemove() const;

protected:
    float x {};
    float y {};
    float duration {};  // Seconds
    bool remove {false};    // Flag for removal
    sf::Clock durationClock {};
    sf::Sprite effectSprite {};
};

/*
 *  Effect -> Blood
 */
class Blood : public Effect
{
public:
    Blood(float x, float y);

private:
    Spritesheet effectSheet {"resources/images/blood.png", 32, 32};
};

/*
 *  Effect -> Bleed
 */
class Bleed : public Effect
{
public:
    Bleed(float x, float y);

private:
    Spritesheet effectSheet {"resources/images/bleed.png", 32, 32};
};

#endif