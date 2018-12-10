#ifndef WAVE_H
#define WAVE_H

#include "Monster.h"
#include "Tile.h"
#include <queue>
#include <memory>
#include <istream>
#include "defs.h"

class Wave
{
public:
    Wave(); //lägg kanske till vilo intervallet
    ~Wave() = default;
    void setSpawnTile(shptr<Tile> init_spawnTile);
    void readWaveData(std::string fileName);
    shptr<Monster> spawnMonster();
    bool timeToSpawn();
    bool empty();
    std::istream& operator>>(std::istream& recruits);
    
private:
    void pushMonster(int, int);
    shptr<Tile> spawnTile;
    sf::Clock clock;
    float cooldown;
    std::queue<shptr<Monster>> monsterQueue{};
}; 

#endif    
