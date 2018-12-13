#include "constants.h"
#include "Effect.h"
#include "Events.h"
#include "Game_State.h"
#include "Resources.h"
#include "Sidebar.h"
#include "Tower.h"
#include <cstdlib>
#include <memory>

#include "Manager.h"
#include <iostream>
#include <sstream>

using namespace sf;
using std::string;


Game_State::Game_State(string level)
{
    if(!gameOverlayTexture.loadFromFile("resources/images/overlay.png"))
    {
        throw Game_StateError{"Couldn't load overlay texture"};
    }
    gameOverlay.setTexture(gameOverlayTexture);


    availableTowers.push_back(
    	make_shared<MinigunTower>(static_cast<double>(sidebarPosX + 3 * mapBorderOffset),
    		static_cast<double>(156 + mapBorderOffset)));
    availableTowers.push_back(
    	make_shared<MissileTower>(static_cast<double>(sidebarPosX + 3 * mapBorderOffset),
    		static_cast<double>(156 + mapBorderOffset)));
    availableTowers.push_back(
    	make_shared<LaserTower>(static_cast<double>(sidebarPosX + 3 * mapBorderOffset),
    		static_cast<double>(156 + mapBorderOffset)));
                availableTowers.push_back(
    	make_shared<MinigunTower>(static_cast<double>(sidebarPosX + 3 * mapBorderOffset),
    		static_cast<double>(156 + mapBorderOffset)));
    availableTowers.push_back(
    	make_shared<MissileTower>(static_cast<double>(sidebarPosX + 3 * mapBorderOffset),
    		static_cast<double>(156 + mapBorderOffset)));
    availableTowers.push_back(
    	make_shared<LaserTower>(static_cast<double>(sidebarPosX + 3 * mapBorderOffset),
    		static_cast<double>(156 + mapBorderOffset)));


    gameMap = make_unique<Map>(level);
    gameResources = make_unique<Resources>(100, 100);
    gameSidebar = make_unique<Sidebar>(sidebarPosX, availableTowers);
    wavePump = make_unique<WavePump>();

    shptr<Tile> tempTile = gameMap->getSpawnPoint();
    Monster * tempMonster{};
    tempMonster = new BrownRabbit(tempTile, 0);    
    wavePump->addMonsterType(*tempMonster);
    tempMonster = new Squirrel(tempTile, 0);
    wavePump->addMonsterType(*tempMonster);
    tempMonster = new Fox(tempTile, 0);
    wavePump->addMonsterType(*tempMonster);
    tempMonster = new WhiteRabbit(tempTile, 0);
    wavePump->addMonsterType(*tempMonster);
    tempMonster = nullptr;

    wavePump->readFromFile("test3");



}

void Game_State :: handle_event (Event event)
{
    if ( event.type == Event::MouseButtonReleased )
    {
        auto mouse { event.mouseButton };
        if ( mouse.button == Mouse::Button::Left )
        {
        	if (mouse.x > sidebarPosX)
        	{
        		gameSidebar -> handle_event(mouse.x, mouse.y, gameResources, availableTowers);
        	}
            else if (pause)
            {
                // Go back to main menu
                go_back = true;
            }
            else if (mapScreen.contains(mouse.x, mouse.y))
            {
                // Click on map
                gameMap->handle(event, monsters, towers, gameResources);
            }
        }
        if (gameOver)
        {
            go_back = true;
        }
    }

    if (event.type == sf::Event::KeyPressed)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && !pauseButtonPressed)
        {
            pause = !pause;
            pauseButtonPressed = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B) && !bloodButtonPressed)
        {
            blood = !blood;
            bloodButtonPressed = true;
        }
        /*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            projectiles.push_back(make_shared<Anvil>(sf::Mouse::getPosition().x,0, 0, 1));
        }
        */
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        pauseButtonPressed = false;
        bloodButtonPressed = false;
    }

    // Send the event to the base class (see Go_Back_State.h)
    Go_Back_State::handle_event (event);
}

