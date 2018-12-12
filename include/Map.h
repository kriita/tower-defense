#ifndef MAP_H
#define MAP_H

#include "defs.h"
#include "Monster.h"
#include "Resources.h"
#include "Tower.h"
#include "Tile.h"
#include "Spritesheet.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

/*
 *  MapError
 */
class MapError : public std::logic_error
{
    using std::logic_error::logic_error;
};

/*
 *  Map
 */
class Map
{
public:
    Map(std::string mapFileName);
    Map(Map const&) = delete;
    ~Map() = default;

    void render(sf::RenderTarget &target);
    void update();
    void handle(sf::Event event,
                std::vector<shptr<Monster>> & monsters,
                std::vector<shptr<Tower>> & towers,
                ptr<Resources> & resources);
    void makePreview(float xNew, float yNew, float scale);
    std::vector<bool> getSpriteNeighbors(int xTile, int yTile);
    shptr<Tile> getTile(int x, int y);
    shptr<Tile> getSpawnPoint();
    shptr<Tile> getEndPoint();

    void operator = (Map const&) = delete;

private:
    std::string fileName {};
    shptr<Tile> spawnPoint {};
    shptr<Tile> endPoint {};
    std::vector<std::vector<shptr<Tile>>> mapTiles {};
    std::vector<shptr<Tile>> updateList {};

    void createMatrix();
    void readMapData();
    void findPath();
    void setTileSprites();
};

#endif