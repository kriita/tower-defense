#include "defs.h"
#include "Effect.h"
#include "Go_Back_State.h"
#include "Map.h"
#include "Monster.h"
#include "Projectile.h"
#include "Resources.h"
#include "Sidebar.h"
#include "Tile.h"
#include "Tower.h"
#include "Wave.h"
#include <vector>
#include <memory>
#include <string>

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

class Game_StateError : public std::logic_error
{
    using std::logic_error::logic_error;
};

class Game_State : public Go_Back_State
{
public:

    Game_State (std::string level);

    void handle_event (sf::Event event) override;
    Game_Event update () override;
    void render (sf::RenderTarget & target) override;

private:

    bool pause {false};
    bool pauseButtonPressed {false};
    bool blood {true};
    bool bloodButtonPressed {false};

    ptr<Map> gameMap {};
    ptr<Resources> gameResources {};
    ptr<Sidebar> gameSidebar {};
    ptr<Wave> wave {};

    //shptr<Monster> focusMonster {};
    //shptr<Tower> focusTower {};

    std::vector<shptr<Monster>> monsters {};
    std::vector<shptr<Tower>> towers {};
    std::vector<shptr<Tower>> availableTowers{};
    std::vector<shptr<Projectile>> projectiles {};

    std::vector<ptr<Effect>> bloodFX {};

    sf::Texture gameOverlayTexture {};
    sf::Sprite gameOverlay {};

    sf::FloatRect mapScreen { mapBorderOffset, mapBorderOffset,
                              xTilesMax * tileWidth,
                              yTilesMax * tileWidth};

    /*
     * Remove all balls which are no longer visible on the
     * screen.
     */
    void cleanup ();

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
