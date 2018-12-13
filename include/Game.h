#pragma once

#include "State.h"
#include "State_Machine.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>

/*
 * This class is responsible for running the main loop of the game.
 *
 * The Game is structured around an implementation of a state machine
 * (see State_Machine.[h|cpp]).
 * The class does not know anything about the actual game, all it knows
 * is that the game consists of states, and the only job if this class
 * is to manage those states, keep the game running and handling the Window
 * in which the Game is drawn.
 *
 * Each state represents a seperate 'screen' of the game, and are all
 * derived from the pure virtual class 'State' (see State.[h|cc]). In this
 * example, the following states are available:
 * - A welcome screen (located in Menu_State.[h|cpp])
 * - The actual "game" (located in Game_State.[h|cpp])
 * - A pause screen (located in Pause_State.[h|cpp]).
 *
 * The first state (the so called "initial state") of the game is the
 * welcome screen. From there the state can issue messages, or 'events'
 * meant to perform certain operations on the state machine (for example
 * switch to a new state, go back to the previous state etc.).
 * These events are returned from the state to this class (the Game class)
 * who in return will pass it on to the actual state machine (see Game.cpp
 * for details).
 */

class GameError : public std::logic_error
{
    using std::logic_error::logic_error;
};

class Game
{
public:

    /*
     * Constructor of Game.
     *
     * Will perform these tasks:
     * - initialize the state machine with an initial state (welcome
     *   screen),
     * - spawn a window with the specified titlebar, width and height
     *   (in pixels)
     */
    Game (std::string const & title, unsigned width, unsigned height);

    /*
     * Run the main loop of the state machine, and therefore by extension
     * the entire game.
     *
     * Each iteration of the main loop go through these steps:
     * - Handle all window events from the event queue (these include
     *   key presses/releases, mouse movement, resizing of the window
     *   and more).
     *
     *   What this means is that we check if the user has requested
     *   to close the window and therefore the game, and for any other
     *   events we pass them on to the state.
     * - Update the currently active state.
     *
     *   This means running any logic that the state might have, for
     *   example; move objects, check for collision, manage resources
     *   etc. This step will probably perform the vast majority of the
     *   logic in the project (depending on the project of course).
     *
     * - Draw the currently active state to the window.
     *
     *   This step will simply pass the window to the state and will
     *   thus allow the state to draw itself onto the windows. This
     *   is beneficial since we now have completely decoupled the
     *   state from the Game class, thus allowing all behaviour of a
     *   state to be implemented in the corresponding class without
     *   having to touch any other code.
     */
    void start ();

    /*
     * This function will tell to game to stop running.
     *
     * Note: This function will not exit the game directly, but will
     * instead do so after the current iteration has completed. 
     */
    void stop  ();

private:

    /*
     * Internal function to handle the incoming window events.
     *
     * All events will be passed to the 'state' parameter.
     */
    void handle_events (State & state);

    /*
     * This function puts the program to sleep for a certain
     * period of time in order to keep a steady framerate.
     * The inargument is how many milliseconds the current iteration
     * took to complete.
     *
     * Say that the game is supposed to run at 60 frames per second (fps).
     * This means that each frame should take exactly 1000/60 = 16.666...
     * milliseconds to run. If it took longer, then there is not much
     * we can do about it, but if it took a shorter amount of time,
     * then request that our program sleep for the remaining time.
     */
    void delay (sf::Clock & clock) const;

    /*
     * SFML representation of window which we can draw on.
     */
    sf::RenderWindow window;

    /*
     * The state machine, contains all relevant information and
     * operations neccessary to use the state machine.
     */
    State_Machine    machine;

    /*
     * If true, then the game should keep on run, otherwise the next
     * iteration of the game loop will not run.
     */
    bool             running;

    bool fullscreen {false};

    bool music {true};

    // For custom cursor
    sf::Texture cursorTexture {};
    sf::Sprite cursorSprite {};  

    sf::Music backgroundMusic {};
};
