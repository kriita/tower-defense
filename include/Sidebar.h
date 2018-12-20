#pragma once

/** 
 * Sidebar.h
 **
 * Header file for Sidebar.cpp.
 *
 */

#include <stdexcept>
#include "constants.h"
#include <SFML/Graphics.hpp>
#include "Resource_Window.h"
#include "Resources.h"
#include "Shop_Window.h"
#include "Focus_Window.h"
#include "Tower.h"
#include <memory>

class SidebarError : public std::logic_error
{
	using std::logic_error::logic_error;
};

class Sidebar
{
public:
	Sidebar(int xPos, std::vector<shptr<Tower>>(&availableTowers1));
	~Sidebar() = default;
	
	void update(ptr<Resources> & gameResources, std::vector<shptr<Tower>>(& availableTowers));
	void render(sf::RenderTarget &target, ptr<Resources>(&gameResources), std::vector<shptr<Tower>>(& availableTowers));
	void handle_event(int mousePosX, int mousePosY, ptr<Resources>(&gameResources), std::vector<shptr<Tower>>(&availableTowers), ptr<WavePump>(&wavePump));

	int getX();
	int getY();
	
private:
	int x {};
	int y {};

	ptr<Resource_Window> sidebarResources {};
	ptr<Shop_Window> sidebarShop {};
	std::vector<shptr<Tower>> availableTowers{};
	shptr<Focus_Window> sidebarInfo {};
	
	sf::RectangleShape background {sf::Vector2f(screen_width - sidebarPosX, screen_height)};
};