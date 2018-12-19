
#include "Projectile.h"
#include "defs.h"
#include "Monster.h"
#include "Tile.h"
#include "constants.h"
#include "catch.hpp"

#include <SFML/Graphics.hpp>

using namespace std;

class TestMonster : public Monster
{
    public:
    TestMonster(shptr<Tile> tile) : Monster(tile) {health = 100;};
};

TEST_CASE("Testing of Projectile::getTarget()")
{
    Projectile myProj {};
    shptr<Tile> tilePointer = make_shared<Path>(32,32, pathChar);
    shptr<Monster> monsterptr = make_shared<TestMonster>(tilePointer);

    CHECK_FALSE(myProj.getTarget());    // myProj should not have a target
    CHECK_FALSE(dynamic_cast<Monster*> ((myProj.getTarget()).get()));
    myProj.setTarget(monsterptr);
    CHECK(dynamic_cast<Monster*> ((myProj.getTarget()).get())); // myProj should
    CHECK(myProj.getTarget());                                  // have a target
    myProj.setTarget(nullptr);
    CHECK_FALSE(myProj.getTarget());    // myProj should no longer have a target
    CHECK_FALSE(dynamic_cast<Monster*> ((myProj.getTarget()).get()));
}


TEST_CASE("Testing of ProjectileError")
{
    Projectile myProj {0, 0, 0, 0, 0};
    REQUIRE_THROWS_AS(myProj.getDirByRadians(), ProjectileError);
}

