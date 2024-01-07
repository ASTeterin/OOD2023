#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task1/modernGraphicsLibAdapter.h"
#include <sstream>

TEST_CASE("Check drawing line")
{
	std::stringstream ss;
	
	modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
	CModernGraphicsLibAdapter adapter(renderer);

	renderer.BeginDraw();
	adapter.MoveTo(5, 5);
	adapter.LineTo(10, 20);
	renderer.EndDraw();
	

	CHECK(ss.str() == "<draw>\n<line fromX=5 fromY=5 toX=10 toY=20 />\n</draw>\n");
}

TEST_CASE("Check drawing line without EndDraw()")
{
	std::stringstream ss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
	CModernGraphicsLibAdapter adapter(renderer);
	renderer.BeginDraw();
	adapter.MoveTo(5, 5);
	adapter.LineTo(10, 20);

	CHECK(ss.str() == "<draw>\n<line fromX=5 fromY=5 toX=10 toY=20 />\n");
}


TEST_CASE("Check drawing line without BeginDraw()")
{
	std::stringstream ss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
	CModernGraphicsLibAdapter adapter(renderer);

	adapter.MoveTo(0, 0);


	CHECK_THROWS(adapter.LineTo(10, 20));
}

TEST_CASE("Call two methods beginDraw()")
{
	std::stringstream ss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
	CModernGraphicsLibAdapter adapter(renderer);
	renderer.BeginDraw();
	adapter.MoveTo(0, 0);
	adapter.LineTo(10, 20);

	CHECK_THROWS(renderer.BeginDraw());
}

TEST_CASE("Call endDraw() without calling BeginDraw()")
{
	std::stringstream ss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
	CModernGraphicsLibAdapter adapter(renderer);

	CHECK_THROWS(renderer.EndDraw());
}

TEST_CASE("Check drawing line without moveTo")
{
	std::stringstream ss;
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
		CModernGraphicsLibAdapter adapter(renderer);
		renderer.BeginDraw();
		adapter.LineTo(10, 20);
		renderer.EndDraw();
	}

	CHECK(ss.str() == "<draw>\n<line fromX=0 fromY=0 toX=10 toY=20 />\n</draw>\n");
}