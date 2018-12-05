#include "Wave.h"
#include <utility>

void Wave::setSpawnTile(shptr<Tile> init_spawnTile)
{
    spawnTile = std::move(init_spawnTile);    
}

shptr<Monster> Wave::spawnMonster()
{
    clock.restart();
    return std::make_shared<Orc>(spawnTile, 2);
}
     
bool Wave::timeToSpawn()
{
    return clock.getElapsedTime().asSeconds() > cooldown;
}
