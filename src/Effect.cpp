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
    float elapsed {(durationClock.getElapsedTime()).asSeconds()};

    if (elapsed > duration)
    {
        remove = true;
    }
    else if (elapsed > duration - fadeDuration)
    {
        float fadeAlpha {((duration - elapsed) / fadeDuration) * 255};
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
    effectSprite.setRotation(rand() % 360);
}