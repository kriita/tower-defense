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
{}

void Tile::render(sf::RenderTarget &target)
{
    target.draw(tileSprite);
}

void Tile::resize(float xNew, float yNew, float scale)
{
    tileSprite.scale(scale, scale);
    tileSprite.setPosition(xNew + (xTile - xTilesMax / 2) * tileWidth * scale,
                           yNew + (yTile - yTilesMax / 2) * tileWidth * scale);
    std::cout << xNew + (xTile - xTilesMax / 2) * tileWidth * scale << " "
        << yNew + (yTile - yTilesMax / 2) * tileWidth * scale << "\n";
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

bool Tile::checkAnimated() const
{
    return animated;
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

void Tile::setSheetOffset(vector<bool> bin)
{
    if (!bin[1] && !bin[3] && bin[4] && bin[6])         { yOffset = 0; xOffset = 0; }
    else if (!bin[1] && bin[3] && bin[4] && bin[6])     { yOffset = 0; xOffset = 1; }
    else if (!bin[1] && bin[3] && !bin[4] && bin[6])    { yOffset = 0; xOffset = 2; }
    else if (bin[1] && !bin[3] && bin[4] && bin[6])     { yOffset = 1; xOffset = 0; }
    else if (bin[1] && bin[3] && !bin[4] && bin[6])     { yOffset = 1; xOffset = 2; }
    else if (bin[1] && !bin[3] && bin[4] && !bin[6])    { yOffset = 2; xOffset = 0; }
    else if (bin[1] && bin[3] && bin[4] && !bin[6])     { yOffset = 2; xOffset = 1; }
    else if (bin[1] && bin[3] && !bin[4] && !bin[6])    { yOffset = 2; xOffset = 2; }
    else if (bin[1] && !bin[3] && !bin[4] && bin[6])    { yOffset = 6; xOffset = 0; }
    else if (bin[1] && bin[3] && bin[4] && !bin[6])     { yOffset = 3; xOffset = 1; }
    else if (!bin[1] && bin[3] && bin[4] && !bin[6])    { yOffset = 7; xOffset = 0; }
    else if (!bin[1] && !bin[3] && bin[4] && !bin[6])   { yOffset = 4; xOffset = 0; }
    else if (!bin[1] && !bin[3] && !bin[4] && !bin[6])  { yOffset = 4; xOffset = 1; }
    else if (bin[1] && !bin[3] && !bin[4] && !bin[6])   { yOffset = 4; xOffset = 2; }
    else if (!bin[1] && bin[3] && !bin[4] && !bin[6])   { yOffset = 7; xOffset = 0; }
    else if (!bin[0] && bin[2] && bin[5] && bin[7])     { yOffset = 3; xOffset = 0; }
    else if (bin[0] && !bin[2] && bin[5] && bin[7])     { yOffset = 3; xOffset = 2; }
    else if (bin[0] && bin[2] && !bin[5] && bin[7])     { yOffset = 5; xOffset = 0; }
    else if (bin[0] && bin[2] && bin[5] && !bin[7])     { yOffset = 5; xOffset = 2; }
    else if (!bin[0] && bin[2] && !bin[5] && bin[7])    { yOffset = 6; xOffset = 1; }
    else if (!bin[0] && !bin[2] && bin[5] && bin[7])    { yOffset = 6; xOffset = 2; }
    else if (bin[0] && bin[2] && !bin[5] && !bin[7])    { yOffset = 7; xOffset = 1; }
    else if (bin[0] && !bin[2] && bin[5] && !bin[7])    { yOffset = 7; xOffset = 2; }
    else                                                { yOffset = 1; xOffset = 1; }
}

void Tile::setPathSheetOffset(vector<bool> bin)
{
    if (!bin[1] && !bin[3] && bin[4] && bin[6])             { yOffset = 0; xOffset = 0; }
    else if (!bin[1] && bin[3] && !bin[4] && bin[6])        { yOffset = 0; xOffset = 2; }
    else if (bin[1] && bin[3] && bin[4] && bin[6])          { yOffset = 1; xOffset = 1; }
    else if (bin[1] && !bin[3] && bin[4] && !bin[6])        { yOffset = 2; xOffset = 0; }
    else if (bin[1] && bin[3] && !bin[4] && !bin[6])        { yOffset = 2; xOffset = 2; }
    else if ((bin[1] && !bin[3] && !bin[4] && bin[6]) ||
             (bin[1] && !bin[3] && !bin[4] && !bin[6]) ||
             (!bin[1] && !bin[3] && !bin[4] && bin[6]))     { yOffset = 3; xOffset = 0; }
    else if ((!bin[1] && bin[3] && bin[4] && !bin[6]) ||
             (!bin[1] && !bin[3] && bin[4] && !bin[6]) ||
             (!bin[1] && bin[3] && !bin[4] && !bin[6]))     { yOffset = 3; xOffset = 2; }
}

void Tile::setTileSprite(sf::Sprite sprite)
{
    tileSprite = sprite;
    tileSprite.setPosition (mapBorderOffset + tileWidth / 2 + tileWidth * xTile,
                            mapBorderOffset + tileWidth / 2 + tileWidth * yTile);
    tileSprite.setOrigin (tileWidth/2, tileWidth/2);
}

/*
 *  Tile -> Path
 */
Path::Path(int x, int y, char type)
: Tile{x, y, type}
{}

void Path::setSprite(vector<bool> bin)
{
    setPathSheetOffset(bin);
    setTileSprite(tileSheet.get_sprite(yOffset, xOffset));
}

/*
 *  Tile -> Grass
 */
Grass::Grass(int x, int y, char type)
: Tile{x, y, type}
{
    placeable = true;
}

void Grass::setSprite(vector<bool> bin)
{
    bin[0] = 0;
    setTileSprite(tileSheet.get_sprite(1, 1));
}

/*
 *  Tile -> Tree
 */
Tree::Tree(int x, int y, char type)
: Tile{x, y, type}
{}

void Tree::setSprite(vector<bool> bin)
{
    setSheetOffset(bin);
    setTileSprite(tileSheet.get_sprite(yOffset, xOffset));
}

/*
 *  Tile -> Water
 */
Water::Water(int x, int y, char type)
: Tile{x, y, type}
{
    animated = true;
}

void Water::setSprite(vector<bool> bin)
{
    setSheetOffset(bin);
    setTileSprite(tileSheet.get_sprite(yOffset, xOffset));
}

void Water::update()
{
    if ((animClock.getElapsedTime()).asSeconds() > 1)
    {
        xOffset = (xOffset + 3) % 6;
        setTileSprite(tileSheet.get_sprite(yOffset, xOffset));
        animClock.restart();
    }
}