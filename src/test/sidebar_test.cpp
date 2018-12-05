#include "Sidebar.h"
#include "Resource_Window.h"

#include "catch.hpp"

TEST_CASE("Sidebar Construction Test")
{
	Sidebar testSidebar {12};

	CHECK(testSidebar.getX() == 12);
}