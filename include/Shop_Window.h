#pragma once

/**
 * Shop_Window.h
 * *
 * Header file for Shop_Window.cpp.
 */


#include "constants.h"
#include "defs.h"
#include "Map.h"
#include "Resources.h"
#include "Tower.h"

#include <memory>
#include <SFML/Graphics.hpp>
#include <stdexcept>

#include "Manager.h"

class Shop_Window_Error : public std::logic_error
{
	using std::logic_error::logic_error;
};

class Shop_Window
{
public:
	Shop_Window(int xPos);
	~Shop_Window() = default;

	void update(std::vector<shptr<Tower>>(& availableTowers));
	void render(sf::RenderTarget &target, ptr<Resources>(&gameResources), std::vector<shptr<Tower>>(&availableTowers));
	void handle_event(int mousePosX, int mousePosY, ptr<Resources>(&gameResources), std::vector<shptr<Tower>>(&availableTowers));

private:
	int x {};
	int y {};

//	sf::Text price1 {"", Font_Manager::load("resources/fonts/font.ttf"), H4};
	std::vector<shptr<sf::Rect<int>>> items {};
	std::vector<shptr<sf::Text>> prices {};

	sf::Text buildModeText {"BUILD MODE", Font_Manager::load("resources/fonts/font.ttf"), H4};
};