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
    if ((durationClock.getElapsedTime()).asSeconds() > duration)
    {
        remove = true;
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
    effectSprite = effectSheet.get_sprite(0, 0);
    effectSprite.setPosition(x, y);
    effectSprite.setOrigin(tileWidth/2, tileWidth/2);
    effectSprite.setRotation(rand() % 360);
}