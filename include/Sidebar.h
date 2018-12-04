#pragma once

/** 
 * Sidebar.h
 **
 * Header file for Sidebar.cpp.
 *
 * WARNING: Commented out until Resource_Window, Shop_Window and Info_Window are finished.
 * 
 */

#include <stdexcept>
#include "constants.h"
#include <SFML/Graphics.hpp>
#include "Resource_Window.h"
//#include "Shop_Window.h"
//#include "Info_Window.h"
#include <memory>

class SidebarError : public std::logic_error
{
	using std::logic_error::logic_error;
};

class Sidebar
{
public:
	Sidebar(int xPos);
	~Sidebar() = default;
	
	void update(ptr<Resources> const & gameResources);
	void render(sf::RenderTarget &target);

	int getX();
	int getY();
	
private:
	int x;
	int y;

	//shptr<Resource_Window> sidebarResources {};
	//shptr<Shop_Window> sidebarShop {};
	//shptr<Info_Window> sidebarInfo {};
};