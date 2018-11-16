#include <SFML/Graphics.hpp>
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

int xMax {18};  // temporära data
int yMax {18};  // temporära data

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
            
            if(typeChar == 'S')
            {
                spawnPoint = &mapTiles[x][y];
                typeChar = '0';
            }
            else if(typeChar == 'E')
            {
                endPoint = &mapTiles[x][y];
                typeChar = '0';
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
    int xDir {(x == 0 ? 1 : (x == xMax-1 ? -1 : 0))};
    int yDir {(y == 0 ? 1 : (y == yMax-1 ? -1 : 0))};

    Tile* fromTile {spawnPoint};

    while (getTile(x, y) != endPoint)
    {
        if (getTile(x + xDir, y + yDir)->getType() == '0' ||
            getTile(x + xDir, y + yDir)->getType() == 'E')
        {
            x += xDir;
            y += yDir;
        }
        else if (getTile(x + (1 - abs(xDir)), y + (1 - abs(yDir)))->getType() == '0' ||
                 getTile(x + (1 - abs(xDir)), y + (1 - abs(yDir)))->getType() == 'E')
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
    mapSpriteSheet.loadFromFile("resources/images/spritesheet.png");

    for (int y {0}; y < yMax; ++y)
    {
        for (int x {0}; x < xMax; ++x)
        {
            // gör till egen funktion
            binaryNeighbor = 0;

            if (x != 0 && mapTiles[x-1][y].getType() == '0')
                binaryNeighbor += 1;
            if (x != xMax-1 && mapTiles[x+1][y].getType() == '0')
                binaryNeighbor += 2;
            if (y != 0 && mapTiles[x][y-1].getType() == '0')
                binaryNeighbor += 4;
            if( y != yMax-1 && mapTiles[x][y+1].getType() == '0')
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