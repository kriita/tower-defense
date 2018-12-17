#ifndef WAVEPUMP_H
#define WAVEPUMP_H

#include "defs.h"
#include "Monster.h"
#include "Tile.h"
#include "Resources.h"
#include <vector>
#include <memory>
#include <cstdlib>
#include <iostream>
#include <map>
#include <queue>
#include <string>

class WavePumpError: public std::logic_error
{
    using std::logic_error::logic_error;
};

class WavePump
{
public:
    WavePump(float _spawnCooldown = 0.f, float _intermissionSpan = 7.f);
    ~WavePump() = default;
    bool readyToSpawn();
    void updateIntermission();
    void addMonsterType(Monster);
    void update(std::vector<shptr<Monster>> &, ptr<Resources> &);
    void intermission();
    void pushMonster(std::string word, int multiple = 1);
    void readFromFile(std::string name, 
		      std::string path = "resources/waves/",
		      std::string suffix = ".w");
    void updateActive(std::vector<shptr<Monster>> const &);
    std::string getMonsterTypes(); //test function
    int getWave();
    int getIntermissionCountdown();
    float getSpawnCooldown();
    bool empty();
    void skipIntermission();
    void setSpawnCooldown(float);
    
private:
    std::map<std::string, Monster> monsterTypes{};
    std::queue<std::queue<shptr<Monster>>> waves{};
    std::queue<int> waveMonsterAmount{};
    sf::Clock clock{};
    sf::Clock intermissionClock{};
    float spawnCooldown{};
    float intermissionSpan{};
    int totalWaveAmount{};
    bool active{}; //no monster on the playing feild.
    bool activeIntermission{};
};

#endif
