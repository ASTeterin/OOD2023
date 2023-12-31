﻿#define CATCH_CONFIG_MAIN
#include <sstream>
#include "../task2/modernGraphicsLibAdapter.h"
#include "../../../Catch2/catch.hpp"

TEST_CASE("check drawing line")
{
	std::stringstream ss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
	{
		CModernGraphicsLibAdapter adapter(ss);

		adapter.MoveTo(1, 1);
		adapter.LineTo(10, 20);
	}

	CHECK(ss.str() == "<draw>\n<line fromX=1 fromY=1 toX=10 toY=20 />\n</draw>\n");
}

TEST_CASE("check drawing without destructor")
{
	std::stringstream ss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
	CModernGraphicsLibAdapter adapter(ss);

	adapter.MoveTo(1, 1);
	adapter.LineTo(10, 20);


	CHECK(ss.str() == "<draw>\n<line fromX=1 fromY=1 toX=10 toY=20 />\n");
}

TEST_CASE("check drawing line without MoveTo")
{
	std::stringstream ss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
	{
		CModernGraphicsLibAdapter adapter(ss);

		adapter.LineTo(10, 20);
	}

	CHECK(ss.str() == "<draw>\n<line fromX=0 fromY=0 toX=10 toY=20 />\n</draw>\n");
}