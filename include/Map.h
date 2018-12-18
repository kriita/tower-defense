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
 * 
 *  The class is responsible for creating a map object that holds a matrix 
 *  made from two levels of vectors, holding shared pointers to Tile objects
 *  which make up the map.
 * 
 *  Map layouts are read from a map file specified through the constructor.
 *  The files consists of a single character (char) for each Tile, with spaces
 *  between them and in a 18x18 grid.
 * 
 *  The available characters are:
 *  S: starting point
 *  E: ending point
 *  0: path
 *  1: grass
 *  2: water
 *  t: tree
 *  
 *  MapError messages will be thrown if an incorrect format is used.
 *  Tile objects are created in the matrix from the type of character.
 * 
 *  Pointers to the starting/ending point Tile are set.
 * 
 *  After the map is created a loop goes through all the tiles, checks for tiles
 *  of same type around and runs setSprite for the tile, including the info
 *  about the surrounding tiles of same type. This is to make use of sprite sheets.
 */
class Map
{
public:
    Map(std::string mapFileName);
    Map(Map const&) = delete;
    ~Map() = default;

    void render(sf::RenderTarget &target) const;
    void update();
    void handle(sf::Event event,
                std::vector<shptr<Monster>> & monsters,
                std::vector<shptr<Tower>> & towers,
                ptr<Resources> & resources);
    void makePreview(float xNew, float yNew, float scale);
    std::vector<bool> getSpriteNeighbors(int xTile, int yTile);
    shptr<Tile> getTile(int x, int y) const;
    shptr<Tile> getSpawnPoint() const;
    shptr<Tile> getEndPoint() const;

    void operator = (Map const&) = delete;

private:
    std::string fileName {};        // Filename without ".map"
    shptr<Tile> spawnPoint {};
    shptr<Tile> endPoint {};
    std::vector<std::vector<shptr<Tile>>> mapTiles {};
    std::vector<shptr<Tile>> updateList {};

    void readMapData();
    void findPath();
    void setTileSprites();
};

#endif