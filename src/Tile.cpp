#include "constants.h"
#include "Spritesheet.h"
#include "Tile.h"
#include <memory>

/*
 *  Tile
 */

void Tile::render(sf::RenderTarget &target)
{
    target.draw(tileSprite);
}

int Tile::getTileX() const
{
    return xPos;
}

int Tile::getTileY() const
{
    return yPos;
}

double Tile::getX() const
{
    return mapBorderOffset + tileWidth / 2 + tileWidth * xPos;
}

double Tile::getY() const
{
    return mapBorderOffset + tileWidth / 2 + tileWidth * yPos;
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

void Tile::setData(int x, int y, char type)
{
    xPos = x;
    yPos = y;
    tileType = type;
    placeable = (tileType == placeableChar);
}

void Tile::setSprite(Spritesheet const& spriteSheet, unsigned xOffset, unsigned yOffset)
{
    if (tileType == pathChar)
    {
        tileSprite = spriteSheet.get_sprite(5 + yOffset, 3 + xOffset);
    }
    else if (tileType == placeableChar)
    {
        tileSprite = spriteSheet.get_sprite(5, 1);
    }
    else
    {
        tileSprite = spriteSheet.get_sprite(2, 1);
    }

    tileSprite.setPosition (mapBorderOffset + tileWidth / 2 + tileWidth * xPos,
                            mapBorderOffset + tileWidth / 2 + tileWidth * yPos);
    tileSprite.setOrigin (tileWidth/2, tileWidth/2);

}

void Tile::setNextTile(shptr<Tile> const tile)
{
    nextTile = tile;
}

shptr<Tile> Tile::getNextTile()
{
    return nextTile;
}