#include "Game.h"
#include "Events.h" // include all possible game events
#include "Menu_State.h" // include the initial state
#include "State.h" // include the base state
#include "constants.h" // include all global constants

using namespace sf;

/*
 * Initialize the window and the state machine.
 *
 * The constructor of RenderWindow takes a 'VideoMode'
 * which defines the width, height and bits per pixel
 * (default 32), a title which should be visible in
 * the titlebar of the windows, as well as a style flag.
 * The style flag is a bit mask (i.e. a value where
 * each bit represents a property) of properties we
 * want our window to have. If we do not care,
 * we can omitt this argument or use sf::Style::Default.
 *
 * The constructor of RenderWindow does take a fourth
 * argument, but it is very rarely used so it is not
 * covered here (see the SFML documentation for more info).
 *
 * The state machine constructor takes only one argument:
 * a pointer to the initial state. The program will
 * only work if we have at least one state running so
 * we have to supply what state we should start with.
 *
 */
Game :: Game (std::string const & title,
              unsigned            width,
              unsigned            height)
    : window { VideoMode { width, height },
               title, Style::Titlebar | Style::Close },
      machine { std::make_unique<Menu_State> () },
      running { true }
{
}

void Game :: start ()
{
    // The clock is used to measure of long each iteration took
    // this is used to keep the framerate as steady as possible.
    Clock clock { };
    while ( running )
    {
        State & state { machine.current_state () };
        
        handle_events (state);

        // update the game and store the recieved game event
        // into the 'event' variable.
        Game_Event event { state.update () };

        /*
         * clear fills the entire window with one color
         * (by default black) thus overwriting everything
         * that was drawn before.
         *
         * If we do not perform this step we allow for weird
         * graphical artifacts to show up.
         */
        window.clear ();

        // let the state render itself onto the window
        state.render (window);

        /*
         * No drawn pixels will be shown in the window
         * until this function is called.
         *
         * All drawing operations are performed on a
         * hidden buffer in memory, so if we want them
         * to actually show up on the screen we have
         * make sure that the window switches to drawing
         * that buffer instead of its current one.
         * (This technique is called 'double buffering')
         */
        window.display ();

        /*
         * When all logic and rendering has been performed
         * we are now ready to update the state.
         */
        event.apply (machine, *this);

        /*
         * Wait if we still haven't reached the target
         * time for a frame.
         */
        delay (clock);
    }
}

void Game :: stop ()
{
    running = false;
}

void Game :: handle_events (State & state)
{
    /*
     * event is an object which contains all
     * relevant information for an event that
     * occured in the window (i.e. key-pressed,
     * mouse clicks etc.).
     *
     * The function 'pollEvent' takes the next
     * event in the event queue and places it
     * in the 'event' variable so that we can
     * read what that event was.
     *
     * While there are events in event queue
     * 'pollEvent' will return true.
     */
    Event event;
    while ( window.pollEvent (event) )
    {
        // Check if the window has been closed.
        // This event fires whenever the user
        // presses the X icon, or if the operating
        // system kills it.
        if ( event.type == Event::Closed )
            running = false;

        // send the event to 'state'
        state.handle_event (event);
    }
}

void Game :: delay (sf::Clock & clock) const
{
    sleep (milliseconds (1000.0 / fps) - clock.getElapsedTime ());
    clock.restart ();
}
