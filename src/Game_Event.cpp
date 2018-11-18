#include "Game_Event.h"

/*
 * Move the ownership of 'event' to the Game_Event object
 */
Game_Event :: Game_Event (ptr<Base_Event> event)
    : event { move (event) }
{
}

/*
 * Wrapper for calling apply on the the underlying
 * polymorphic object.
 */
void Game_Event :: apply (State_Machine & machine,
                          Game &          game)
{
    event -> apply (machine, game);
}
