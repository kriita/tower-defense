#ifndef WAVEPUMP_H
#define WAVEPUMP_H

#include "defs.h"
#include "Monster.h"
#include "Tile.h"

#include <vector>
#include <memory>
#include <cstdlib>
#include <iostream>
#include <ctime>

//notes: vore trevligt att ha monsterVectorn som en pekare här.
//trevligt också om monster.getType var virutal kom inte åt den i ett test
//en kopieringskonstructor till monster vore bra!

class WavePumpError: public std::logic_error
{
    using std::logic_error::logic_error;
};

class WavePump
{
public:
    WavePump();
    ~WavePump() = default;
    void setSpawnTile(shptr<Tile>);
    void addMonsterType(shptr<Monster>);
    void scrambleMonsterSequence();
    void iterateIndex();
    bool readyToSpawn();
    shptr<Monster> spawnMonster();
    
private:
    int waveCount{};
    int spawnCount{};
    int monsterLevelRoof{};
    int monsterLevelFloor{};
    float spawnCooldown{};
    sf::Clock clock{};
    std::vector<shptr<Monster>> monsterTypes{};
    std::vector<shptr<Monster>> monsterSequence{};
    int monsterSequenceIndex{};
    shptr<Tile> spawnTile{};
    
};

#endif
