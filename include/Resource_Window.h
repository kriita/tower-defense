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

#include "constants.h"
#include "defs.h"
#include "Map.h"
#include "Resources.h"
#include "WavePump.h"

#include <memory>
#include <SFML/Graphics.hpp>
#include <stdexcept>

#include "Manager.h"

class Resource_Window_Error : public std::logic_error
{
	using std::logic_error::logic_error;
};

class Resource_Window
{
public:
	Resource_Window(int xPos);
	~Resource_Window() = default;
	
	void update(ptr<Resources> (& gameResources));
	void render(sf::RenderTarget &target);
	void handle_event(int mousePosX, int mousePosY, ptr<WavePump>(&wavePump), ptr<Resources>(&gameResources));

private:
	int x;
	int y;

	sf::Texture HPTexture {};
	sf::Sprite HPSprite {};
	sf::Text HPText {"", Font_Manager::load("resources/fonts/font.ttf"),
			H3};

	sf::Texture moneyTexture {};
	sf::Sprite moneySprite {};
	sf::Text moneyText {"", Font_Manager::load("resources/fonts/font.ttf"),
			   H3};

	sf::Text waveText {"", Font_Manager::load("resources/fonts/font.ttf"),
			H4};

	shptr<sf::Rect<int>> nextWaveBtn {};

	sf::Texture nextWaveTexture {};
	sf::Sprite nextWaveSprite {};
};