#include "constants.h"
#include "Map.h"
#include "Tile.h"
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

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
    setTileSprites();
}

void Map::render(sf::RenderTarget &target)
{
    for (int y {0}; y < yTilesMax; ++y)
    {
        for (int x {0}; x < xTilesMax; ++x)
        {
            getTile(x, y)->render(target);
        }
    }
}

void Map::createMatrix()
{
    mapTiles.resize(xTilesMax, vector<shptr<Tile>>(yTilesMax, nullptr));

    for (int y {0}; y < yTilesMax; ++y)
    {
        for (int x {0}; x < xTilesMax; ++x)
        {
            mapTiles[x][y] = std::make_shared<Tile> ();
        }
    }
}

void Map::readMapData()
{
    createMatrix();

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
                spawnPoint = mapTiles[x][y];
                typeChar = pathChar;
            }
            else if(typeChar == endChar)
            {
                endPoint = mapTiles[x][y];
                typeChar = pathChar;
            }

            getTile(x, y)->setData(x, y, typeChar);
        }
    }
    mapFile.close();
}

void Map::findPath()
{
    int x {spawnPoint->getTileX()};
    int y {spawnPoint->getTileY()};
    int xDir {(x == 0 ? 1 : (x == xTilesMax-1 ? -1 : 0))};
    int yDir {(y == 0 ? 1 : (y == yTilesMax-1 ? -1 : 0))};

    shptr<Tile> fromTile {spawnPoint};

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
    unsigned binaryNeighbor {};
    unsigned xOffset {};
    unsigned yOffset {};

    for (int y {0}; y < yTilesMax; ++y)
    {
        for (int x {0}; x < xTilesMax; ++x)
        {
            binaryNeighbor = getSpriteNeighbors(x, y);

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

            getTile(x, y)->setSprite(mapSpriteSheet, xOffset, yOffset);
        }
    }
}

int Map::getSpriteNeighbors(int xPos, int yPos)
{
    unsigned binaryNeighbor {0};
    char tileType {getTile(xPos, yPos)->getType()};

    if (xPos != 0 && getTile(xPos-1, yPos)->getType() == tileType)
        binaryNeighbor += 1;
    if (xPos != xTilesMax-1 && getTile(xPos+1, yPos)->getType() == tileType)
        binaryNeighbor += 2;
    if (yPos != 0 && getTile(xPos, yPos-1)->getType() == tileType)
        binaryNeighbor += 4;
    if (yPos != yTilesMax-1 && getTile(xPos, yPos+1)->getType() == tileType)
    binaryNeighbor += 8;

    return binaryNeighbor;
}

shptr<Tile> Map::getTile(int x, int y)
{
    if (x < 0 || y < 0 || x >= xTilesMax || y >= yTilesMax)
    {
        throw ("Error: getTile coordinates out of bounds");
    }

    return mapTiles[x][y];
}

shptr<Tile> Map::getSpawnPoint()
{
    return spawnPoint;
}

shptr<Tile> Map::getEndPoint()
{
    return endPoint;
}