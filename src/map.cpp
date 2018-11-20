#include "constants.h"
#include "map.h"
#include "tile.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

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
    setTileSprites();
}

void Map::render(sf::RenderTarget &target)
{
    for (int y {0}; y < yTilesMax; ++y)
    {
        for (int x {0}; x < xTilesMax; ++x)
        {
            mapTiles[x][y].render(target);
        }
    }
}

void Map::readMapData()
{
    mapTiles.resize(xTilesMax, vector<Tile>(yTilesMax, Tile {}));

    string mapFolder {"resources/maps/"};

    ifstream mapFile((mapFolder + fileName).c_str());
    string line {};
    char typeChar {};
    for (int y {0}; y < yTilesMax; ++y)
    {
        std::getline(mapFile, line);
        std::istringstream iss(line);
        for (int x {0}; x < xTilesMax; ++x)
        {
            iss >> typeChar;
            
            if(typeChar == startChar)
            {
                spawnPoint = &mapTiles[x][y];
                typeChar = pathChar;
            }
            else if(typeChar == endChar)
            {
                endPoint = &mapTiles[x][y];
                typeChar = pathChar;
            }

            mapTiles[x][y].setData(x, y, typeChar);
        }
    }
    mapFile.close();
}

void Map::findPath()
{
    int x {spawnPoint->getX()};
    int y {spawnPoint->getY()};
    int xDir {(x == 0 ? 1 : (x == xTilesMax-1 ? -1 : 0))};
    int yDir {(y == 0 ? 1 : (y == yTilesMax-1 ? -1 : 0))};

    Tile* fromTile {spawnPoint};

    while (getTile(x, y) != endPoint)
    {
        if (getTile(x + xDir, y + yDir)->getType() == pathChar ||
            getTile(x + xDir, y + yDir)->getType() == endChar)
        {
            x += xDir;
            y += yDir;
        }
        else if (getTile(x + (1 - abs(xDir)), y + (1 - abs(yDir)))->getType() == pathChar ||
                 getTile(x + (1 - abs(xDir)), y + (1 - abs(yDir)))->getType() == endChar)
        {
            fromTile->setNextTile(getTile(x, y));
            fromTile = getTile(x, y);
            x += (1 - abs(xDir));
            y += (1 - abs(yDir));
            xDir = (1 - abs(xDir));
            yDir = (1 - abs(yDir));
        }
        else 
        {
            fromTile->setNextTile(getTile(x, y));
            fromTile = getTile(x, y);
            x -= (1 - abs(xDir));
            y -= (1 - abs(yDir));
            xDir = abs(xDir) - 1;
            yDir = abs(yDir) - 1;
        }
    }
    fromTile->setNextTile(endPoint);
}

void Map::setTileSprites()
{
    int binaryNeighbor {};
    int xOffset {};
    int yOffset {};

    for (int y {0}; y < yTilesMax; ++y)
    {
        for (int x {0}; x < xTilesMax; ++x)
        {
            // gör till egen funktion?
            binaryNeighbor = 0;

            if (x != 0 && mapTiles[x-1][y].getType() == pathChar)
                binaryNeighbor += 1;
            if (x != xTilesMax-1 && mapTiles[x+1][y].getType() == pathChar)
                binaryNeighbor += 2;
            if (y != 0 && mapTiles[x][y-1].getType() == pathChar)
                binaryNeighbor += 4;
            if( y != yTilesMax-1 && mapTiles[x][y+1].getType() == pathChar)
                binaryNeighbor += 8;

            if (binaryNeighbor == 4 || binaryNeighbor == 6 || binaryNeighbor == 8 ||
                binaryNeighbor == 10 || binaryNeighbor == 12)
                xOffset = 0;
            else if (binaryNeighbor == 15)
                xOffset = 1;
            else if (binaryNeighbor == 1 || binaryNeighbor == 3 ||
                     binaryNeighbor == 5 || binaryNeighbor == 9)
                xOffset = 2;

            if (binaryNeighbor == 9 || binaryNeighbor == 10)
                yOffset = 0;
            else if (binaryNeighbor == 15)
                yOffset = 1;
            else if (binaryNeighbor == 5 || binaryNeighbor == 6)
                yOffset = 2;
            else if (binaryNeighbor == 1 || binaryNeighbor == 3 || binaryNeighbor == 4 ||
                     binaryNeighbor == 8 || binaryNeighbor == 12)
                yOffset = 3;

            mapTiles[x][y].setSprite(mapSpriteSheet, xOffset, yOffset);
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