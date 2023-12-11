#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task1/modernGraphicsLibAdapter.h"
#include <sstream>

TEST_CASE("Check drawing line")
{
	std::stringstream ss;
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
		CModernGraphicsLibAdapter adapter(renderer);

		adapter.MoveTo(0, 0);
		adapter.LineTo(10, 20);
	}

	CHECK(ss.str() == "<draw>\n<line fromX=0 fromY=0 toX=10 toY=20 />\n</draw>\n");
}

TEST_CASE("Check drawing line without destructor")
{
	std::stringstream ss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
	CModernGraphicsLibAdapter adapter(renderer);

	adapter.MoveTo(0, 0);
	adapter.LineTo(10, 20);


	CHECK(ss.str() == "<draw>\n<line fromX=0 fromY=0 toX=10 toY=20 />\n");
}

TEST_CASE("Check drawing line after destroy")
{
	std::stringstream ss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
	{
		CModernGraphicsLibAdapter adapter(renderer);

		adapter.MoveTo(0, 0);
		adapter.LineTo(10, 20);
	}

	CHECK_THROWS(renderer.DrawLine({ 0, 0 }, { 10, 20 }));
}