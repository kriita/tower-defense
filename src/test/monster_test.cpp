#include "Monster.h"
#include "defs.h"
#include "Tile.h"

using namespace std;

#include "catch.hpp"

TEST_CASE("asdfasdf")
{
    Map m {"test/map"};
    shptr<Monster> testMonster = BrownRabbit(m->getSpawnPoint());
    
}