#include "constants.h"
#include "Map.h"
#include "Tile.h"
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

//#include <iostream>

using std::string;
using std::vector;
using std::ifstream;
using std::make_shared;

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

void Map::update()
{
    for (auto & tile : updateList)
    {
        tile->update();
    }
}

void Map::readMapData()
{
    mapTiles.resize(xTilesMax, vector<shptr<Tile>>(yTilesMax, nullptr));

    string mapFolder {"resources/maps/"};

    ifstream mapFile((mapFolder + fileName).c_str());
    if (!mapFile)
    {
        throw MapError{"Cannot open map file"};
    }

    string line {};
    char typeChar {};
    for (int y {0}; y < yTilesMax; ++y)
    {
        std::getline(mapFile, line);
        std::istringstream iss(line);
        for (int x {0}; x < xTilesMax; ++x)
        {
            iss >> typeChar;

            if (typeChar == startChar)
            {
                mapTiles[x][y] = make_shared<Path> (x, y, pathChar);
                spawnPoint = mapTiles[x][y];
                typeChar = pathChar;
            }
            else if (typeChar == endChar)
            {
                mapTiles[x][y] = make_shared<Path> (x, y, pathChar);
                endPoint = mapTiles[x][y];
                typeChar = pathChar;
            }
            else if (typeChar == pathChar)
            {
                mapTiles[x][y] = make_shared<Path> (x, y, pathChar);
            }
            else if (typeChar == treeChar)
            {
                mapTiles[x][y] = make_shared<Tree> (x, y, treeChar);
            }
            else if (typeChar == waterChar)
            {
                mapTiles[x][y] = make_shared<Water> (x, y, waterChar);
            }
            else
            {
                mapTiles[x][y] = make_shared<Grass> (x, y, fieldChar);
            }

            if (getTile(x, y)->checkAnimated())
                updateList.push_back(getTile(x, y));
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
    for (int y {0}; y < yTilesMax; ++y)
    {
        for (int x {0}; x < xTilesMax; ++x)
        {           
            if (getTile(x, y)->getType() == pathChar)
                getTile(x, y)->setSprite(getSpriteNeighbors(x, y));
            else
                getTile(x, y)->setSprite(getSpriteNeighbors(x, y));
        }
    }
}

vector<bool> Map::getSpriteNeighbors(int xTile, int yTile)
{
    vector<bool> bin {};
    bin.resize(8, false);
    char tileType {getTile(xTile, yTile)->getType()};
    unsigned n {0};

    for (int y {yTile-1}; y <= yTile+1; ++y)
    {
        for (int x {xTile-1}; x <= xTile+1; ++x)
        {
            if (x >= 0 && x <= xTilesMax-1 &&
                y >= 0 && y <= yTilesMax-1 &&
                !(x == xTile && y == yTile))
            {
                if (getTile(x, y)->getType() == tileType)
                    bin[n] = 1;
            } else if (x < 0 || x == xTilesMax ||
                y < 0 || y == yTilesMax)
                bin[n] = 1;

            if (!(x == xTile && y == yTile))
                ++n;
        }
    }

    return bin;
}

shptr<Tile> Map::getTile(int x, int y)
{
    if (x < 0 || y < 0 || x >= xTilesMax || y >= yTilesMax)
    {
        throw MapError{"GetTile() coordinates out of bounds"};
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