#include "Wave.h"
#include <utility>

#include <iostream>

void Wave::setSpawnTile(shptr<Tile> init_spawnTile)
{
    spawnTile = std::move(init_spawnTile);    
}

shptr<Monster> Wave::spawnMonster()
{
    clock.restart();
    auto temp = monsterQueue.front();
    monsterQueue.pop();
    return temp;
}

void readWaveData(std::string fileName)
{
    (void) fileName;
}
     
bool Wave::timeToSpawn()
{
    if (clock.getElapsedTime().asSeconds() < cooldown)
    {
	return false;
    }
    else if (empty())
    {
	return false;
    }
    else if (monsterQueue.front() == nullptr)
    {
	clock.restart();
	monsterQueue.pop();
	return false;
    }
    else
    { 
	return (!empty() && clock.getElapsedTime().asSeconds() > cooldown);
    }
	 
}

Wave::Wave()
    : spawnTile{nullptr}, clock{}, cooldown{.5f}
{}

bool Wave::empty()
{
    return monsterQueue.empty();
}


void Wave::pushMonster(int MonsterType, int level)
{
    switch(MonsterType)
    {
    case 0:
	monsterQueue.push(nullptr);
	break;
    case 1: 
	monsterQueue.push(std::make_shared<Orc>(spawnTile, level));
	break;
    case 2:
	monsterQueue.push(std::make_shared<Flash>(spawnTile, level));
	break;
    case 3:
	monsterQueue.push(std::make_shared<Tank>(spawnTile, level));
	break;
    case 4:
	monsterQueue.push(std::make_shared<Derp>(spawnTile, level));
	break;
    default:
	break;
    }
    
}

std::istream& Wave::operator>>(std::istream& reqruits)
{
    if (reqruits)
    {
	int next_reqruit{};
	reqruits >> next_reqruit;
	
	while (reqruits)
	{
	    pushMonster(next_reqruit, 1);
	    reqruits >> next_reqruit;
	}

    }
    return reqruits;
}



