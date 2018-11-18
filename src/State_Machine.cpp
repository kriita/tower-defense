#include "State_Machine.h"
#include "State.h"

using namespace std;

State_Machine :: State_Machine (ptr<State> initial_state)
    : states { }
{
    states.push (move (initial_state));
}

void State_Machine :: switch_state (ptr<State> initial_state)
{
    current_state ().deactivate ();
    states.push (move (initial_state));
    current_state ().activate ();
}

bool State_Machine :: previous_state ()
{
    // if this is the initial state,
    // simply return false, since
    // we should never allow the state
    // machine to contain no states.
    if ( states.size () <= 1 )
        return false;

    current_state ().deactivate ();
    states.pop ();
    current_state ().activate ();
    
    return true;
}

State & State_Machine :: current_state () const
{
    // return a reference instead of a pointer
    // to reduce errors and to not loose ownership
    // of the state.
    return *(states.top ());
}
