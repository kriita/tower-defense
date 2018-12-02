#include "constants.h"
#include "Events.h"
#include "Game_State.h"
#include "Resources.h"
#include "Tower.h"
#include <memory>

#include "Manager.h"
#include <iostream>

using namespace sf;

Game_State::Game_State()
{
    if(!gameOverlayTexture.loadFromFile("resources/images/overlay.png"))
    {
        throw Game_StateError{"Couldn't load overlay texture"};
    }
    gameOverlay.setTexture(gameOverlayTexture);

    gameMap = make_unique<Map>("map.dat");
    gameResources = make_unique<Resources>(100, 100);
}

void Game_State :: handle_event (Event event)
{
    if ( event.type == Event::MouseButtonReleased )
    {
        auto mouse { event.mouseButton };
        if ( mouse.button == Mouse::Button::Left )
        {
            if (pause)
            {
                // Go back to main menu
                go_back = true;
            }
            else
            {
                shptr<Tile> tmpTile {gameMap->getTile(static_cast<int>((mouse.x - mapBorderOffset) / tileWidth),
                                                      static_cast<int>((mouse.y - mapBorderOffset) / tileWidth))};
                if (tmpTile->checkPlaceable())
                {
                    towers.push_back(make_shared<MinigunTower> (tmpTile->getX(), tmpTile->getY()));
                    tmpTile->switchPlaceable();
                }
                else 
                {
                    monsters.push_back(make_shared<Orc> (gameMap->getSpawnPoint()));
                }

                //projectiles.push_back(make_shared<Anvil>((event.mouseButton).x, 0, 0, 1));
            }
        }
    }

    if (event.type == sf::Event::KeyPressed)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && !pauseButtonPressed)
        {
            pause = !pause;
            pauseButtonPressed = true;
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
    }

    // Send the event to the base class (see Go_Back_State.h)
    Go_Back_State::handle_event (event);
}

Game_Event Game_State :: update ()
{
    // Only update when game not paused
    if (!pause)
    {
        // Update map
        gameMap->update();

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

        // Update monsters
        for (auto & m : monsters)
        {
            m->update();
            //cout << m->isDead() << m->getHealth() << endl;
        }

        for (unsigned i = 0; i < monsters.size(); )
        {   
            if (monsters[i]->isDead())
                monsters.erase(monsters.begin() + i);
            else
                i++;
        }
    }

    cleanup();

    // Let the base class perform it's update
    return Go_Back_State::update ();
}

void Game_State :: render (RenderTarget & target)
{
    // Render map
    gameMap->render(target);

    // Render towers
    for (auto & t : towers)
    {
        t->render(target);
    }

    // Render projectiles
    for (auto & p : projectiles)
    {
        p->render(target);
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
}

void Game_State :: cleanup ()
{
    // Clean projectiles out of bounds
    for (unsigned i = 0; i < projectiles.size(); )
    {   
        auto bounds {projectiles[i]->getBounds()};
        FloatRect mapScreen { mapBorderOffset, mapBorderOffset,
                           mapBorderOffset + xTilesMax * tileWidth,
                           mapBorderOffset + yTilesMax * tileWidth };
        if (!mapScreen.intersects(bounds))
            projectiles.erase(projectiles.begin() + i);
        else
            ++i;    
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