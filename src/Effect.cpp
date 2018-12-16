#include "constants.h"
#include "Effect.h"
#include <cstdlib>

/*
 *  Effect
 */
Effect::Effect(float x, float y)
: x {x}, y {y}
{}

void Effect::render(sf::RenderTarget &target)
{
    effectSprite.setPosition(x, y);
    target.draw(effectSprite);
}

void Effect::update()
{
    if (!clockStart)
    {
        clockStart = true;
        durationClock.restart();
    }

    float elapsed {(durationClock.getElapsedTime()).asSeconds()};

    if (elapsed > duration)
    {
        remove = true;
    }
    else if (elapsed > duration - fadeDuration)
    {
        float fadeAlpha {((duration - elapsed) / fadeDuration) * startAlpha};
        effectSprite.setColor(sf::Color(255, 255, 255, static_cast<int>(fadeAlpha)));
    }
}

bool Effect::checkRemove() const
{
    return remove;
}

/*
 *  Effect -> Blood
 */
Blood::Blood(float x, float y)
: Effect {x, y}
{
    duration = 60;
    fadeDuration = 2;
    effectSprite = effectSheet.get_sprite(0, 0);
    effectSprite.setPosition(x, y);
    effectSprite.setOrigin(tileWidth/2, tileWidth/2);
    effectSprite.setColor(sf::Color(255, 255, 255, startAlpha));
    effectSprite.setRotation(rand() % 360);
}

/*
 *  Effect -> Bleed
 */
Bleed::Bleed(float x, float y)
: Effect {x, y}
{
    duration = 30;
    fadeDuration = 2;
    effectSprite = effectSheet.get_sprite(0, 0);
    effectSprite.setPosition(x, y);
    effectSprite.setOrigin(tileWidth/2, tileWidth/2);
    effectSprite.setColor(sf::Color(255, 255, 255, startAlpha));
    effectSprite.setRotation(rand() % 360);
}

/*
 *  Effect -> Slow
 */
Slow::Slow(float x, float y, float radius)
: Effect {x, y}
{
    duration = 1.5;
    fadeDuration = 1.5;
    startAlpha = 150;
    effectSprite = effectSheet.get_sprite(0, 0);
    effectSprite.setPosition(x, y);
    effectSprite.setOrigin(48, 48);
    effectSprite.setColor(sf::Color(255, 255, 255, startAlpha));
    effectSprite.setScale(2 * radius / 96, 2 * radius / 96);
}

/*
 *   Effect -> MissileExplosion
 */
MissileExplosion::MissileExplosion(float x, float y)
: Effect {x, y}
{
    duration = 0.5;
    effectSprite = effectSheet.get_sprite(0,0);
    effectSprite.setOrigin(tileWidth/2, tileWidth/2);
    effectSprite.setRotation(rand() % 360);
}

void MissileExplosion::changeSprite()
{
    float elapsed {(durationClock.getElapsedTime()).asSeconds()};

    if (elapsed > duration)
    {
        return void();
    }
    else
    {
        if (elapsed > ((1 + currSpriteCol) * duration / 3))
        {
            currSpriteCol += 1;
            effectSprite = effectSheet.get_sprite(0, currSpriteCol);
            effectSprite.setOrigin(tileWidth/2, tileWidth/2);
        }
    }
}