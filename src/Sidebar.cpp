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

/*
#include "sidebar.h"
#include "constants.h"

Sidebar::Sidebar(int xPos, int yPos)
: x {xPos}, y {yPos}, sidebarResources {new Resource_Window(gameResources)},
sidebarShop {new Shop_Window(availableTowers)}, sidebarInfo {new Info_Window()}
{}

class Sidebar
{
public:
	Sidebar(int xPos, int yPos);
	~Sidebar() = default;
	
private:
	int x;
	int y;

	Resource_Window sidebarResources;
	Shop_Window sidebarShop;
	Info_Window sidebarInfo;
};
*/