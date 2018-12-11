#include "WavePump.h"

WavePump::WavePump()
    :waveCount{1}, monsterLevelRoof{5}, monsterLevelFloor{1}, 
    spawnCooldown{0.5f}, clock{}, monsterTypes{}, monsterSequence{7},
    monsterSequenceIndex{0}, spawnTile{nullptr}
{
    std::srand(std::time(nullptr));
}

void WavePump::setSpawnTile(shptr<Tile> tile)
{
    spawnTile = std::move(tile);
}

void WavePump::addMonsterType(shptr<Monster> monster)
{
    monsterTypes.push_back(monster);
}

void WavePump::scrambleMonsterSequence()
{
    for (unsigned int i{0}; i < monsterSequence.size(); i++)
    {
	//need copy constructor for monster, nuvarnade lösning
	//använder inte monsterType som tänkt.
      //shptr<Monster> tempMonster = std::make_shared<Monster>(monsterTypes[0]);
	
	int randomNumber = std::rand()%4;
	shptr<Monster> tempMonster{};
	switch(randomNumber)
	{
	case 0:
	    randomNumber = std::rand()%(monsterLevelRoof-monsterLevelFloor) +
		monsterLevelFloor;
	    tempMonster = std::make_shared<Orc>(spawnTile, randomNumber);
	    monsterSequence[i] = std::move(tempMonster);
	    break;
	case 1:
	    randomNumber = std::rand()%(monsterLevelRoof-monsterLevelFloor) +
		monsterLevelFloor;
	    tempMonster = std::make_shared<Flash>(spawnTile, randomNumber);
	    monsterSequence[i] = std::move(tempMonster);
	    break;
	case 2:
	    randomNumber = std::rand()%(monsterLevelRoof-monsterLevelFloor) +
		monsterLevelFloor;
	    tempMonster = std::make_shared<Tank>(spawnTile, randomNumber);
	    monsterSequence[i] = std::move(tempMonster);
	    break;
	case 3:
	    randomNumber = std::rand()%(monsterLevelRoof-monsterLevelFloor) +
		monsterLevelFloor;
	    tempMonster = std::make_shared<Derp>(spawnTile, randomNumber);
	    monsterSequence[i] = std::move(tempMonster);
	    break;
	default: throw WavePumpError{"This should not happen!"};
	}
    }
}

void WavePump::IterateIndex()
{
    if (++monsterSequenceIndex < static_cast<int>(monsterSequence.size()))
    {
	monsterSequenceIndex = 0;
    }
}

bool WavePump::readyToSpawn()
{
    return clock.getElapsedTime().asSeconds() > spawnCooldown;
}

shptr<Monster> spawnMonster()
{
    //return )(/&)(/&¤)(/&#/(¤&!!!!
    return nullptr;
}
