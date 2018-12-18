#pragma once
#include <SFML/Graphics.hpp>
#include "defs.h"
#include "Map.h"
#include "State.h"
#include "Go_Back_State.h"
#include <vector>
#include <string>

/*
 * Free to use picture for start
 * https://freephotos.cc/animal#372166
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
    sf::Text text;
    bool play;
    bool showMaps{false};
    sf::Texture menuOverlayTexture {};
    sf::Sprite menuOverlay {};
    std::string level {};
    sf::Texture rabbitOverlayTexture {};
    sf::Sprite rabbitOverlay {};    
    int firstMapX = 190;
    int firstMapY = 140;
    int mapSize = 112;
    int offset = 150;
    std::vector<ptr<Map>> maps {};
};
