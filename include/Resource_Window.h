#pragma once

/**
 * Resource_Window.h
 * *
 * Header file for Resource_Window.cpp.
 *
 * WARNING: Needs to be subclass to a pure virtual Sidebar_Window in order to
 * dynamic cast in the event handler)
 *
 * IDEA: Make errors subclass of SidebarWindowError?
 */

#include "Resources.h"
#include "constants.h"
#include "defs.h"
#include "Map.h"
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <memory>

#include "Manager.h"

class Resource_Window_Error : public std::logic_error
{
	using std::logic_error::logic_error;
};

class Resource_Window
{
public:
	Resource_Window(int xPos);
	~Resource_Window();
	
	void update(ptr<Resources> const & gameResources);
	void render(sf::RenderTarget &target);

private:
	int x;
	int y;

	sf::Texture HPTexture {};
	sf::Sprite HPSprite {};
	sf::Text HPText {"", Font_Manager::load("resources/fonts/font.ttf"),
			4 * static_cast<unsigned int>(mapBorderOffset)};

	sf::Texture moneyTexture {};
	sf::Sprite moneySprite {};
	sf::Text moneyText {"", Font_Manager::load("resources/fonts/font.ttf"),
			   4 * static_cast<unsigned int>(mapBorderOffset)};
	//sf::Text waveText;
};