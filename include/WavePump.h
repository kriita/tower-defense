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

/*/
 *WavePump
 *
 *
 *
 *
 *
 *
 *
/*/

class WavePumpError: public std::logic_error
{
    using std::logic_error::logic_error;
};

class WavePump
{
public:
    WavePump(float _intermissionSpan = 14.f);
    ~WavePump() = default;
    void skipIntermission();
    void addMonsterType(Monster);
    void readFromFile(std::string name, 
		      std::string path = "resources/waves/",
		      std::string suffix = ".w");
    void prepare(ptr<Resources> &);
    void intermission();
    void pump(std::vector<std::shared_ptr<Monster>> &);
    void update(std::vector<shptr<Monster>> &, ptr<Resources> &);

    int getWave() const {return currentWave; }
    bool watingWavesEmpty() const {return watingWaves.empty(); }
    bool activeWavesEmpty() const {return activeWaves.empty(); }
    bool empty() const {return watingWavesEmpty() && activeWavesEmpty(); }

private:
    void pushMonster(std::string type);
    void pushMonsterSequence(std::vector<std::string> sequence, int multi);
    
    //the containers sould probably have been their own classes,
    //lots of "...fisrt().front().back()..." code now.
    std::map<std::string, Monster> monsterTypes{};
    std::queue<std::pair< std::pair<float, sf::Clock>,
			  std::queue<shptr<Monster>>>> watingWaves{};

    std::vector<std::pair<std::pair<float, sf::Clock>,
			  std::queue<shptr<Monster>>>> activeWaves{};

    sf::Clock clock{};
    float intermissionSpan{10.f};
    
    bool intermissionMode{true};
    bool pumpMode{false};
    bool prepareMode{false};

    float spawnCooldown{0.5f};
    int monsterLevel{0}; 
    int currentWave{0};

    int pumpCount{0};

    
};

#endif
