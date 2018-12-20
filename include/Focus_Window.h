#pragma once

/**
 * Focus_Window.h
 * *
 * Header file for Focus_Window.cpp.
 * 
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

class Focus_Window_Error : public std::logic_error
{
	using std::logic_error::logic_error;
};

class Focus_Window
{
public:
	Focus_Window(int xPos);
	~Focus_Window() = default;

	void update();
	void render(sf::RenderTarget &target, ptr<Resources>(&gameResources));
	void handle_event(int mousePosX, int mousePosY, ptr<Resources>(&gameResources));

private:
	int x {};
	int y {};

	std::vector<shptr<sf::Rect<int>>> upgrades {};
	std::vector<shptr<sf::Text>> prices {};
	std::vector<shptr<sf::Sprite>> upgradeIcons{};
	std::vector<shptr<sf::Sprite>> upgradeCompleteIcons{};

	sf::Texture upgradeIconTexture {};
	sf::Texture upgradeCompleteIconTexture {};
};