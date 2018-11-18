#pragma once

#include "State.h"

/*
 * A pure virtual class deried from State which contains the
 * logic for allowing the 'escape' key to send the user to
 * the previous game screen.
 *
 * This class is the base class for both Menu_State and
 * Game_State, since we want to allow the user to return
 * to the previous state (exit the game in the case of
 * Menu_State) by pressing the escape button.
 *
 * This class exists soley to reduce code repetion of the
 * same functionality.
 *
 * See State.h for a description of the functions.
 */
class Go_Back_State : public State
{
public:

    Go_Back_State () = default;
    
    virtual void handle_event (sf::Event event) override;
    virtual Game_Event update () override;
    virtual void activate () override;

protected:

    /*
     * Keep track of wheter or not 'escape' has been pressed.
     */
    bool go_back { false };
    
};
