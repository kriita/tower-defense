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
	for (unsigned int i = 0; i < 6; ++i)
	{
		prices.push_back(std::make_shared<sf::Text>
		("", Font_Manager::load("resources/fonts/font.ttf"), H4));
	}
	

	// Gör om till for-loop i = 0; i < 181; i += 90
	prices[0] -> setPosition(x + 20, y + 40);
	prices[1] -> setPosition(x + 140, y + 40);
	prices[2] -> setPosition(x + 20, y + 130);
	prices[3] -> setPosition(x + 140, y + 130);
	prices[4] -> setPosition(x + 20, y + 220);
	prices[5] -> setPosition(x + 140, y + 220);

	items.push_back(std::make_shared<sf::Rect<int>>(
		static_cast<int>(sidebarPosX + mapBorderOffset),
    		static_cast<int>(y),
    		48, 48));
	items.push_back(std::make_shared<sf::Rect<int>>(
		static_cast<int>(sidebarPosX + mapBorderOffset + 120),
    		static_cast<int>(y),
    		48, 48));
	items.push_back(std::make_shared<sf::Rect<int>>(
		static_cast<int>(sidebarPosX + mapBorderOffset),
    		static_cast<int>(y + 90),
    		48, 48));
	items.push_back(std::make_shared<sf::Rect<int>>(
		static_cast<int>(sidebarPosX + mapBorderOffset + 120),
    		static_cast<int>(y + 90),
    		48, 48));
	items.push_back(std::make_shared<sf::Rect<int>>(
		static_cast<int>(sidebarPosX + mapBorderOffset),
    		static_cast<int>(y + 180),
    		48, 48));
	items.push_back(std::make_shared<sf::Rect<int>>(
		static_cast<int>(sidebarPosX + mapBorderOffset + 120),
    		static_cast<int>(y + 180),
    		48, 48));

	buildModeText.setPosition(x + 20,
			   y + 200);
}

void Shop_Window::update(std::vector<shptr<Tower>>( &availableTowers))
{
	for (unsigned int i = 0; i < availableTowers.size(); ++i)
	{
		prices[i] -> setString(std::to_string(availableTowers[i] -> getPrice()));
	}
	//price1.setString(std::to_string(availableTowers[0] -> getPrice()));
}

void Shop_Window::render(sf::RenderTarget &target, ptr<Resources>(&gameResources), std::vector<shptr<Tower>>( &availableTowers))
{
	for (unsigned int i = 0; i < availableTowers.size(); ++i)
	{
		availableTowers[i] -> render(target);
	}

	//target.draw(price1);
	
	for (unsigned int i = 0; i < prices.size(); ++i)
	{
		target.draw(*(prices[i]));
	}

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