#pragma once

#include "State_Machine.h"
#include "defs.h"

/*
 * See Events.[h|cpp] for the actual implementation
 * of all events.
 */

using namespace std;

/*
 * Since Game.h includes this file, we would get a
 * circular include if we included Game.h here.
 * Because of this, we have to forward declare Game.
 */
class Game;

/*
 * Game_Event is a way for a state to communicate to
 * the Game class, and the state machine what they should
 * do.
 *
 * Using these Game_Events we can make sure that each
 * state can communicate with the state machine while
 * still not having access to the actual state machine.
 *
 * This type of 'messaging' is quite powerful since
 * it maintains a good level of code security (which
 * leads to less error prone code) while still allowing
 * a vast range of operations to be performed.
 *
 * Game_Event uses polymorphism to allow each type
 * of event to define what it should do with the
 * state machine and the game class.
 *
 * But for polymorphism to work, we need either a
 * reference or a pointer to the polymorphic type.
 * Therefore does Game_Event simply act as a wrapper
 * around the actual polymorphic event.
 *
 * Each event is derived from 'Base_Event' and uses
 * the virtual 'apply' function to define what should
 * happen when the event is performed on the state machine.
 */
class Game_Event
{

public:

    // forward declare the base event class
    class Base_Event;

    /*
     * Wrapper function to call the underlying polymorphic
     * object's apply function.
     *
     * This function is used in Game.cpp at the end of
     * each iteration of the game loop to update the
     * state machine according to the wishes of the
     * current state.
     */
    void apply (State_Machine & machine, Game & game);

    /*
     * This function creates new instances of the
     * various game events.
     *
     * Event_Type must be the class derived from
     * Base_Event which we want to create.
     *
     * 'typename... Args' is what is called a
     * variadic template. These are a way to
     * take arbitrarily many arguments in a function.
     * This functionality is used simply to pass
     * arguments from the 'create' function to
     * the constructor of 'Event_Type'.
     *
     * Variadic templates are not covered in this
     * course.
     *
     * Example usage:
     *
     * To create a 'Keep_Going' event:
     * Game_Event::create<Keep_Going> ()
     *
     * When we want to switch to a new state
     * we have to supply what state we should
     * switch to, this is done like so:
     * Game_Event::create<Switch_State> (make_unique<New_State> (...));
     *
     * Another, easier way to implement this type of functionality
     * is to manually create a static function for each
     * created Event. So for example:
     *
     * static Game_Event keep_going ();
     * static Game_Event switch_state (ptr<State> next);
     * ...
     *
     * This would lead to lower scalability since whenver
     * we create a new event we cannot forget to create a
     * function, but it is also a 100% valid solution (and
     * probably more understandable).
     */
    template <typename Event_Type, typename... Args>
    static Game_Event create (Args && ... args);

private:

    /*
     * We want the user to create Game_Events using
     * the 'create' function, therefore we declare
     * the constructor private.
     *
     * The reason we want the user to use 'create'
     * is two-fold:
     * 1. we want to be as easy as possible to create
     *    new events,
     * 2. we want to make sure that the Game_Event
     *    object is constructed correctly since it
     *    operates at the top level of the game,
     *    which we do not want to crash.
     */
    Game_Event (ptr<Base_Event> event);

    // pointer to actual implementation of the event
    ptr<Base_Event> event;
    
};

/*
 * pure virtual base class of all available Game_Event
 * implementations.
 */
class Game_Event::Base_Event
{

public:

    virtual ~Base_Event () = default;

protected:

    /*
     * This class should not be used directly.
     * It should be used through the Game_Event
     * class.
     *
     * Therefore we hide all functionality of
     * the class.
     */
    Base_Event () = default;

    /*
     * This function is called whenever Game_Event::apply
     * is called, which is at the end of the main game loop.
     *
     * This function defines what action should be performed
     * whenever a state returns this event.
     */
    virtual void apply (State_Machine & machine, Game & game) = 0;

    // make sure that Game_Event can call apply.
    friend Game_Event;
    
};

/*
 * Implementation of 'create'.
 */
template <typename Event_Type, typename... Args>
Game_Event Game_Event :: create (Args && ... args)
{
    return Game_Event { make_unique<Event_Type> (
            std::forward<Args>(args)...) };
}
