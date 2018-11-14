#include "tile.h"

/*
 *  Tile
 */

int Tile::getX() const
{
    return xPos;
}

int Tile::getY() const
{
    return yPos;
}

int Tile::getType() const
{
    return type;
}

void Tile::setData(int x, int y, int t)
{
    xPos = x;
    yPos = y;
    type = t;
}

void Tile::setNextTile(Tile* const tile)
{
    nextTile = tile;
}

Tile* Tile::getNextTile()
{
    return nextTile;
}

bool Tile::checkOnPath() const
{
    return !(nextTile == nullptr);
}