Game_Event Game_State :: update ()
{
    // Only update when game not paused
    if (!pause && !gameOver)
    {
        // Update map
        gameMap->update();

        // Update sidebar
        gameSidebar->update(gameResources, availableTowers);

        // Update blood effect
        for (auto & b : bloodFX)
        {
            b->update();
        }

        // Update towers
        for (auto & t : towers)
        {
            t->update(monsters, projectiles);
        }

        // Update projectiles
        for (auto & p : projectiles)
        {
            p->update(monsters);
        }

        // Update Resouces
        if (gameResources->getHP() <= 0)
            gameOver = true;

        // Update monsters
        for (auto & m : monsters)
        {
            m->update();

            if (m->isBleeding() && (rand() % 100) <= 50)
                bloodFX.push_back(make_unique<Bleed> (m->getX(), m->getY()));
        }

	//Update wavePump
	wavePump->update(monsters);
    }

    cleanup();
    /*
    if (gameOver)
    {
        gameOver = false;
        return Game_Event::create<Switch_State> (
            move (std::make_unique<Menu_State>));
    }
    
    // Let the base class perform it's update
    */
    return Go_Back_State::update ();
}

void Game_State :: render (RenderTarget & target)
{
    // Render map
    gameMap->render(target);

    // Render sidebar
    gameSidebar->render(target, gameResources, availableTowers);

    // Render blood
    if (blood)
    {
        for (auto & b : bloodFX)
        {
            b->render(target);
        }
    }

    // Render projectiles
    for (auto & p : projectiles)
    {
        p->render(target);
    }

    // Render towers
    for (auto & t : towers)
    {
        t->render(target);
    }

    // Render monsters
    for (auto & m : monsters)
    {
        m->render(target);
    }

    target.draw(gameOverlay);

    // Render pause-screen <-- temporär pause-text
    if (pause)
    {
        Text text { "Paused",
             Font_Manager::load ("resources/fonts/font.ttf"),
             30 };
        Text text2 { "Paused",
             Font_Manager::load ("resources/fonts/font.ttf"),
             30 };

        text.setPosition (250, 300);
        text2.setPosition (252, 302);
        text2.setFillColor(Color::Black);
    
        target.draw (text2);
        target.draw (text);
    }

    if (gameOver)
    {
        Text text { "Game over",
             Font_Manager::load ("resources/fonts/font.ttf"),
             30 };
        Text text2 { "Game over",
             Font_Manager::load ("resources/fonts/font.ttf"),
             30 };

        text.setPosition (250, 300);
        text2.setPosition (252, 302);
        text2.setFillColor(Color::Black);
    
        target.draw (text2);
        target.draw (text);
    }
}

void Game_State :: cleanup ()
{
    // Clean projectiles out of bounds
    for (unsigned i = 0; i < projectiles.size(); )
    {   
        auto bounds {projectiles[i]->getBounds()};
        
        if (!mapScreen.intersects(bounds))
            projectiles.erase(projectiles.begin() + i);
        else
            ++i;    
    }

    // Clean up blood effects
    for (unsigned b = 0; b < bloodFX.size(); )
    {
        if (bloodFX[b]->checkRemove())
            bloodFX.erase(bloodFX.begin() + b);
        else
            b++;
    }

    // Clean up monsters
    for (unsigned i = 0; i < monsters.size(); )
    {   
        if (monsters[i]->isDead())
        {
            // Spawn some blood and erase
            if (monsters[i]->shallLoseHP())
                gameResources->changeHP(- monsters[i]->getHPLoss());
            else
                gameResources->changeMoney(monsters[i]->getBounty());
            
            if (monsters[i]->getHealth() <= 0)
                bloodFX.push_back(make_unique<Blood> (monsters[i]->getX(), monsters[i]->getY()));
            monsters.erase(monsters.begin() + i);
        }
        else
            i++;
    }
/*
    for ( auto it { std::begin (projectiles) }; it != std::end (projectiles); )
    {
        // get the global bounds of our current ball
        
	auto bounds { it -> getBounds () };
        // get a rectangle representing the screen
	FloatRect screen { mapBorderOffset, mapBorderOffset, mapBorderOffset + xTilesMax * tileWidth,
                                                         mapBorderOffset + yTilesMax * tileWidth };
	if ( !screen.intersects (bounds) )
	    it = projectiles.erase (it);
	else
	    ++it;
    }
    */
}
