#include "Go_Back_State.h"
#include "map.h"
#include "tile.h"
#include "tower.h"
#include "monster.h"

#include <vector>
#include <memory>

/*
 * This class represents the "game".
 *
 * It is a simple program where a ball appears wherever
 * the user has clicked with the mouse. This ball
 * is assigned a random velocity and will begin moving
 * according to that velocity.
 *
 * This class serves as an example of a state, but also
 * of how the various functions of the State class can
 * be used to get moving objects in the game.
 *
 * It also demonstrates how to remove objects from
 * the game in a safe way, as to avoid memory leaks.
 */
class Game_State : public Go_Back_State
{
public:

    Game_State ();

    void handle_event (sf::Event event) override;
    Game_Event update () override;
    void render (sf::RenderTarget & target) override;

private:

    Map gameMap {"map.dat"};

    std::vector<shptr<Monster>> monsters {};
    std::vector<shptr<Tower>> towers {};

    sf::Texture gameOverlayTexture;
    sf::Sprite gameOverlay {};

    /*
     * Remove all balls which are no longer visible on the
     * screen.
     */
    //void cleanup ();

    /*
     * Spritesheet from which the graphics for all balls
     * are taken.
     */
    //Spritesheet sheet { "resources/images/balls.png", 64, 64 };

    /*
     * A collection which contains all balls that are currently
     * visible on the screen (see Ball.h).
     */
    //std::vector<Ball> balls { };
    
};