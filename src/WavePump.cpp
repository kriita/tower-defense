
#include "WavePump.h"

#include <fstream>
#include <sstream>

WavePump::WavePump(float _intermissionSpan)
    :clock{}, intermissionSpan{_intermissionSpan}
{}

void WavePump::skipIntermission()
{
    prepareMode = true;
    intermissionMode = false;
}

void WavePump::addMonsterType(Monster monster)
{
    monsterTypes.insert(
	std::pair<std::string, Monster>(monster.getType(), monster) );
}

void WavePump::readFromFile(std::string name, std::string path,
			    std::string suffix)
{
    std::ifstream fileData((path + name + suffix).c_str());
    if (!fileData)
	throw WavePumpError{"Did not find file"};

    //each row in name.w will make wave 1, 2, ...
    std::string row{};
    while ( getline(fileData, row, '\n') )
    {	
	watingWaves.push( *(new std::pair< std::pair<float, sf::Clock>,
		                     std::queue<shptr<Monster>> >) );
	std::istringstream rowStream{row};
	std::string word{};
	//interprit every word on every row
	int multi{};
	std::vector<std::string> sequence{};
	while ( getline(rowStream, word, ' ') )
	{
	    multi = 0;
	    while( !sequence.empty() )
	    {
		sequence.pop_back();
	    }
	    //set length of short pause inbetween to spawning monsters
	    //syntax: C= 'a floating point'
	    if (word.find("C=") != std::string::npos)
	    {
		std::istringstream subWordStream{word};
		subWordStream.ignore(256, '=');
		subWordStream >> spawnCooldown;
	    }	    
	    //set level of monsters, syntax L=0, 1, 2, ..., 9
	    else if (word.find("L=") != std::string::npos)
	    {
		std::istringstream subWordStream{word};
		subWordStream.ignore(256, '=');
		subWordStream >> monsterLevel;
		if (monsterLevel > 9)
		{
		    monsterLevel = 9;
		}
		    
	    }
	    //sequence format repeats a sequence N times.
	    //syntax: {}type1,type2,type3,*N
	    if (word.find("{}") != std::string::npos)
	    {
		std::istringstream wordStream{word};
		wordStream.ignore(256, '}');
		while ( getline(wordStream, word, ',') )
		{
		    if (word.find('*') != std::string::npos)
		    {
			//* must be followed by a integer
			std::istringstream subWordStream{word};
			subWordStream.ignore(256, '*');
			subWordStream >> multi;
		    }
		    else
		    {
			//add to sequence of types
		        sequence.push_back(word);
		    }
		}
	    }
	    //single type multiple times, syntax: type1*N
	    else if (word.find('*') != std::string::npos)
	    {
		std::string type;
		std::istringstream subWordStream{word};
		getline(subWordStream, type, '*');
		sequence.push_back(type);
		subWordStream >> multi;
	    }
	    //single type once, syntax: type1
	    else if (monsterTypes.find(word) != monsterTypes.end())
	    {
		multi = 1;
		sequence.push_back(word);
	    }
	    //anything else is interprited as a short pause
	    //note: also imsspelled words
	    else
	    {
		multi = 1;
		sequence.push_back("nop");
	    }
	    //push the wave
	    watingWaves.back().first.first = spawnCooldown;
	    pushMonsterSequence(sequence, multi);
	}
    }
}

void WavePump::pushMonster(std::string type)
{
    if (monsterTypes.find(type) != monsterTypes.end())
    {
	//push the type of monster, note spelling is important!
	watingWaves.back().second.push(
	    std::make_shared<Monster>(monsterTypes.at(type)) );
	//set the Level
	watingWaves.back().second.back()->setLevel(monsterLevel);
    }
    else
    {
	//push nullptr, will act as small pause in spawning
	watingWaves.back().second.push(nullptr);
    }
}

void WavePump::pushMonsterSequence(std::vector<std::string> sequence, int multi)
{
    for (int i{0}; i < multi; i++)
    {
	for (unsigned int j{0}; j < sequence.size(); j++)
	{
	    pushMonster(sequence[j]);
	}
    }   
}

void WavePump::prepare(ptr<Resources> & resources)
{
    if ( watingWavesEmpty() )
    {
	
    }
    else
    {
	currentWave++;
	resources->changeCurrentWave(getWave());
	activeWaves.push_back(watingWaves.front());
	watingWaves.pop();
	prepareMode = false;
	pumpMode = true; 
    }
}

void WavePump::intermission()
{
    if (clock.getElapsedTime().asSeconds() < intermissionSpan)
    {
	
    }
    else
    {
	intermissionMode = false;
	prepareMode = true;
    }
}

void WavePump::pump(std::vector<std::shared_ptr<Monster>> & monsters)
{
    for (unsigned int i{0}; i < activeWaves.size(); i++)
    {
        if (activeWaves[i].second.empty() )
	{
	    activeWaves.erase(activeWaves.begin() + i);
	}
	else
	{
	    //spawn if the spawnCooldown is cpmpleted and its not a nullptr
	    if ( activeWaves[i].first.first < 
		 activeWaves[i].first.second.getElapsedTime().asSeconds() )
	    {
		if (activeWaves[i].second.front() != nullptr) 
		{
		    monsters.push_back(activeWaves[i].second.front());
		    activeWaves[i].second.pop();
		    pumpCount++;
		    activeWaves[i].first.second.restart();
		}
		else
		{
		    activeWaves[i].second.pop();
		    activeWaves[i].first.second.restart();
		}
	    }
	    else {}
	}
    }
    if ( activeWavesEmpty() )
    {
	intermissionMode = true;
	clock.restart();
	pumpMode = false;
	prepareMode = false;
    }
}

void WavePump::update(std::vector<std::shared_ptr<Monster>> & monsters,
		      ptr<Resources> & resources)
{
    if (prepareMode)
	prepare(resources);

    if (pumpMode)
	pump(monsters);

    if (intermissionMode)
	intermission();

    /*/  std::cout << empty() << " iM:" << intermissionMode 
               << " pM:" << pumpMode << " pC:" << pumpCount <<  std::endl;
/*/
}
