/**
 * Sidebar.cpp
 **
 * Description: Defines the behavior and rendering of the in-game sidebar.
 * 
 */

#include "constants.h"
#include "Focus_Window.h"
#include "Resource_Window.h"
#include "Resources.h"
#include "Shop_Window.h"
#include "Sidebar.h"
#include "Tower.h"

#include <SFML/Graphics.hpp>
#include <memory>

#include "Manager.h"

using std::make_unique;

Sidebar::Sidebar(int xPos, std::vector<shptr<Tower>>(&availableTowers1))
: x {xPos}, availableTowers {availableTowers1}
{
	sidebarResources = make_unique<Resource_Window>(xPos);
	sidebarShop = make_unique<Shop_Window>(xPos, availableTowers);
	sidebarInfo = make_unique<Focus_Window>(xPos);

	background.setFillColor(sf::Color(135, 105, 70));
	background.setPosition(x,0);
}

void Sidebar::update(ptr<Resources> (& gameResources),
		     std::vector<shptr<Tower>>(& availableTowers))
{
	sidebarResources -> update(gameResources);
	sidebarShop -> update(availableTowers);
}

void Sidebar::render(sf::RenderTarget &target, ptr<Resources>(&gameResources), std::vector<shptr<Tower>>(& availableTowers))
{
	target.draw(background);
	sidebarResources -> render(target);
	sidebarShop -> render(target, gameResources, availableTowers);
	sidebarInfo -> render(target, gameResources);
}

void Sidebar::handle_event(int mousePosX, int mousePosY, ptr<Resources>(&gameResources),
	std::vector<shptr<Tower>>(&availableTowers), ptr<WavePump>(&wavePump))
{
	sidebarResources -> handle_event(mousePosX, mousePosY, wavePump, gameResources);
	sidebarShop -> handle_event(mousePosX, mousePosY, gameResources, availableTowers);
}

int Sidebar::getX()
{
	return x;
}

int Sidebar::getY()
{
	return y;
}