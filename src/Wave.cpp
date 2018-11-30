#include "Wave.h"
#include <utility>

Wave::Wave(shptr<Tile> init_spawnTile): spawnTile{std::move(init_spawnTile)} 
{
    
}
     
