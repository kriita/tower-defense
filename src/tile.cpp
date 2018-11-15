#include <SFML/Graphics.hpp>
#include "tile.h"

/*
 *  Tile
 */

Tile::Tile()
{

}

void Tile::render(sf::RenderWindow &window)
{
    window.draw (tileRect);
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

    //
    // Temporärt
    float const w {32.0};

    tileRect.setSize(sf::Vector2f(w, w));
    tileRect.setPosition (150 + w*xPos, 100 + w*yPos);
    tileRect.setOrigin (w/2, w/2);
    if (tileType == '0' || tileType == 'S' || tileType == 'E')
    {
        tileRect.setFillColor (sf::Color(150, 80, 0));
    }
    else if (tileType == '1')
    {
        tileRect.setFillColor (sf::Color(0, 150, 0));
    }
    else if (tileType == '2')
    {
        tileRect.setFillColor (sf::Color(150, 150, 150));
    }
    //
    //
}

void Tile::setNextTile(Tile* const tile)
{
    nextTile = tile;
}

Tile* Tile::getNextTile()
{
    return nextTile;
}