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

    void render(sf::RenderTarget &target);
    Tile* getTile(int x, int y);
    Tile* getSpawnPoint();
    Tile* getEndPoint();

    void operator = (Map const &m) = delete;

private:
    std::string fileName {};
    int timeStamp {};
    Tile* spawnPoint {};
    Tile* endPoint {};
    std::vector<std::vector<Tile>> mapTiles {};

    sf::Texture mapSpriteSheet {};

    void readMapData();
    void findPath();
    void setTileSprites();
};

#endif