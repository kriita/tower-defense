
#include "Projectile.h"
#include "defs.h"
#include "Monster.h"
#include "catch.hpp"

#include <SFML/Graphics.hpp>

using namespace std;

// Class ProjectilTarget below is only used in testcases (at least until Monster.h is done)

class ProjectileTarget : public Monster
{
    public:
    void loseLife() override {};        // Decreases game life
    void defeat() override {};  
};


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
