#include "map.h"
#include "tile.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include <iostream>

using std::string;
using std::vector;
using std::ifstream;

/*
 *  Map
 */
Map::Map(string mapFileName)
: fileName {mapFileName}
{
    readMapData();
    findPath();
}

void Map::readMapData()
{
    int xMax {20};  // temporära data
    int yMax {15};  // temporära data

    mapTiles.resize(xMax, vector<Tile>(yMax, Tile {}));

    ifstream mapFile("resources/maps/map.dat");
    string line {};
    char c {};
    for (int y {0}; y < yMax; ++y)
    {
        std::getline(mapFile, line);
        std::istringstream iss(line);
        for (int x {0}; x < xMax; ++x)
        {
            iss >> c;
            mapTiles[x][y].setData(x, y, c - 48);

            if(y == 0 && c == 48)
                spawnPoint = &mapTiles[x][y];

            if(y == yMax-1 && c == 48)
                endPoint = &mapTiles[x][y];
        }
    }
    mapFile.close();
}

void Map::findPath()
{
    int x {spawnPoint->getX()};
    int y {0};
    int xDir {0};
    int yDir {1};

    while (y != endPoint->getY())
    {
        if(x == 15) break;
        if (getTile(x + xDir, y + yDir)->getType() == 0)
        {
            getTile(x, y)->setNextTile(getTile(x + xDir, y + yDir));
            x += xDir;
            y += yDir;
        }
        else if (getTile(x + (1 - xDir), y + (1 - yDir))->getType() == 0)
        {
            getTile(x, y)->setNextTile(getTile(x + (1 - xDir), y + (1 - yDir)));
            x += (1 - xDir);
            y += (1 - yDir);
        }
        else 
        {
            getTile(x, y)->setNextTile(getTile(x - (1 - xDir), y - (1 - yDir)));
            x -= (1 - xDir);
            y -= (1 - yDir);
        }
        std::cout << "->" << x << ":" << y << "\n";
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