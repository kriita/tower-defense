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
    WavePump(float _spawnCooldown = .5f, float _intermissionSpan = 7.f);
    ~WavePump() = default;
    void addMonsterType(Monster);
    void update(std::vector<shptr<Monster>> &, ptr<Resources> &);
    void readFromFile(std::string name, 
		      std::string path = "resources/waves/",
		      std::string suffix = ".w");
    int getWave() const;
    int getIntermissionCountdown() const;
    bool empty() const;
    void skipIntermission();
    
private:
    bool readyToSpawn() const;
    void updateIntermission();
    void intermission();
    void updateActive(std::vector<shptr<Monster>> const &);
    void pushMonster(std::string word, int multiple = 1);

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
    unsigned monsterLevel{};
};

#endif
