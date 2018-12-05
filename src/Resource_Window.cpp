/**
 * Resource_Window.h
 * *
 * Header file for Resource_Window.cpp.
 *
 * WARNING: Needs to be subclass to a pure virtual Sidebar_Window in order to
 * dynamic cast in the event handler)
 *
 * WARNING: gameResources is the placeholder name for the game resources
 * object.
 *
 * IDEA: Make errors subclass of SidebarWindowError?
 */

#include "Resource_Window.h"
#include "Resources.h"
#include "Map.h"
#include "constants.h"
#include "defs.h"
#include <SFML/Graphics.hpp>
#include <memory>

Resource_Window::Resource_Window(int xPos)
: x {xPos + static_cast<int>(mapBorderOffset)}, y {static_cast<int>(mapBorderOffset)}
{
	if(!HPTexture.loadFromFile("resources/images/bottle_t.png"))
    	{
        	throw Resource_Window_Error{"Couldn't load bottle texture"};
    	}
	HPSprite.setTexture(HPTexture);
	HPSprite.setPosition(	x + mapBorderOffset,
				y + mapBorderOffset);
	HPText.setPosition(	x + 5 * mapBorderOffset,
				y + mapBorderOffset);
	
	if(!moneyTexture.loadFromFile("resources/images/money_t.png"))
    	{
        	throw Resource_Window_Error{"Couldn't load money texture"};
    	}
	moneySprite.setTexture(moneyTexture);
	moneySprite.setPosition(x + mapBorderOffset,
				y + 6 * mapBorderOffset);
	moneyText.setPosition(	x + 5 * mapBorderOffset,
				y + 6 * mapBorderOffset);
}

void Resource_Window::update(ptr<Resources> (& gameResources))
{
	HPText.setString(std::to_string(gameResources -> getHP()));
	moneyText.setString(std::to_string(gameResources -> getMoney()));
	//waveText.setString(std::to_string(<wave object's wave # value>), font,
	//		4 * mapBorderOffset;
}

void Resource_Window::render(sf::RenderTarget &target)
{
	target.draw(HPSprite);
	target.draw(HPText);
	target.draw(moneySprite);
	target.draw(moneyText);
}