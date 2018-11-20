#ifndef TILE_H
#define TILE_H

#include "Spritesheet.h"

/*
 *  Tile
 */
class Tile
{
public:
    Tile() = default;
    Tile(Tile const&) = default;
    ~Tile() = default;

    void render(sf::RenderTarget &target);
    int getX() const;
    int getY() const;
    char getType() const;
    bool checkPlaceable() const;
    void switchPlaceable();
    void setData(int x, int y, char type);
    void setSprite(Spritesheet const& spriteSheet, unsigned xOffset, unsigned yOffset);
    void setNextTile(Tile* const tile);
    Tile* getNextTile();

    Tile& operator = (Tile const &t) = default;

private:
    int xPos {};
    int yPos {};
    char tileType {};
    bool placeable {};
    Tile* nextTile {};

    sf::Sprite tileSprite {};
};

#endif