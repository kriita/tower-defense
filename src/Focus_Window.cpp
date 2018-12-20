/**
 * Focus_Window.cpp
 * *
 * Defines the behavior of the focus window in the sidebar.
 * Height: 216
 */

#include "Focus_Window.h"
#include "Resources.h"
#include "Map.h"
#include "constants.h"
#include "defs.h"
#include "Tower.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

Focus_Window::Focus_Window(int xPos)
: x {xPos}, y {356}
{
	// Generate text that will describe each upgrade button
	// 
	// The upgrade names could be made more modular if they were
	// stored in the individual towers as a vector, so that the
	// upgrade names would reflect the available upgrade for that
	// specific tower. For example, see the slow tower's upgrades.
	// This would result in a for-loop here. Similar mindset can be
	// applied to the upgrade functions mentioned below.

	prices.push_back(std::make_shared<sf::Text>
		("Upgrade Range", Font_Manager::load("resources/fonts/font.ttf"), BODY*2/3));

	prices.push_back(std::make_shared<sf::Text>
		("Upgrade Attack Power", Font_Manager::load("resources/fonts/font.ttf"), BODY*2/3));

	prices.push_back(std::make_shared<sf::Text>
		("Upgrade Fire Rate", Font_Manager::load("resources/fonts/font.ttf"), BODY*2/3));
	
	if(!upgradeIconTexture.loadFromFile("resources/images/upgradeArrow.png"))
    	{
        	throw Focus_Window_Error{"Couldn't load upgrade arrow texture"};
    	}
    	if(!upgradeCompleteIconTexture.loadFromFile("resources/images/star_t.png"))
    	{
        	throw Focus_Window_Error{"Couldn't load upgrade complete arrow texture"};
    	}

    	// loop trough setting positions of upgrade objects, and generating buttons
	for (unsigned int i = 0; i < 141; i += 70)
	{
		upgradeIcons.push_back(std::make_shared<sf::Sprite>(upgradeIconTexture));
		upgradeCompleteIcons.push_back(std::make_shared<sf::Sprite>(upgradeCompleteIconTexture));

		upgradeIcons[i / 70] -> setPosition(
			static_cast<double>(x + 24),
			static_cast<double>(y + 28 + i*2/3));

		upgradeCompleteIcons[i / 70] -> setPosition(
			static_cast<double>(x + 24),
			static_cast<double>(y + 28 + i*2/3));

		upgrades.push_back(std::make_shared<sf::Rect<int>>(
			static_cast<int>(x + 24),
    			static_cast<int>(y + 28 + i*2/3),
    			32, 32));

		prices[i / 70] -> setPosition(x + 24, y + 60 + i*2/3);
	}
}

void Focus_Window::render(sf::RenderTarget &target, ptr<Resources>(&gameResources))
{
	if ((gameResources -> getFocusTower()) && !(gameResources -> getBuildMode()))
	{
		// Render different icons depending on if there are upgrades left.
		// Doesn't visualize in-game due to the upgrade buttons
		// being broken, but replacing upgradeIcons[i] with
		// upgradeCompleteIcons[i] worked and proved the testing concept.
		// The following 3 can if-clauses can also be made more modular
		// by compiling the functions into a vector and running a for-loop.

		if (gameResources -> getFocusTower() -> getRangeUpgradePrice() == 0)
			target.draw(*(upgradeCompleteIcons[0]));
		else
		{
			target.draw(*(upgradeIcons[0]));
		}

		if (gameResources -> getFocusTower() -> getAttackPowerUpgradePrice() == 0)
			target.draw(*(upgradeCompleteIcons[1]));
		else
		{
			target.draw(*(upgradeIcons[1]));
		}

		if (gameResources -> getFocusTower() -> getFireRateUpgradePrice() == 0)
			target.draw(*(upgradeCompleteIcons[2]));
		else
		{
			target.draw(*(upgradeIcons[2]));
		}
		
		// draw price texts
		for (unsigned int i = 0; i < prices.size(); ++i)
		{
			target.draw(*(prices[i]));
		}
	}
}

// Upgrades different aspects of the tower depending on which upgrade button is pushed.

void Focus_Window::handle_event(int mousePosX, int mousePosY, ptr<Resources>(&gameResources))
{
	if (!((gameResources -> getFocusTower()) == nullptr))
	{
		if (((upgrades[0] -> contains(mousePosX, mousePosY)) &&
		    !(gameResources -> getFocusTower() -> getRangeUpgradePrice() == 0) &&
		    (gameResources -> getFocusTower() -> getRangeUpgradePrice()) <= (gameResources -> getMoney())))
		{
			gameResources -> changeMoney(-(gameResources -> getFocusTower() -> getRangeUpgradePrice()));
			gameResources -> getFocusTower() -> upgradeRange();
		}

		if (upgrades[1] -> contains(mousePosX, mousePosY) &&
		    (!(gameResources -> getFocusTower() -> getAttackPowerUpgradePrice() == 0)) &&
		    (gameResources -> getFocusTower() -> getAttackPowerUpgradePrice() <= gameResources -> getMoney()))
		{
			gameResources -> changeMoney(-(gameResources -> getFocusTower() -> getAttackPowerUpgradePrice()));
			gameResources -> getFocusTower() -> upgradeAttackPower();
		}

		if ((upgrades[2] -> contains(mousePosX, mousePosY)) &&
		    !(gameResources -> getFocusTower() -> getFireRateUpgradePrice() == 0) &&
		    (gameResources -> getFocusTower() -> getFireRateUpgradePrice() <= gameResources -> getMoney()))
		{
			gameResources -> changeMoney(-(gameResources -> getFocusTower() -> getFireRateUpgradePrice()));
			gameResources -> getFocusTower() -> upgradeFireRate();
		}
	}
}