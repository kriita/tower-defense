#include "map.h"
#include "tile.h"

using namespace std;

#include "catch.hpp"

TEST_CASE("Create map")
{
    Map m {"map.dat"};
    CHECK(m.getTile(1, 1)->getX() == 1);
    CHECK(m.getTile(3, 1)->getX() == 3);

    CHECK(m.getSpawnPoint()->getX() == 3);
    CHECK(m.getSpawnPoint()->getY() == 0);
    CHECK(m.getEndPoint()->getX() == 5);
    CHECK(m.getEndPoint()->getY() == 14);

    CHECK(m.getSpawnPoint()->getNextTile()->getY() == 1);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getY() == 2);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getX() == 3);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getY() == 3);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getNextTile()->getX() == 4);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getNextTile()->getY() == 3);
    CHECK(m.getTile(5, 13)->getNextTile() == m.getEndPoint());
    CHECK(m.getTile(5, 14) == m.getEndPoint());

    CHECK(m.getTile(2, 7)->checkOnPath() == false);
    CHECK(m.getTile(3, 7)->checkOnPath() == true);
    CHECK(m.getTile(4, 7)->checkOnPath() == false);
}