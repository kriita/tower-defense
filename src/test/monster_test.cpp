#include "Monster.h"
#include "defs.h"
#include "Tile.h"
#include "Map.h"

using namespace std;

#include "catch.hpp"



TEST_CASE("Damage and kill")
{
    Map m {"test/map"};
    BrownRabbit testM{m.getSpawnPoint(), 0};
    CHECK(testM.getHealth() == 50);
    testM.takeDamage(10);
    CHECK(testM.getHealth() == 40);
    testM.takeSlowDmg(10, 10, 10, true);
    CHECK(testM.getHealth() == 30);
    testM.takeStunDmg(10, 10, 10, true);
    CHECK(testM.getHealth() == 20); 
    testM.takeCritDamage(10, 0, true);
    CHECK(testM.getHealth() == 10);
    CHECK(testM.isDead() == false);    
    testM.takeCritDamage(10, 1, true);
    CHECK(testM.getHealth() <= 0);       
    CHECK(testM.isDead() == true);
    CHECK(testM.shallLoseHP() == false);
}

TEST_CASE("Next Test")
{
    Map m {"test/map"};
    WhiteRabbit testM{m.getSpawnPoint(), 0};
    CHECK(testM.getType() == "WhiteRabbit"); 
    CHECK(testM.getSpeed() == 1); 
    CHECK(testM.getHealth() == 501); 
    testM.setLevel(5);
    CHECK(testM.getSpeed() == 0.5);
    CHECK(testM.getHealth() == 25000); 
}