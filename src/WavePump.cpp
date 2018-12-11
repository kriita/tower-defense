#include "WavePump.h"

WavePump::WavePump()
    :waveCount{1}, monsterLevelRoof{5}, monsterLevelFloor{1}, 
    spawnCooldown{0.5f}, clock{}, monsterTypes{}, monsterSequence{7},
    monsterSequenceIndex{0}//, spawnTile{nullptr}
{

}

/*void WavePump::setSpawnTile(shptr<Tile> tile)
{
    spawnTile = std::move(tile);
}*/

void WavePump::addMonsterType(shptr<Monster> monster)
{
    monsterTypes.push_back(monster);
}
