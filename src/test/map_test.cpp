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

    //CHECK(m.getSpawnPoint()->checkOnPath() == true);
    CHECK(m.getSpawnPoint()->getNextTile()->getY() == 1);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getY() == 2);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getX() == 3);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getY() == 3);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getNextTile()->getX() == 4);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getNextTile()->getY() == 3);

    CHECK(m.getEndPoint()->getX() == 5);
    CHECK(m.getEndPoint()->getY() == 14);
}