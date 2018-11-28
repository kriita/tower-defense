#ifndef MAP_H
#define MAP_H

#include "defs.h"
#include "Tile.h"
#include "Spritesheet.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
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
    int getPathNeighbors(int xPos, int yPos);
    std::vector<bool> getSpriteNeighbors(int xTile, int yTile);
    shptr<Tile> getTile(int x, int y);
    shptr<Tile> getSpawnPoint();
    shptr<Tile> getEndPoint();

    void operator = (Map const &m) = delete;

private:
    std::string fileName {};
    int timeStamp {};
    shptr<Tile> spawnPoint {};
    shptr<Tile> endPoint {};
    std::vector<std::vector<shptr<Tile>>> mapTiles {};
    Spritesheet mapSpriteSheet {"resources/images/spritesheet.png", 32, 32};

    void createMatrix();
    void readMapData();
    void findPath();
    void setTileSprites();
};

#endif