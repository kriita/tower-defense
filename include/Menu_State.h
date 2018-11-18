#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Go_Back_State.h"

/*
 * A simple state containing a short welcome message.
 *
 * This class acts as an example of how a state can be
 * implemented.
 */
class Menu_State : public Go_Back_State
{

public:

    Menu_State ();

    virtual void handle_event (sf::Event event) override;
    virtual Game_Event update () override;
    virtual void render (sf::RenderTarget & taget) override;
    virtual void activate () override;
    
private:

    /*
     * sf::Text is a drawable object representing a string.
     *
     * sf::Text can be drawn to any RenderTarget as long as
     * a font and a string is supplied.
     *
     * It works like a sf::Sprite but represents text instead
     * of an image.
     */
    sf::Text text;

    /*
     * Flag to determine wheter or not the 'enter' key has been
     * pressed (see Menu_State.cpp for details).
     */
    bool play;
    
};
