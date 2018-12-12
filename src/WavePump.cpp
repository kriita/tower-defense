#include "WavePump.h"

#include <fstream>
#include <sstream>

WavePump::WavePump(float _spawnCooldown, float _intermissionSpan)
    :monsterTypes{}, clock{}, intermissionClock{},
    spawnCooldown{_spawnCooldown}, intermissionSpan{_intermissionSpan}
{}


bool WavePump::readyToSpawn()
{
    return clock.getElapsedTime().asSeconds() > spawnCooldown;
}

bool WavePump::isIntermission()
{
    return intermissionClock.getElapsedTime().asSeconds() < intermissionSpan;
}

void WavePump::addMonsterType(Monster monster)
{
    monsterTypes.insert( 
	std::pair<std::string, Monster>(monster.getType(), monster) );
}

void WavePump::update(std::vector<shptr<Monster>> & monsters)
{
    if ( readyToSpawn() && !isIntermission() )
    {
	if (waves.empty())
	{
	    return;
	}
	else if(waves.front().empty())
	{
	    intermission();
	}
	else
	{
	    clock.restart();
	    /*/monsters.push_back(std::make_shared<Monster>(
	      monsterTypes.begin()->second));/*/
	    shptr<Monster> tempMonster = waves.front().front();
	    if(tempMonster != nullptr)
	    {
		monsters.push_back(std::make_shared<Monster>(*tempMonster));
	    }
	    waves.front().pop();
	}
    }
    else
    {
	return;
    }
}

void WavePump::intermission()
{
    waves.pop();
    intermissionClock.restart();
}

void WavePump::pushMonster(std::string word, int multiple)
{
    for (int i{}; i < multiple; ++i)
    {
	if (monsterTypes.find(word) != monsterTypes.end())
	{
	    waves.back().push(
		std::make_shared<Monster>(monsterTypes.at(word)));
	} else
	{
	    waves.back().push(
		nullptr);
	}
    }
}

void WavePump::readFromFile(std::string name, 
			    std::string path,
			    std::string suffix)
{
    std::cout << "readning file..." << std::endl;

    std::ifstream fileData((path + name + suffix).c_str());
    if (!fileData)
	throw WavePumpError{"Did not find file"};

    std::string row{};
    while( getline(fileData, row) )
    {
	waves.push(*(new std::queue<shptr<Monster>>()));
	std::istringstream rowStream{row};
	std::string word{};
	while ( getline(rowStream, word, ' ') ) //interprit each word here
	{
	    //if (monsterTypes.find("BrownRabbit"))
	    if (word.find('*') != std::string::npos)
	    {
		std::istringstream wordStream{word};
		getline(wordStream, word, '*');
		int multiple{};
		wordStream >> multiple;
		pushMonster(word, multiple);
	    } else
	    {
		pushMonster(word);
	    }
	}
    }
}


std::string WavePump::getMonsterTypes()
{
    std::string temp{};
    for (auto it = monsterTypes.begin(); it != monsterTypes.end(); ++it)
    {
	temp += it->first + " ";
    }
    return "monsterTypes: " + temp;
}
