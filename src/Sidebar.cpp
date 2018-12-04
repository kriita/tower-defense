/**
 * Sidebar.cpp
 **
 * Description: Defines the behavior and rendering of the in-game sidebar. 
 *
 * WARNING: Commented out until Resource_Window, Shop_Window and Info_Window
 * are finished.
 *
 * WARNING: gameResources is a temporary name for game_state's Resources
 * object.
 *
 * WARNING: availableTowers is a temporary name for the vector provided in the
 * map object that consists of availableTower object. An availableTower object
 * is (atm) a struct that has 3 values: the (tower) class of the buildable
 * tower object, its price as an int, and its sprite.
 * * availableTower IS JUST A WORKING CLASS AND DOESN'T NECESSARILY REFLECT THE
 * FINAL PRODUCT *
 * 
 */

#include "Sidebar.h"
#include "constants.h"
#include <SFML/Graphics.hpp>
#include "Resource_Window.h"
//#include "Shop_Window.h"
//#include "Info_Window.h"
#include <memory>

#include "Manager.h"

using std::make_unique;

Sidebar::Sidebar(int xPos)
: x {xPos}
//sidebarShop {new Shop_Window(xPos, availableTowers)},
//sidebarInfo {new Info_Window(xPos)}
{
	sidebarResources = make_unique<Resource_Window>(xPos);
}

void Sidebar::update(ptr<Resources> (& gameResources))
{
	sidebarResources -> update(gameResources);
//	sidebarShop.update();
//	sidebarInfo.update();
}

void Sidebar::render(sf::RenderTarget &target)
{
	sidebarResources -> render(target);
//	sidebarShop.render();
//	sidebarInfo.render();
}

int Sidebar::getX()
{
	return x;
}

int Sidebar::getY()
{
	return y;
}