#ifndef TILE_H
#define TILE_H

#include "Spritesheet.h"
#include "defs.h"
#include <SFML/Graphics.hpp>
#include <vector>

/*
 *  Tile
 */
class Tile
{
public:
    Tile(int x, int y, char type);
    Tile(Tile const&) = default;
    virtual ~Tile() = default;

    void render(sf::RenderTarget &target);
    int getTileX() const;
    int getTileY() const;
    double getX() const;
    double getY() const;
    char getType() const;
    bool checkPlaceable() const;
    void switchPlaceable();
    void setData(int x, int y, char type);
    virtual void setSprite(Spritesheet const& spriteSheet, std::vector<bool> bin) = 0;
    void setNextTile(shptr<Tile> const tile);
    shptr<Tile> getNextTile();

    Tile& operator = (Tile const &t) = default;

protected:
    int xTile {};
    int yTile {};
    unsigned xOffset {};
    unsigned yOffset {};
    char tileType {};
    bool placeable {false};
    shptr<Tile> nextTile {};

    sf::Sprite tileSprite {};
};

class Path : public Tile
{
public:
    Path(int x, int y, char type);

    void setSprite(Spritesheet const& spriteSheet, std::vector<bool> bin);

private:
    Spritesheet tileSheet {"resources/images/path.png", 32, 32};
};

class Grass : public Tile
{
public:
    Grass(int x, int y, char type);

    void setSprite(Spritesheet const& spriteSheet, std::vector<bool> bin);

private:
    Spritesheet tileSheet {"resources/images/grass.png", 32, 32};
};

class Water : public Tile
{
public:
    Water(int x, int y, char type);

    void setSprite(Spritesheet const& spriteSheet, std::vector<bool> bin);

private:
    Spritesheet tileSheet {"resources/images/water.png", 32, 32};
};

#endif