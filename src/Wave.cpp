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
    return std::make_shared<Orc>(spawnTile, 2);
}
     
bool Wave::timeToSpawn()
{
    return clock.getElapsedTime().asSeconds() > cooldown;
}

Wave::Wave()
    : spawnTile{nullptr}, cooldown{2.f}
{}

bool Wave::empty()
{
    return monsterQueue.empty();
}


void Wave::pushMonster(int MonsterType, int level)
{
    switch(MonsterType)
    {
    case 1: 
	monsterQueue.push(std::make_shared<Orc>(spawnTile, level)); 
	std::cout << monsterQueue.size() << std::endl; 
	break;
    case 2: std::cout << "2222222" << std::endl; break;
    default: std::cout << "Who?" << std::endl; break;
    }
    
}
 
std::istream& Wave::operator>>(std::istream& reqruits)
{
    if (reqruits)
    {
	
	int next_reqruit{};
	reqruits >> next_reqruit;
	reqruits >> 
	
	while (reqruits)
	{
	    pushMonster(next_reqruit, 1); // think of a way to read level
	    reqruits >> next_reqruit;
	}
    }
}



