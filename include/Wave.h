#ifndef WAVE_H
#define WAVE_H

#include "Monster.h"
#include "Tile.h"
#include <queue>
#include <memory>
#include "defs.h"

class Wave
{
    shptr<Tile> spawnTile;
public:
    Wave(shptr<Tile>init_spawnTile);
};

#endif    
