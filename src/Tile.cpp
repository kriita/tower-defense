#include "constants.h"
#include "Spritesheet.h"
#include "Tile.h"
#include <memory>
#include <vector>

#include <iostream>

using std::vector;

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

void Path::setSprite(Spritesheet const& spriteSheet, vector<bool> bin)
{
    unsigned xOffset {};
    unsigned yOffset {};
/*
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
*/
    tileSprite = spriteSheet.get_sprite(6, 4);

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

void Grass::setSprite(Spritesheet const& spriteSheet, vector<bool> bin)
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

void Water::setSprite(Spritesheet const& spriteSheet, vector<bool> bin)
{
    unsigned xOffset {};
    unsigned yOffset {};

    if (!bin[1] && !bin[3] && bin[4] && bin[6])         { yOffset = 0; xOffset = 0; }
    else if (!bin[1] && bin[3] && bin[4] && bin[6])     { yOffset = 0; xOffset = 1; }
    else if (!bin[1] && bin[3] && !bin[4] && bin[6])    { yOffset = 0; xOffset = 2; }
    else if (bin[1] && !bin[3] && bin[4] && bin[6])     { yOffset = 1; xOffset = 0; }
    else if (bin[1] && bin[3] && !bin[4] && bin[6])     { yOffset = 1; xOffset = 2; }
    else if (bin[1] && !bin[3] && bin[4] && !bin[6])    { yOffset = 2; xOffset = 0; }
    else if (bin[1] && bin[3] && bin[4] && !bin[6])     { yOffset = 2; xOffset = 1; }
    else if (bin[1] && bin[3] && !bin[4] && !bin[6])    { yOffset = 2; xOffset = 2; }
    else                                                { yOffset = 1; xOffset = 1; }

    tileSprite = tileSheet.get_sprite(yOffset, xOffset);

    tileSprite.setPosition (mapBorderOffset + tileWidth / 2 + tileWidth * xTile,
                            mapBorderOffset + tileWidth / 2 + tileWidth * yTile);
    tileSprite.setOrigin (tileWidth/2, tileWidth/2);
}