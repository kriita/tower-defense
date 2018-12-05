#ifndef WAVE_H
#define WAVE_H

#include "Monster.h"
#include "Tile.h"
#include <queue>
#include <memory>
#include "defs.h"

class Wave
{
public:
    Wave();
    ~Wave() = default;
    void setSpawnTile(shptr<Tile> init_spawnTile);
    shptr<Monster> spawnMonster();
    bool timeToSpawn();

private:
    ptr<Monster> monster_pointer;
    shptr<Tile> spawnTile;
    sf::Clock clock;
    float cooldown{2.f};
};

#endif    
