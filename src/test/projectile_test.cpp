
#include "Projectile.h"
#include "defs.h"
#include "Monster.h"
#include "catch.hpp"

#include <SFML/Graphics.hpp>

using namespace std;
// Testing of Projectile::getTarget() works if class Monster in Projectile.h
// is discommented and Monster.h is not included.


TEST_CASE("Testing of Projectile::getTarget()")
{
    Projectile myProj {};
    
    CHECK_FALSE(myProj.getTarget());    // myProj should not have a target
    CHECK_FALSE(dynamic_cast<Monster*> ((myProj.getTarget()).get()));
    shptr<Monster> monsterptr = make_shared<ProjectileTarget>();
    myProj.setTarget(monsterptr);
    CHECK(dynamic_cast<Monster*> ((myProj.getTarget()).get())); // myProj should
    CHECK(myProj.getTarget());                                  // have a target
    myProj.setTarget(nullptr);
    CHECK_FALSE(myProj.getTarget());    // myProj should no longer have a target
    CHECK_FALSE(dynamic_cast<Monster*> ((myProj.getTarget()).get()));
}
