#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

/*
 *  Tile
 */
class Tile
{
public:
    Tile();
    Tile(Tile const&) = default;
    ~Tile() = default;

    void render(sf::RenderWindow &window);
    int getX() const;
    int getY() const;
    char getType() const;
    void setData(int x, int y, char type);
    void setNextTile(Tile* const tile);
    Tile* getNextTile();

    Tile& operator = (Tile const &t) = default;

private:
    int xPos {};
    int yPos {};
    char tileType {};
    Tile* nextTile {};

    sf::RectangleShape tileRect {};
};

#endif