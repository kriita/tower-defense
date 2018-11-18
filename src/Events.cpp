#include "Events.h"
#include "Game.h"

// Keep_Going does absolutely nothing
void Keep_Going :: apply (State_Machine &,
                          Game &)
{
}

void Previous_State :: apply (State_Machine & machine,
                              Game &          game)
{
    // if we could not go back to a previous state
    // (because no previous state exists) we
    // simply exit the game.
    if ( !machine.previous_state () )
        game.stop ();
}

Switch_State :: Switch_State (ptr<State> && state)
    : state { move (state) }
{
}

void Switch_State :: apply (State_Machine & machine,
                            Game &)
{
    // move 'state' into the state machine.
    machine.switch_state (move (state));
}

void Exit_Game :: apply (State_Machine &,
                         Game & game)
{
    game.stop ();
}
