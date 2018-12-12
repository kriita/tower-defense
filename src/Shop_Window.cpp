/**
 * Shop_Window.h
 * *
 * Defines the behavior of the in-game shop in the sidebar.
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

#include <iostream>

Shop_Window::Shop_Window(int xPos)
: x {xPos}, y {140}
{
	price1.setPosition(x + mapBorderOffset,
			   y + 3 * mapBorderOffset);
	items.push_back(std::make_shared<sf::Rect<int>>(
		static_cast<int>(sidebarPosX + mapBorderOffset),
    		static_cast<int>(y),
    		48, 48));

	buildModeText.setPosition(x + 4,
			   y + 12 * mapBorderOffset);
}

void Shop_Window::update(std::vector<shptr<Tower>>( &availableTowers))
{
	price1.setString(std::to_string(availableTowers[0] -> getPrice()));
}

void Shop_Window::render(sf::RenderTarget &target, ptr<Resources>(&gameResources), std::vector<shptr<Tower>>( &availableTowers))
{
	availableTowers[0] -> render(target);
	target.draw(price1);

	if (gameResources -> getBuildMode())
	{
		target.draw(buildModeText);
	}
}

void Shop_Window::handle_event(int mousePosX, int mousePosY, ptr<Resources>(&gameResources), std::vector<shptr<Tower>>(&availableTowers))
{
	for (unsigned int i = 0; i < items.size(); ++i)
	{
		if (items[i] -> contains(mousePosX, mousePosY)) //&&
			//(availableTowers[i] -> getPrice()) <= (gameResources -> getMoney()))
		{
			gameResources -> setFocus(availableTowers[i]);
			gameResources -> switchBuildMode();
		}
	}
}