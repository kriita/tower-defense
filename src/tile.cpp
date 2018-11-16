#include <SFML/Graphics.hpp>
#include "tile.h"

/*
 *  Tile
 */

void Tile::render(sf::RenderWindow &window)
{
    window.draw (tileSprite);
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
    float const w {32.0};

    tileSprite.setTexture(spriteSheet);
    tileSprite.setPosition (28 + w*xPos, 28 + w*yPos);
    tileSprite.setOrigin (w/2, w/2);

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