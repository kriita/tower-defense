#include <SFML/Graphics.hpp>
#include "map.h"
#include "tile.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

#include <iostream>

using std::string;
using std::vector;
using std::ifstream;

int xMax {20};  // temporära data
int yMax {15};  // temporära data

/*
 *  Map
 */
Map::Map(string mapFileName)
: fileName {mapFileName}
{
    readMapData();
    findPath();
}

void Map::render(sf::RenderWindow &window)
{
    for (int y {0}; y < yMax; ++y)
    {
        for (int x {0}; x < xMax; ++x)
        {
            mapTiles[x][y].render(window);
        }
    }
}

void Map::readMapData()
{
    mapTiles.resize(xMax, vector<Tile>(yMax, Tile {}));

    string mapFolder {"resources/maps/"};

    ifstream mapFile((mapFolder + fileName).c_str());
    string line {};
    char typeChar {};
    for (int y {0}; y < yMax; ++y)
    {
        std::getline(mapFile, line);
        std::istringstream iss(line);
        for (int x {0}; x < xMax; ++x)
        {
            iss >> typeChar;
            mapTiles[x][y].setData(x, y, typeChar);

            if(typeChar == 'S')
                spawnPoint = &mapTiles[x][y];

            if(typeChar == 'E')
                endPoint = &mapTiles[x][y];
        }
    }
    mapFile.close();
}

void Map::findPath()
{
    int x {spawnPoint->getX()};
    int y {spawnPoint->getY()};
    int xDir {0};
    int yDir {1};

    while (getTile(x, y) != endPoint)
    {
        if (getTile(x + xDir, y + yDir)->getType() == '0' ||
            getTile(x + xDir, y + yDir)->getType() == 'E')
        {
            getTile(x, y)->setNextTile(getTile(x + xDir, y + yDir));
            x += xDir;
            y += yDir;
        }
        else if (getTile(x + (1 - abs(xDir)), y + (1 - abs(yDir)))->getType() == '0' ||
                 getTile(x + (1 - abs(xDir)), y + (1 - abs(yDir)))->getType() == 'E')
        {
            getTile(x, y)->setNextTile(getTile(x + (1 - abs(xDir)), y + (1 - abs(yDir))));
            x += (1 - abs(xDir));
            y += (1 - abs(yDir));
            xDir = (1 - abs(xDir));
            yDir = (1 - abs(yDir));
        }
        else 
        {
            getTile(x, y)->setNextTile(getTile(x - (1 - abs(xDir)), y - (1 - abs(yDir))));
            x -= (1 - abs(xDir));
            y -= (1 - abs(yDir));
            xDir = abs(xDir) - 1;
            yDir = abs(yDir) - 1;
        }
    }
}

Tile* Map::getTile(int x, int y)
{
    return &mapTiles[x][y];
}

Tile* Map::getSpawnPoint()
{
    return spawnPoint;
}

Tile* Map::getEndPoint()
{
    return endPoint;
}