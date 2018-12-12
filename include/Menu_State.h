#pragma once

#include <SFML/Graphics.hpp>

#include "defs.h"
#include "Map.h"
#include "State.h"
#include "Go_Back_State.h"

#include <vector>
#include <string>

/*
 * A simple state containing a short welcome message.
 *
 * This class acts as an example of how a state can be
 * implemented.
 */
class Menu_State : public Go_Back_State
{
/*
Free to use picture
 https://freephotos.cc/animal#372166

*/

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
    sf::Text textBana1;
    /*
     * Flag to determine wheter or not the 'enter' key has been
     * pressed (see Menu_State.cpp for details).
     */
    bool play;
    bool showMaps{false};
    sf::RectangleShape rect;
    sf::Texture menuOverlayTexture {};
    sf::Sprite menuOverlay {};
    std::string level {};
    sf::Texture rabbitOverlayTexture {};
    sf::Sprite rabbitOverlay {};    
    int firstMapX = 190;
    int firstMapY = 140;
    int mapSize = 112;
    int xOffset = 150;
    // Holds maps able for New game
    std::vector<ptr<Map>> maps {};
};
