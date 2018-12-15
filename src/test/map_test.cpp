#include "Map.h"
#include "Tile.h"

using namespace std;

#include "catch.hpp"

TEST_CASE("Normal map")
{
    Map m {"test/map"};

    CHECK(m.getTile(1, 1)->getTileX() == 1);
    CHECK(m.getTile(1, 1)->getTileY() == 1);
    CHECK(m.getTile(3, 5)->getTileX() == 3);
    CHECK(m.getTile(3, 5)->getTileY() == 5);

    CHECK(m.getSpawnPoint()->getTileX() == 3);
    CHECK(m.getSpawnPoint()->getTileY() == 0);
    CHECK(m.getEndPoint()->getTileX() == 5);
    CHECK(m.getEndPoint()->getTileY() == 17);

    CHECK(m.getSpawnPoint()->getNextTile()->getTileY() == 3);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getTileX() == 16);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getTileX() == 16);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getTileY() == 9);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getNextTile()->getTileX() == 3);
    CHECK(m.getSpawnPoint()->getNextTile()->getNextTile()->getNextTile()->getNextTile()->getTileY() == 9);
    CHECK(m.getTile(12, 6)->getNextTile()->getTileX() == 12);
    CHECK(m.getTile(12, 6)->getNextTile()->getTileY() == 11);
    CHECK(m.getTile(5, 11)->getNextTile() == m.getEndPoint());
    CHECK(m.getTile(5, 17) == m.getEndPoint());

    // Out of bounds coordinates
    REQUIRE_THROWS_AS(m.getTile(0, 40), MapError);
    REQUIRE_THROWS_AS(m.getTile(40, 0), MapError);
    REQUIRE_THROWS_AS(m.getTile(40, 40), MapError);
}

TEST_CASE("Error throws")
{
    // Incorrect map file name
    REQUIRE_THROWS_AS(make_unique<Map>("239867230476slodhnirgsldfhndsjk"), MapError);

    // Incorrect line length
    REQUIRE_THROWS_AS(make_unique<Map>("test/1"), MapError);

    // No spawn point
    REQUIRE_THROWS_AS(make_unique<Map>("test/2"), MapError);

    // No end point
    REQUIRE_THROWS_AS(make_unique<Map>("test/3"), MapError);

    // Multiple spawn points
    REQUIRE_THROWS_AS(make_unique<Map>("test/4"), MapError);

    // Multiple end points
    REQUIRE_THROWS_AS(make_unique<Map>("test/5"), MapError);
}