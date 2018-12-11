#pragma once

/**
 * Shop_Window.h
 * *
 * Header file for Shop_Window.cpp.
 */


#include "constants.h"
#include "defs.h"
#include "Map.h"
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
	void render(sf::RenderTarget &target, std::vector<shptr<Tower>>(&availableTowers));

private:
	int x;
	int y;

	sf::Text price1 {"", Font_Manager::load("resources/fonts/font.ttf"),
			H4};
};