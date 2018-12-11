#ifndef WAVEPUMP_H
#define WAVEPUMP_H

#include "defs.h"
#include "Monster.h"
#include "Tile.h"

#include <vector>
#include <memory>
#include <iostream>

//notes: vore trevligt att ha monsterVectorn som en pekare här.
//trevligt också om monster.getType var virutal kom inte åt den i ett test

class WavePump
{
public:
    WavePump();
    ~WavePump() = default;
    //void setSpawnTile(shptr<Tile>);
    void addMonsterType(shptr<Monster>);
    void testing() 
    {
	for (unsigned int i{0}; i < monsterTypes.size(); i++)
	{
	    std::cout << monsterTypes[i] << std::endl;
	}
    }
    
private:
    int waveCount{};
    int monsterLevelRoof{};
    int monsterLevelFloor{};
    float spawnCooldown{};
    sf::Clock clock{};
    std::vector<shptr<Monster>> monsterTypes{};
    std::vector<shptr<Monster>> monsterSequence{};
    int monsterSequenceIndex{};
    //shptr<Tile> spawnTile{};
    
};

#endif
