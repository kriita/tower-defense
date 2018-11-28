#include "constants.h"
#include "Spritesheet.h"
#include "Tile.h"
#include <memory>

/*
 *  Tile
 */

Tile::Tile(int x, int y, char type)
: xTile{x}, yTile{y}, tileType{type}
{

}

void Tile::render(sf::RenderTarget &target)
{
    target.draw(tileSprite);
}

int Tile::getTileX() const
{
    return xTile;
}

int Tile::getTileY() const
{
    return yTile;
}

double Tile::getX() const
{
    return mapBorderOffset + tileWidth / 2 + tileWidth * xTile;
}

double Tile::getY() const
{
    return mapBorderOffset + tileWidth / 2 + tileWidth * yTile;
}

char Tile::getType() const
{
    return tileType;
}

bool Tile::checkPlaceable() const
{
    return placeable;
}

void Tile::switchPlaceable()
{
    placeable = !placeable;
}

/*
void Tile::setData(int x, int y, char type)
{
    xTile = x;
    yTile = y;
    tileType = type;
}
*/

void Tile::setNextTile(shptr<Tile> const tile)
{
    nextTile = tile;
}

shptr<Tile> Tile::getNextTile()
{
    return nextTile;
}

Path::Path(int x, int y, char type)
: Tile{x, y, type}
{
    //setSprite(tileSheet, 2, 1);
}

/*
void Path::setSprite(Spritesheet const& spriteSheet, unsigned xOffset, unsigned yOffset)
{
    if (tileType == pathChar)
    {
        tileSprite = spriteSheet.get_sprite(5 + yOffset, 3 + xOffset);
    }
    else
    {
        tileSprite = spriteSheet.get_sprite(2, 1);
    }

    tileSprite = spriteSheet.get_sprite(yOffset, xOffset);

    tileSprite.setPosition (mapBorderOffset + tileWidth / 2 + tileWidth * xTile,
                            mapBorderOffset + tileWidth / 2 + tileWidth * yTile);
    tileSprite.setOrigin (tileWidth/2, tileWidth/2);

}
*/

void Path::setSprite(Spritesheet const& spriteSheet, unsigned binaryNeighbor)
{
    unsigned xOffset {};
    unsigned yOffset {};

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

    tileSprite = spriteSheet.get_sprite(5 + yOffset, 3 + xOffset);

    tileSprite.setPosition (mapBorderOffset + tileWidth / 2 + tileWidth * xTile,
                            mapBorderOffset + tileWidth / 2 + tileWidth * yTile);
    tileSprite.setOrigin (tileWidth/2, tileWidth/2);
}

Grass::Grass(int x, int y, char type)
: Tile{x, y, type}
{
    placeable = true;
    //setSprite(tileSheet, 1, 1);
}

void Grass::setSprite(Spritesheet const& spriteSheet, unsigned binaryNeighbor)
{
    tileSprite = spriteSheet.get_sprite(2, 1);

    tileSprite.setPosition (mapBorderOffset + tileWidth / 2 + tileWidth * xTile,
                            mapBorderOffset + tileWidth / 2 + tileWidth * yTile);
    tileSprite.setOrigin (tileWidth/2, tileWidth/2);
}

Water::Water(int x, int y, char type)
: Tile{x, y, type}
{
    placeable = true;
    //setSprite(tileSheet, 1, 1);
}

void Water::setSprite(Spritesheet const& spriteSheet, unsigned binaryNeighbor)
{
    unsigned xOffset {};
    unsigned yOffset {};

    if (binaryNeighbor == 2 || binaryNeighbor == 6 || binaryNeighbor == 10 ||
        binaryNeighbor == 12 || binaryNeighbor == 14)
        xOffset = 0;
    else if (binaryNeighbor == 0 || binaryNeighbor == 4 || binaryNeighbor == 7 ||
             binaryNeighbor == 8 || binaryNeighbor == 11 || binaryNeighbor == 15)
        xOffset = 1;
    else if (binaryNeighbor == 1 || binaryNeighbor == 3 || binaryNeighbor == 5 ||
             binaryNeighbor == 9 || binaryNeighbor == 13)
        xOffset = 2;

    if (binaryNeighbor <= 9 && binaryNeighbor == 11)
        yOffset = 0;
    else if (binaryNeighbor >= 13 && binaryNeighbor <= 15)
        yOffset = 1;
    else if (binaryNeighbor >= 5 && binaryNeighbor <= 7)
        yOffset = 2;
    else if (binaryNeighbor == 3 || binaryNeighbor == 8 || binaryNeighbor == 12)
        yOffset = 3;
    else if (binaryNeighbor >= 0 && binaryNeighbor <= 2)
        yOffset = 4;
    else if (binaryNeighbor == 4)
        yOffset = 5;

    tileSprite = tileSheet.get_sprite(yOffset, xOffset);

    tileSprite.setPosition (mapBorderOffset + tileWidth / 2 + tileWidth * xTile,
                            mapBorderOffset + tileWidth / 2 + tileWidth * yTile);
    tileSprite.setOrigin (tileWidth/2, tileWidth/2);
}