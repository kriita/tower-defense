#include "Wave.h"
#include <utility>
#include <string>
#include <fstream>
#include <sstream> 

#include <iostream>

void Wave::setSpawnTile(shptr<Tile> init_spawnTile)
{
    spawnTile = std::move(init_spawnTile);    
}


std::vector<int> readSequence(int & amount, std::string word)
{
    std::istringstream iss{word};
    std::vector<int> sequence{};
    int type{};
    char symbol{};
    while(iss >> symbol)
    {
	if (symbol == ')')
	{
	    iss >> symbol;
	    iss >> amount;
	    break;
	}
	else
	{
	    iss >> type;
	    sequence.push_back(type);
	    continue;
	}
    }
    return sequence;
}

std::vector<int> readOneType(int & amount, std::string word)
{
    std::istringstream iss{word};
    std::vector<int> sequence{};
    int type{};
    char symbol{};
    iss >> type;
    iss >> symbol;
    iss >> amount;
    sequence.push_back(type);
    return sequence;

}

void Wave::readWaveData(std::string fileName)
{
    std::string filePath {"resources/waves/"};
    std::ifstream waveFile((filePath + fileName).c_str());
    if(!waveFile)
	throw WaveError{"Cannot open wave file"};

    //tolka .w filen till monster typer och mängd monster
    std::string word{};
    std::string numberString{"1234567890"};
    int amount{1};
    std::vector<int> sequence{};
    while(getline(waveFile, word, ' '))
    {
	if (word.front() == '(')
	{
	    sequence = readSequence(amount, word);
	}
	else if (numberString.find(word.front()) != std::string::npos)
	{
	    sequence = readOneType(amount, word);
	}
	else 
	{
	    throw WaveError{"incorrect wave file"};
	}

	//ställ monstern i kö
	for (int i{0}; i < amount; i++)
	{
	    for (unsigned int j{0}; j < sequence.size(); j++)
	    {
		pushMonster(sequence[j], 1);
	    }
	}
	    
    }
    
    std::cout << "done!"<< std::endl;
}
    
shptr<Monster> Wave::spawnMonster()
{
    clock.restart();
    auto temp = monsterQueue.front();
    monsterQueue.pop();
    return temp;
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



