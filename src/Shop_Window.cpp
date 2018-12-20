/**
 * Shop_Window.cpp
 * *
 * Defines the behavior of the in-game shop in the sidebar.
 * Currently located in the middle of the sidebar.
 *
 * Semi-modular, small fixes in the constructor can make the shop much more
 * modular.
 * 
 * Height: 216
 */

#include "Shop_Window.h"
#include "Resources.h"
#include "Map.h"
#include "constants.h"
#include "defs.h"
#include "Tower.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

Shop_Window::Shop_Window(int xPos, std::vector<shptr<Tower>> (&availableTowers1))
: x {xPos}, y {140}, availableTowers {availableTowers1}
{
	// Generate blank price objects
	for (unsigned int i = 0; i < 6; ++i)
	{
		prices.push_back(std::make_shared<sf::Text>
		("", Font_Manager::load("resources/fonts/font.ttf"), H4));
	}
	
	// Set position of graphic modules
	for (unsigned int i = 0; i < 71; i += 70)
	{
		availableTowers[i / 35] -> setPosition(
			static_cast<double>(x + 36), 
			static_cast<double>(y + 28 + i));
		availableTowers[i / 35 + 1] -> setPosition(
			static_cast<double>(x + 36 + 120), 
			static_cast<double>(y + 28 + i));

		prices[i / 35] -> setPosition(x + 20, y + 40 + i);
		prices[i / 35 + 1] -> setPosition(x + 140, y + 40 + i);

		items.push_back(std::make_shared<sf::Rect<int>>(
			static_cast<int>(sidebarPosX + mapBorderOffset),
    			static_cast<int>(y + i),
    			48, 48));
		items.push_back(std::make_shared<sf::Rect<int>>(
			static_cast<int>(sidebarPosX + mapBorderOffset + 120),
    			static_cast<int>(y + i),
    			48, 48));
	}

	buildModeText.setPosition(x + 20,
			   y + 200);
}

void Shop_Window::update(std::vector<shptr<Tower>>( &availableTowers))
{
	// Set values of price text objects to reflect those of the respective towers
	for (unsigned int i = 0; i < availableTowers.size(); ++i)
	{
		prices[i] -> setString(std::to_string(availableTowers[i] -> getPrice()));
	}
}

void Shop_Window::render(sf::RenderTarget &target, ptr<Resources>(&gameResources), std::vector<shptr<Tower>>( &availableTowers))
{
	// Draw available towers
	for (unsigned int i = 0; i < availableTowers.size(); ++i)
	{
		availableTowers[i] -> render(target);
	}
	
	// Draw prices of each tower
	for (unsigned int i = 0; i < prices.size(); ++i)
	{
		target.draw(*(prices[i]));
	}

	// Show build mode text if a tower is being built
	if (gameResources -> getBuildMode())
	{
		target.draw(buildModeText);
	}
}

void Shop_Window::handle_event(int mousePosX, int mousePosY, ptr<Resources>(&gameResources), std::vector<shptr<Tower>>(&availableTowers))
{
	for (unsigned int i = 0; i < items.size(); ++i)
	{
		// If a tower in the shop is clicked on, and there is enough money in the bank,
		// turn on build mode and allow user to build it.
		if ((items[i] -> contains(mousePosX, mousePosY)) &&
		    (availableTowers[i] -> getPrice()) <= (gameResources -> getMoney()))
		{
			gameResources -> setFocus(availableTowers[i]);
			gameResources -> switchBuildMode();
		}
	}
}