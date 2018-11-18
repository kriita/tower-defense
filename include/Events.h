#pragma once

/*
 * For details on the usage of these classes, see Game_Event.h.
 */

#include "Game_Event.h"
#include "State.h"

/*
 * The Keep Going event signals that no action should be performed
 * in the state machine and that it should simply 'keep going'.
 */
class Keep_Going : public Game_Event :: Base_Event
{
protected:

    void apply (State_Machine & machine, Game & game) override;
    
};

/*
 * The Previous State event signals that this state should be
 * destroyed and the previous state should become the active
 * one instead.
 */
class Previous_State : public Game_Event :: Base_Event
{
protected:

    void apply (State_Machine & machine, Game & game) override;
    
};

/*
 * The Switch State event causes a new state to be pushed
 * into the state machine, and causes that state to become
 * the current state.
 */
class Switch_State : public Game_Event :: Base_Event
{
public:

    /*
     * 'state' is a unique_ptr to the state which
     * should become the new active state.
     */
    Switch_State (ptr<State> && state);
    
protected:
    
    virtual void apply (State_Machine & machine, Game & game) override;

    ptr<State> state;
    
};

/*
 * The Exit Game state causes the game to exit as soon as possible.
 */
class Exit_Game : public Game_Event :: Base_Event
{
protected:

    void apply (State_Machine & machine, Game & game) override;
    
};
