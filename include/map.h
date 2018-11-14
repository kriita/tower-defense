#ifndef MAP_H
#define MAP_H

#include "tile.h"
#include <vector>
#include <string>

/*
 *  Map
 */
class Map
{
public:
    Map(std::string mapFileName);
    Map(Map const &m) = delete;
    ~Map() = default;
    void operator = (Map const &m) = delete;

    Tile* getTile(int x, int y);
    Tile* getSpawnPoint();
    Tile* getEndPoint();

private:
    std::string fileName {};
    int timeStamp {};
    Tile* spawnPoint {};
    Tile* endPoint {};
    std::vector<std::vector<Tile>> mapTiles {};

    void readMapData();
    void findPath();
};

#endif