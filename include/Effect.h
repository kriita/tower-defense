#ifndef EFFECT_H
#define EFFECT_H

#include "Spritesheet.h"
#include <SFML/Graphics.hpp>

/*
 *  Effect
 * 
 *  Creates a graphical effect at specified coordinates for [duration] seconds.
 *  There is also a value for fade out duration, [fadeDuration].
 *  These values, as well as starting alpha channel value (opacity) can be
 *  set in the sub class constructors.
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
    float x {};                     // Center x coordinate
    float y {};                     // Center y coordinate
    float duration {};              // Seconds
    float fadeDuration {0};         // Seconds
    unsigned startAlpha {255};      // 0-255
    bool remove {false};            // Flag for removal
    sf::Clock durationClock {};
    sf::Sprite effectSprite {};
    bool clockStart {false};        // Start counting after first update
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

/*
 *  Effect ->MissileExplosion 
 */
class MissileExplosion: public Effect
{
    public:
    MissileExplosion(float x, float y);
    void changeSprite();
    
    private:
    Spritesheet effectSheet {"resources/images/MissileExplosionSheet.png", 32, 32};
    int currSpriteCol {0}; // Current column used in effectSheet
};
#endif