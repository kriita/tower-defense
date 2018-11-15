#include "map.h"
#include "tile.h"

using namespace std;

#include "catch.hpp"

TEST_CASE("Create map")
{
    Map m {"map.dat"};
    CHECK(m.getTile(1, 1)->getX() == 1);
    CHECK(m.getTile(1, 1)->getY() == 1);
    CHECK(m.getTile(3, 5)->getX() == 3);
    CHECK(m.getTile(3, 5)->getY() == 5);

    CHECK(m.getSpawnPoint()->getX() == 3);
    CHECK(m.getSpawnPoint()->getY() == 0);
    CHECK(m.getEndPoint()->getX() == 5);
    CHECK(m.getEndPoint()->getY() == 14);

    CHECK(m.getSpawnPoint()->getNextTile()->getY() == 3);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getX() == 16);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getX() == 16);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getY() == 9);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getNextTile()->getX() == 3);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getNextTile()->getY() == 9);
    CHECK(m.getTile(12, 6)->getNextTile()->getX() == 12);
    CHECK(m.getTile(12, 6)->getNextTile()->getY() == 11);
    CHECK(m.getTile(5, 11)->getNextTile() == m.getEndPoint());
    CHECK(m.getTile(5, 14) == m.getEndPoint());
}