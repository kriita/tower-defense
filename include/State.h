#pragma once

#include "Game_Event.h"

#include <SFML/Graphics.hpp> // this include most of the basic SFML features

/*
 * This class represents a state of the game.
 * These states are different views in the game,
 * which contains its own separate logic.
 *
 * Examples of states are: menues, different
 * views in a game (shop views, overworld views,
 * game view) etc.
 *
 * This is a pure virtual function which declares
 * a couple of general functions which is used by
 * the state machine to deligate work to the state.
 *
 * The responsibilities of a state are roughly speaking
 * separated into three categories:
 * - Input from the user (keypresses, mouse clicks, etc.)
 * - Internal logic (move sprites, check for collision etc.)
 * - Rendering (drawing objects to the screen)
 *
 * These steps are represented by the functions:
 * - handle_event (input step)
 * - update (logic step)
 * - render (rendering step)
 *
 * To define a valid state said state has to be derived
 * of this class, and needs to override the three functions
 * mentioned above.
 */
class State
{
    
public:

    // this is a base class so a virtual destructor is needed
    virtual ~State () = default;

    /*
     * This function is called for each event which occurs
     * in the window. It is the responsibility of the state
     * to filter out any events it is interested in, since
     * no filtering is performed before calling this function.
     *
     * What this means is that if a state only wants to know
     * if a certain event has happened, the state needs to
     * check for that event inside this function.
     */
    virtual void handle_event (sf::Event event);

    /*
     * The 'update' function is called every iteration of the
     * game loop, no more and no less.
     *
     * The function will return a Game_Event object, which
     * is an event that will tell the state machine what
     * to do next.
     *
     * Note that 'update' must always return a Game_Event,
     * even when nothing should be done. Because of this,
     * there is an event called 'Keep_Going' which simply
     * tells the state machine to do preciesly that: 'keep
     * going as you are'.
     *
     * See Game_Event.[h|cpp] for more details on how
     * a game event works.
     *
     * See Events.[h|cpp] for example events.
     */
    virtual Game_Event update () = 0;

    /*
     * Render the state onto the screen through a 'RenderTarget'.
     *
     * A RenderTarget is an abstract class which defines an
     * interface for rendering to a canvas. Two types
     * of RenderTargets exist in SFML:
     * - RenderWindow; draw directly to a window.
     * - RenderTexture; draw onto a texture which can be extracted
     *   later on using the 'getTexture' member function.
     */
    virtual void render(sf::RenderTarget & target) = 0;

    /*
     * This function is called whenever this state
     * becomes the active one in the state machine.
     *
     * By default it does nothing, but can be useful
     * sometimes (see Menu_State.[h|cc] and
     * Go_Back_State.[h|cc] for examples of how this
     * can be used).
     */
    virtual void activate ();

    /*
     * This function is called whenever this state
     * is replaced with another state in the state machine.
     */
    virtual void deactivate ();
    
};
