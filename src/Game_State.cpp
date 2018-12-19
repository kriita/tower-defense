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
    : text { "", Font_Manager::load ("resources/fonts/font.ttf"), 24},
  menuText {"Main menu", Font_Manager::load ("resources/fonts/font.ttf"), 24}
{
    if(!gameOverlayTexture.loadFromFile("resources/images/overlay.png"))
    {
        throw Game_StateError{"Couldn't load overlay texture"};
    }
    gameOverlay.setTexture(gameOverlayTexture);

    // Available towers for shop
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
    	make_shared<SlowTower>(static_cast<double>(sidebarPosX + 3 * mapBorderOffset),
    		static_cast<double>(156 + mapBorderOffset)));

    // Create game managing objects
    gameMap = make_unique<Map>(level);
    gameResources = make_unique<Resources>(100, 100);
    gameSidebar = make_unique<Sidebar>(sidebarPosX, availableTowers);
    wavePump = make_unique<WavePump>(1.f, 3.f);

    // Monster origins for wave
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
    tempMonster = new Hamster(tempTile, 0);
    wavePump->addMonsterType(*tempMonster);
    tempMonster = new GrayRacoon(tempTile, 0);
    wavePump->addMonsterType(*tempMonster);
    tempMonster = new Hedgehog(tempTile, 0);
    wavePump->addMonsterType(*tempMonster);
    tempMonster = new BrownRacoon(tempTile, 0);
    wavePump->addMonsterType(*tempMonster);
    tempMonster = nullptr;

    wavePump->readFromFile(level);
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
                // Click on sidebar
        		gameSidebar -> handle_event(mouse.x, mouse.y, gameResources, availableTowers, wavePump);
        	}
            else if (mapScreen.contains(mouse.x, mouse.y))
            {
                // Click on map
                gameMap->handle(event, monsters, towers, gameResources);
            }
        }
        if ((gameOver || pause) 
            && (mouse.x > 240) && (mouse.x < 240 + 140)
            && (mouse.y > 310) && (mouse.y < 310 + 40))
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
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
	    wavePump->skipIntermission();
        }
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        pauseButtonPressed = false;
        bloodButtonPressed = false;
    }

    Go_Back_State::handle_event (event);
}

Game_Event Game_State :: update ()
{
    // Update only when game not paused
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
	    wavePump->update(monsters, gameResources);
    }

    // Pause/game over text
    if (pause)
    {
        text.setString("Paused");
        text.setPosition (255, 250);
    }
    else if (gameOver)
    {
        text.setString("Game over");
        text.setPosition (235, 250);
    }

    text.setFillColor(Color::White);
    text.setOutlineColor(Color::Black);
    text.setOutlineThickness(3);
    
    rectangle.setSize(sf::Vector2f(139, 40));
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setFillColor(Color::Red);
    rectangle.setOutlineThickness(2);
    rectangle.setPosition(230, 310);

    menuText.setPosition (235, 313);
    menuText.setFillColor(Color::White);
    menuText.setOutlineColor(Color::Black);
    menuText.setOutlineThickness(3);

    cleanup();

    return Go_Back_State::update ();
}

void Game_State :: render (RenderTarget & target)
{
    // Render map
    gameMap->render(target);

    // Render blood
    if (blood)
    {
        for (auto & b : bloodFX)
        {
            b->render(target);
        }
    }

    // Render monsters
    for (auto & m : monsters)
    {
        m->render(target);
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

    // Render sidebar
    gameSidebar->render(target, gameResources, availableTowers);

    // Render overlay
    target.draw(gameOverlay);

    // Render pause/game over screen
    if (pause)
    {
        target.draw(rectangle);
        target.draw(text);
        target.draw(menuText);
    }
    else if (gameOver)
    {
        target.draw(rectangle);
        target.draw(text);
        target.draw(menuText);
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
}
