#include "Go_Back_State.h"
#include "Events.h"

using namespace sf;

/*
 * Check for the escape key. If it is found,
 * set the go_back flag to true.
 */
void Go_Back_State :: handle_event (Event event)
{
    if ( event.type == Event::KeyPressed )
    {
        if ( event.key.code == Keyboard::Key::Escape )
            go_back = true;
    }
}

/*
 * If escape has been pressed, then we return the
 * message 'Previous_State' which tells the state machine
 * to destroy this state and go back to the previous one.
 *
 * If the escape key has not been pressed we do nothing.
 */
Game_Event Go_Back_State :: update ()
{
    if ( go_back )
    {
        go_back = true;
        return Game_Event::create<Previous_State> ();
    }

    return Game_Event::create<Keep_Going> ();
}

/*
 * Since this class is meant as a base class
 * we cannot really control wheter or not
 * a derived class performs their own logic before
 * the 'update' function of this class is called.
 *
 * This causes a problem whenever the derived
 * class switches to a new state in the same frame
 * that the escape key is pressed, since go_back
 * has been set to true (we pressed escape).
 *
 * This would mean that when that new state is
 * popped from the state machine and it returns
 * to this state, we would immedietly go back
 * to the state before this one, since we have
 * not reset go_back.
 *
 * Therefore we reset go_back in this state
 * whenever it becomes active.
 *
 * The situation described above can cause quite
 * subtle glitches in the program which might
 * not be ideal, but unfortunately this is a
 * drawback of this way of implementing a
 * state machine.
 */
void Go_Back_State :: activate ()
{
    go_back = false;
}
