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
#include "WavePump.h"
#include <vector>
#include <memory>
#include <string>

/*
 *  This class represents the "game".
 * 
 *  Game interface borders made from "MageCity":
 *  https://opengameart.org/content/mage-city-arcanos
 * 
 *  Map tiles made from "Basic map 32x32" by Silver IV:
 *  https://opengameart.org/content/basic-map-32x32-by-silver-iv
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
    bool gameOver {false};              // Sub state "game over"
    bool pause {false};                 // Sub state "pause"
    bool pauseButtonPressed {false};
    bool blood {true};                  // Blood effects on/off
    bool bloodButtonPressed {false};

    // Game managing objects
    ptr<Map> gameMap {};
    ptr<Resources> gameResources {};
    ptr<Sidebar> gameSidebar {};
    ptr<WavePump> wavePump {};

    // Game object containers
    std::vector<shptr<Monster>> monsters {};
    std::vector<shptr<Tower>> towers {};
    std::vector<shptr<Tower>> availableTowers{};
    std::vector<shptr<Projectile>> projectiles {};
    std::vector<ptr<Effect>> bloodFX {};

    // Graphical stuff
    sf::Texture gameOverlayTexture {};
    sf::Sprite gameOverlay {};
    sf::RectangleShape rectangle{};
    sf::Text text;
    sf::Text menuText;
    sf::FloatRect mapScreen { mapBorderOffset, mapBorderOffset,
                              xTilesMax * tileWidth,
                              yTilesMax * tileWidth};

    void cleanup ();    // Cleans up projectiles out of bounds
};
