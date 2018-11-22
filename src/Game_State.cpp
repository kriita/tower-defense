#include "Game_State.h"
#include "Events.h"
#include "constants.h"
#include "tower.h"
#include <memory>

#include <iostream>

using namespace sf;

Game_State::Game_State()
{
    if(!gameOverlayTexture.loadFromFile("resources/images/overlay.png"))
    {
        //error
    }
    gameOverlay.setTexture(gameOverlayTexture);
}

/*
 * Check for mouse button presses.
 *
 * If a mouse button press is detected, when that
 * mouse button is release we add a new ball to
 * the screen at the mouse's location.
 *
 * This demonstrates how we can integrate the mouse
 * into our project.
 */
void Game_State :: handle_event (Event event)
{
    if ( event.type == Event::MouseButtonReleased )
    {
        auto mouse { event.mouseButton };
        if ( mouse.button == Mouse::Button::Left )
        {
            shptr<Tile> tmpTile {gameMap.getTile(static_cast<int>((mouse.x - mapBorderOffset) / tileWidth),
                                                 static_cast<int>((mouse.y - mapBorderOffset) / tileWidth))};
            if (tmpTile->checkPlaceable())
            {
                towers.push_back(make_shared<Tower1> (tmpTile->getX(), tmpTile->getY()));
                tmpTile->switchPlaceable();
            }
        }
    }

    // Send the event to the base class (see Go_Back_State.h)
    Go_Back_State::handle_event (event);
}

Game_Event Game_State :: update ()
{
    for (auto & t : towers)
    {
        t->update();
    }

    // Iterate over all balls and let
    // the update themselves.
    //for ( auto & ball :  balls )
	//ball.update ();

    // Let the base class perform it's update
    return Go_Back_State::update ();
}

void Game_State :: render (RenderTarget & target)
{
    gameMap.render(target);

    for (auto & t : towers)
    {
        t->render(target);
    }

    target.draw(gameOverlay);

    // Let each ball render itself onto the
    // supplied RenderTarget
    //for ( auto & ball : balls )
	//ball.render (target);
}

/*
 * If we want to remove all balls which are outside
 * of the screen we need to iterate all balls and
 * do two things for each ball:
 * 1. Check if it is outside of the screen
 * 2. If it is, make sure that we remove it from
 *    the vector.
 *
 * The first part can be solved in several ways.
 * We can for instance implement our own logic
 * for checking if a sprite is on the screen
 * or not, or we can use some built-in functions
 * in SFML.
 *
 * In this example we use the latter.
 *
 * We begin by getting the global bounds of each ball.
 *
 * A bounds is the smallest possible rectangle which
 * covers the entire ball (these are basically the
 * "hitboxes" of our balls).
 *
 * There are two kinds of bounds for each ball, a
 * global bound and a local bound, the difference
 * is where the (0, 0) coordinate is placed.
 *
 * In a global bound, (0, 0) referes to top-left
 * corner of the window, while in a local bounds
 * it referes to the origin of the ball (in this
 * example, the center of the ball (see Ball.cpp
 * for details)).
 *
 * Using the global bounds we can use the built-in
 * 'intersects' function to check if the bounds
 * intersects the screen. If it does, it is still
 * visible, if not it is safe to remove.
 *
 * The second part is a bit trickier.
 *
 * A problem arises when we iterate over the
 * balls and then remove one of them; the current
 * index has been changed so we have now potentially
 * skipped over an element.
 *
 * Example of how this might happen:
 *
 * Say that we are iterating over this list, with
 * a standard index based for-loop (here ^ denotes
 * the element we are currently looking at):
 *
 * 1 5 7 2 4 3
 *     ^
 * Now say that we remove the 7, then we have:
 *
 * 1 5 2 4 3
 *     ^
 * Note that ^ now points to the next element, but the
 * same location as before, which might at first glance
 * seem like what we exactly want. But we must not
 * forget that the final step in a for loop is to step
 * the index, so the next iteration will look like this:
 *
 * 1 5 2 4 3
 *       ^
 * Which shows that we have skipped an element.
 *
 * This means that we have to be a bit more cleaver
 * when removing elements from the list we are
 * iterating.
 *
 * But we are in luck, we can use an iterator based
 * for-loop, since erase (the function which removes
 * elements from the vector) removes elements pointed
 * to by iterators, and returns an iterator to the next
 * element.
 */
/*
void Game_State :: cleanup ()
{
    for ( auto it { std::begin (balls) }; it != std::end (balls); )
    {
        // get the global bounds of our current ball
	auto bounds { it -> bounds () };
        // get a rectangle representing the screen
	FloatRect screen { 0, 0, screen_width, screen_height };
	if ( !screen.intersects (bounds) )
	    it = balls.erase (it);
	else
	    ++it;
    }
}
*/