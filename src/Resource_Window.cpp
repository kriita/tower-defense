/**
 * Resource_Window.h
 * *
 * Defines the behavior of the resource information window in the sidebar.
 * Currently located at the top of the sidebar.
 * 
 * */

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
	// Constructor generates button fo the next wave and
	// sets position of graphic modules.

	nextWaveBtn = std::make_shared<sf::Rect<int>> (static_cast<int>(sidebarPosX + mapBorderOffset + 120),
    						       static_cast<int>(y + 5.5 * mapBorderOffset),
						       48, 48);

	if(!HPTexture.loadFromFile("resources/images/bottle_t.png"))
    	{
        	throw Resource_Window_Error{"Couldn't load bottle texture"};
    	}
	HPSprite.setTexture(HPTexture);
	HPSprite.setOrigin(0,8);
	HPSprite.setPosition(	x + static_cast<int>(0.5*mapBorderOffset),
				y + mapBorderOffset);
	HPText.setPosition(	x + static_cast<int>(4.5*mapBorderOffset),
				y + mapBorderOffset);
	
	if(!moneyTexture.loadFromFile("resources/images/money_t.png"))
    	{
        	throw Resource_Window_Error{"Couldn't load money texture"};
    	}
	moneySprite.setTexture(moneyTexture);
	moneySprite.setPosition(x + static_cast<int>(0.5*mapBorderOffset),
				y + static_cast<int>(4.5*mapBorderOffset));
	moneyText.setPosition(	x + static_cast<int>(4.5*mapBorderOffset),
				y + static_cast<int>(4.5*mapBorderOffset));

	waveText.setPosition(	x + static_cast<int>(0.5*mapBorderOffset),
				y + 8 * mapBorderOffset);

	if(!nextWaveTexture.loadFromFile("resources/images/nextWaveButton.png"))
    	{
        	throw Resource_Window_Error{"Couldn't load next wave button texture"};
    	}
	nextWaveSprite.setTexture(nextWaveTexture);
	nextWaveSprite.setPosition(static_cast<int>(x + 120),
    				   static_cast<int>(y + 6 * mapBorderOffset));
	
}

void Resource_Window::update(ptr<Resources> (& gameResources))
{
	// Update text objects to reflect current state in resources.
	HPText.setString(std::to_string(gameResources -> getHP()));
	moneyText.setString(std::to_string(gameResources -> getMoney()));
	waveText.setString("Wave " + std::to_string(gameResources -> getCurrentWave()));
}

void Resource_Window::render(sf::RenderTarget &target)
{
	target.draw(HPSprite);
	target.draw(HPText);
	target.draw(moneySprite);
	target.draw(moneyText);
	target.draw(waveText);
	target.draw(nextWaveSprite);
}

void Resource_Window::handle_event(int mousePosX, int mousePosY, ptr<WavePump>(&wavePump), ptr<Resources>(&gameResources))
{
	// Skip intermission if next wave button is pressed
	if (nextWaveBtn -> contains(mousePosX, mousePosY))
	{
		wavePump -> skipIntermission();
	}
}