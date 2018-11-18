#include "tile.h"
#include "constants.h"

/*
 *  Tile
 */

void Tile::render(sf::RenderTarget &target)
{
    target.draw(tileSprite);
}

int Tile::getX() const
{
    return xPos;
}

int Tile::getY() const
{
    return yPos;
}

char Tile::getType() const
{
    return tileType;
}

void Tile::setData(int x, int y, char type)
{
    xPos = x;
    yPos = y;
    tileType = type;
}

void Tile::setSprite(sf::Texture const& spriteSheet, int xOffset, int yOffset)
{
    tileSprite.setTexture(spriteSheet);
    tileSprite.setPosition (28 + tileWidth*xPos, 28 + tileWidth*yPos);
    tileSprite.setOrigin (tileWidth/2, tileWidth/2);

    if (tileType == '0' || tileType == 'S' || tileType == 'E')
    {
        tileSprite.setTextureRect(sf::IntRect(96 + xOffset*32, 160 + yOffset*32, 32, 32));
    }
    else
    {
        tileSprite.setTextureRect(sf::IntRect(32, 64, 32, 32));
    }
}

void Tile::setNextTile(Tile* const tile)
{
    nextTile = tile;
}

Tile* Tile::getNextTile()
{
    return nextTile;
}