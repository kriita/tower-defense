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
    float duration {};          // Seconds
    float fadeDuration {0};     // Seconds
    int startAlpha {255};
    bool remove {false};        // Flag for removal
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

/*
 *  Effect -> Slow
 */
class Slow : public Effect
{
public:
    Slow(float x, float y, float radius);

private:
    Spritesheet effectSheet {"resources/images/slowAOE.png", 96, 96};
};

class MissileExplosion: public Effect
{
    public:
    MissileExplosion(float x, float y);
    void changeSprite();
    
    private:
    Spritesheet effectSheet {"resources/images/MissileExplosionSheet", 32, 32};
    int currSpriteCol {0}; // Current column used in effectSheet
};
#endif