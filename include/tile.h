#ifndef TILE_H
#define TILE_H

/*
 *  Tile
 */
class Tile
{
public:
    Tile() = default;
    ~Tile() = default;

    int getX() const;
    int getY() const;
    int getType() const;
    void setData(int x, int y, int t);
    void setNextTile(Tile* const tile);
    Tile* getNextTile();
    bool checkOnPath() const;

private:
    int xPos {};
    int yPos {};
    int type {};
    Tile* nextTile {};
};

#endif