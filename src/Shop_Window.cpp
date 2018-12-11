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

Shop_Window::Shop_Window(int xPos)
: x {xPos + static_cast<int>(mapBorderOffset)}, y {156}
{
	price1.setPosition(	x + 4,
				y + 2 * mapBorderOffset);
}

void Shop_Window::update(std::vector<shptr<Tower>>( &availableTowers))
{
	price1.setString(std::to_string(availableTowers[0] -> getPrice()));
}

void Shop_Window::render(sf::RenderTarget &target, std::vector<shptr<Tower>>( &availableTowers))
{
	availableTowers[0] -> render(target);
	target.draw(price1);
}

void Shop_Window::handle_event(int mousePosX, int mousePosY)
{

}