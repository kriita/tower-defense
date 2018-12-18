#ifndef TILE_H
#define TILE_H

#include "defs.h"
#include "Spritesheet.h"
#include <SFML/Graphics.hpp>
#include <vector>

/*
 *  Tile
 * 
 *  Responsible for one of the maps' tiles.
 *  Has subclasses for different types of tiles which are:
 *  path
 *  grass
 *  water
 *  tree
 */
class Tile
{
public:
    Tile(int x, int y, char type);
    Tile(Tile const&) = delete;
    virtual ~Tile() = default;

    void render(sf::RenderTarget &target) const;
    void virtual update() = 0;
    void resize(float xNew, float yNew, float scale);
    int getTileX() const;
    int getTileY() const;
    double getX() const;
    double getY() const;
    char getType() const;
    bool checkPlaceable() const;
    bool checkAnimated() const;
    void switchPlaceable();
    void setNextTile(shptr<Tile> const tile);
    shptr<Tile> getNextTile() const;
    void setSheetOffset(std::vector<bool> bin);
    void setPathSheetOffset(std::vector<bool> bin);
    void setTileSprite(sf::Sprite sprite);
    virtual void setSprite(std::vector<bool> bin) = 0;

    Tile& operator = (Tile const&) = delete;

protected:
    int xTile {};
    int yTile {};
    unsigned xOffset {};
    unsigned yOffset {};
    char tileType {};
    bool placeable {false};
    bool animated {false};
    shptr<Tile> nextTile {};

    sf::Sprite tileSprite {};
};

/*
 *  Tile -> Path
 */
class Path : public Tile
{
public:
    Path(int x, int y, char type);
    void setSprite(std::vector<bool> bin) override;
    void update() override {};

private:
    Spritesheet tileSheet {"resources/images/path.png", 32, 32};
};

/*
 *  Tile -> Grass
 */
class Grass : public Tile
{
public:
    Grass(int x, int y, char type);
    void setSprite(std::vector<bool> bin) override;
    void update() override {};

private:
    Spritesheet tileSheet {"resources/images/grass.png", 32, 32};
};

/*
 *  Tile -> Tree
 */
class Tree : public Tile
{
public:
    Tree(int x, int y, char type);
    void setSprite(std::vector<bool> bin) override;
    void update() override {};

private:
    Spritesheet tileSheet {"resources/images/tree.png", 32, 32};
};

/*
 *  Tile -> Water
 */
class Water : public Tile
{
public:
    Water(int x, int y, char type);
    void setSprite(std::vector<bool> bin) override;
    void update() override;

private:
    Spritesheet tileSheet {"resources/images/water.png", 32, 32};
    sf::Clock animClock {};
};

#endif