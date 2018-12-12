#include "Game.h"
#include "constants.h"
#include <SFML/Audio.hpp>

/*
 * If you want to study the code, it is recommended that
 * you start looking in Game.h.
 */

int main ()
{

    sf::Music music;
    if (!music.openFromFile("resources/sound/intermission.ogg"))
	return -1; // error
    music.play();
    
    // We only want the main function to start the Game and then run it
    Game g { gameTitle, screen_width, screen_height };
    g.start ();
}
