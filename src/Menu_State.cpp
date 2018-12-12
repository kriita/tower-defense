#include "Menu_State.h"
#include "Events.h"
#include "Game_State.h"
#include "Manager.h"
#include "Map.h"
#include "constants.h"

#include <string>

using namespace sf;

/*
 * Create the welcome message using the font given in
 * 'resources/fonts/font.ttf'.
 *
 * The font is loaded using Font_Manager (see Manager.h for details).
 *
 * The first argument of the sf::Text constructor is what string
 * it should draw, the second argument is what font should be used
 * to draw the text and the final argument specifies the font-size
 * (in pixels) of the text.
 */
Menu_State :: Menu_State ()
    : text { "Welcome to kill cute animals TD. Click in the rabbit!",
             Font_Manager::load ("resources/fonts/font.ttf"),
             16 },
      play { false }
{
    maps.push_back(make_unique<Map> ("Forest"));
    maps.push_back(make_unique<Map> ("Gauntlet"));
    maps[0]->makePreview(250, 200, 0.2);
    maps[1]->makePreview(400, 200, 0.2);

    if(!menuOverlayTexture.loadFromFile("resources/images/menuWindow.png"))
    {
        throw Game_StateError{"Couldn't load overlay texture"};
    }
    menuOverlay.setTexture(menuOverlayTexture);
    menuOverlay.setPosition(screen_width/2, screen_height/2);
    menuOverlay.setOrigin(250, 200 );
    if(!rabbitOverlayTexture.loadFromFile("resources/images/background.jpg"))
    {
        throw Game_StateError{"Couldn't load overlay texture"};
    }
    rabbitOverlay.setTexture(rabbitOverlayTexture);
}

/*
 * First we send the event to our base class, after that we
 * check for the 'enter' key.
 *
 * If it has been pressed we want to change to a new state in update.
 */
void Menu_State :: handle_event (Event event)
{
    Go_Back_State::handle_event (event);


    if ( event.type == Event::MouseButtonReleased )
    {
        auto mouse { event.mouseButton };
        if ( mouse.button == Mouse::Button::Left )
        {
            if (mouse.x > 85 && mouse.x < 315 && mouse.y > 85 && mouse.y < 315  && showMaps)
            {
                level = "Forest";
                play = true;
            }
            else if (mouse.x > 285 && mouse.x < 515 && mouse.y > 85 && mouse.y < 315  && showMaps)
            {
                level = "Gauntlet";
                play = true;
            }
            showMaps = true;
        }
    }
    if ( event.type == Event::KeyPressed )
    {
        if ( event.key.code == Keyboard::Key::Return )
            play = true;
        else if ( event.key.code == Keyboard::Key::Escape )
            go_back = true;
    }
}

/*
 * If the 'enter' key has been pressed, we signal to the
 * state machine that we want to switch to a new 'Game_State'
 * state (see Game_State.h).
 *
 * If 'enter' has not been pressed, check wheter or not
 * the actions of the base class (Go_Back_State (see Go_Back_State.h))
 * should be performed instead.
 */
Game_Event Menu_State :: update ()
{
    if ( play )
    {
        play = false;
        return Game_Event::create<Switch_State> (
            move (std::make_unique<Game_State> (level)));
    }
    if ( showMaps)
    {

    }
    return Go_Back_State::update ();
}

void Menu_State :: render (RenderTarget & target)
{
    auto bounds { text.getGlobalBounds () };
    auto size   { target.getSize () };
    
    text.setPosition ((size.x - bounds.width) / 2,
                      (size.y - bounds.height) / 8);
    

    target.draw(rabbitOverlay);
    if (!showMaps)
        target.draw (text);

    if (showMaps)
    {
        target.draw (menuOverlay);
        maps[0]->render(target);
        maps[1]->render(target);
    }
}

/*
 * Whenever this state becomes the active state
 * we want to make sure that play is not true,
 * because if it where we would immedietly
 * change to a new state.
 *
 * See Go_Back_State.cpp for more details.
 */
void Menu_State :: activate ()
{
    play = false;
    Go_Back_State::activate ();
}
