#ifndef WAVE_H
#define WAVE_H

#include "Monster.h"
#include "Tile.h"
#include <queue>
#include <memory>
#include <istream>
#include <string>
#include "defs.h"

class WaveError : public std::logic_error
{
    using std::logic_error::logic_error;
};

class Wave
{
public:
    Wave(); //lägg kanske till vilo intervallet
    Wave(shptr<Tile> init_spawnTile, float init_cooldown,
	 int init_monsterLevel, std::istream init_monsterFeed);
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
    int monsterLevel;
    std::queue<shptr<Monster>> monsterQueue{};
}; 

#endif    
