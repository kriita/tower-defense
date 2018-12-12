#include "WavePump.h"

WavePump::WavePump()
    :active{false}, waveCount{1}, spawnCount{25}, monsterLevelRoof{5},
    monsterLevelFloor{1}, 
    spawnCooldown{0.1f}, intermissionSpan{3.f}, clock{}, intermissionClock{},
    monsterTypes{}, monsterSequence{7},
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
    int randomNumber{};
    for (unsigned int i{0}; i < monsterSequence.size(); i++)
    {
	randomNumber = (std::rand() % monsterTypes.size());
	monsterSequence[i] =
	    std::make_shared<Monster>(*(monsterTypes[randomNumber]));
    }
}

void WavePump::iterateIndex()
{
    monsterSequenceIndex++;
    if (monsterSequenceIndex >= static_cast<int>(monsterSequence.size()))
    {
	monsterSequenceIndex = 0;
    }
}

void WavePump::intermission()
{
    //prepare next wave while the player rests
    intermissionClock.restart();
    spawnCount = 25;
    scrambleMonsterSequence();
    

}

bool WavePump::readyToSpawn()
{
    return !(isIntermission()) && 
	(clock.getElapsedTime().asSeconds() > spawnCooldown);
}

shptr<Monster> WavePump::spawnMonster()
{
    spawnCount--;

    if (spawnCount <= 0)
    {
	intermission();
    }

    shptr<Monster> tempMonster{};
    tempMonster = std::make_shared<Monster>(
	*(monsterSequence[monsterSequenceIndex]));
    iterateIndex();
    clock.restart();
    return tempMonster;
}

bool WavePump::isIntermission()
{
    return intermissionClock.getElapsedTime().asSeconds() < intermissionSpan;
}
