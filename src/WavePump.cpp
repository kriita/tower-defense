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
	int randomNumber{};
	randomNumber = (std::rand() % monsterTypes.size());
	monsterSequence[i] =
	    std::make_shared<Monster>(*(monsterTypes[randomNumber]));
    }
}

void WavePump::iterateIndex()
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

shptr<Monster> WavePump::spawnMonster()
{
    shptr<Monster> tempMonster{};
    tempMonster = std::make_shared<Monster>(
	*(monsterSequence[monsterSequenceIndex]));
    iterateIndex();
    clock.restart();
    return tempMonster;
}
