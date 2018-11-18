#pragma once

#include "defs.h"

#include <memory>
#include <stack>

class State;

/*
 * This class represents the current state of the state machine.
 *
 * This implementation of a state machine keeps a stack of all
 * the previous states, where the top of the stack is the current
 * state. This is done so that going back is easy.
 *
 * Please note: This is just one way to do it, there are several
 * other ways and none of them work for every case, so if you
 * want to implement your own state machine make sure that
 * it can do all the operations that you need for your project.
 */
class State_Machine
{

public:

    /*
     * Construct a state machine, and push the 'initial_state'
     * to the underlying stack.
     */
    State_Machine (ptr<State> initial_state);

    /*
     * Switch to a new state, stored in the 'state' pointer.
     *
     * This will call 'deactivate' on the current state,
     * then push 'state' to the stack, and finally call
     * 'activate' on the new current state.
     */
    void switch_state (ptr<State> state);

    /*
     * This will make the state machine discard the current
     * state and go back to the one before.
     *
     * Note that the current state will be popped from the
     * stack, meaning it will be destroyed. This is one
     * drawback introduced by using this method of managing
     * the states, take that into consideration when
     * implementing your own state machine.
     * 
     * This function will call 'deactivate' on the current
     * state, then pop that state from the stack, making the
     * previous state the top of the stack. Finally it will
     * call activate on the previous state.
     *
     * This function returns true if it managed to go back
     * and it returns false if there is no previous state.
     */
    bool previous_state ();

    /*
     * Get a reference to the current state.
     *
     * Please that this reference will only be valid
     * as long as the state is the active one.
     * As soon as the stack has been modified in any
     * way, all guarantees of validity are gone.
     */
    State & current_state () const;

private:

    /*
     * The underlying stack, containing unique pointers
     * to the states.
     */
    std::stack<ptr<State>> states;
    
};
