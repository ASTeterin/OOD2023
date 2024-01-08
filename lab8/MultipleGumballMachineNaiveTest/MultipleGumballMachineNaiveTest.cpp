#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../MultyGumballMachine/GumBallMachineWithState.h"
#include "../MultyGumballMachine/NaiveGumBallMachine.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

SCENARIO("test gumble machine creation state with 0 coins")
{
	ostringstream out;
	with_state::CGumballMachine m(0);

	auto stdoutBuffer = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	m.InsertQuarter();
	m.TurnCrank();
	m.EjectQuarter();
	std::cout.rdbuf(stdoutBuffer);
	REQUIRE(out.str() == "You can't insert a quarter, the machine is sold out\n"
						 "You turned but there's no gumballs\n"
						 "No gumball dispensed\n"
						 "You can't eject, you haven't inserted a quarter yet\n");

	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
							"C++-enabled Standing Gumball Model #2016 (with state)\n"
							"Inventory: 0 gumballs\n"
							"Bank: 0 quarters\n"
							"Machine is sold out\n");
}

SCENARIO("test gumble machine creation state with 5 coins")
{
	ostringstream out;
	with_state::CGumballMachine m(5);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
							"C++-enabled Standing Gumball Model #2016 (with state)\n"
							"Inventory: 5 gumballs\n"
							"Bank: 0 quarters\n"
							"Machine is waiting for quarter\n");
}

SCENARIO("test state gumble machine insert 1 quarter and turn")
{
	ostringstream out;
	with_state::CGumballMachine m(5);

	auto stdoutBuffer = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	m.InsertQuarter();
	m.TurnCrank();
	std::cout.rdbuf(stdoutBuffer);
	REQUIRE(out.str() == "You inserted a quarter\n"
						 "You turned...\n"
						 "A gumball comes rolling out the slot...\n");

	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
							"C++-enabled Standing Gumball Model #2016 (with state)\n"
							"Inventory: 4 gumballs\n"
							"Bank: 0 quarters\n"
							"Machine is waiting for quarter\n");
}

SCENARIO("test state gumble machine insert 2 quarter and turn")
{
	ostringstream out;
	with_state::CGumballMachine m(5);

	auto stdoutBuffer = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	m.InsertQuarter();
	m.InsertQuarter();
	m.TurnCrank();
	std::cout.rdbuf(stdoutBuffer);
	REQUIRE(out.str() == "You inserted a quarter\n"
						 "You inserted a quarter\n"
						 "You turned...\n"
						 "A gumball comes rolling out the slot...\n");

	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
							"C++-enabled Standing Gumball Model #2016 (with state)\n"
							"Inventory: 4 gumballs\n"
							"Bank: 1 quarter\n"
							"Machine is waiting for turn of crank\n");
}

SCENARIO("test state gumble machine eject Quarter")
{
	ostringstream out;
	with_state::CGumballMachine m(5);

	auto stdoutBuffer = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.EjectQuarter();
	std::cout.rdbuf(stdoutBuffer);
	REQUIRE(out.str() == "You inserted a quarter\n"
						 "You turned...\n"
						 "A gumball comes rolling out the slot...\n"
						 "You inserted a quarter\n"
						 "Quarter returned\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
							"C++-enabled Standing Gumball Model #2016 (with state)\n"
							"Inventory: 4 gumballs\n"
							"Bank: 0 quarters\n"
							"Machine is waiting for quarter\n");
}

SCENARIO("test state gumble machine insert 3")
{
	ostringstream out;
	with_state::CGumballMachine m(3);

	auto stdoutBuffer = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	std::cout.rdbuf(stdoutBuffer);
	REQUIRE(out.str() == "You inserted a quarter\n"
						 "You turned...\n"
						 "A gumball comes rolling out the slot...\n"
						 "You inserted a quarter\n"
						 "You turned...\n"
						 "A gumball comes rolling out the slot...\n"
						 "You inserted a quarter\n"
						 "You turned...\n"
						 "A gumball comes rolling out the slot...\n"
						 "Oops, out of gumballs\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
							"C++-enabled Standing Gumball Model #2016 (with state)\n"
							"Inventory: 0 gumballs\n"
							"Bank: 0 quarters\n"
							"Machine is sold out\n");
}

SCENARIO("test state gumble machine insert coin when out of gumballs")
{
	ostringstream out;
	with_state::CGumballMachine m(1);
	auto stdoutBuffer = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	std::cout.rdbuf(stdoutBuffer);
	REQUIRE(out.str() == "You inserted a quarter\n"
						 "You turned...\n"
						 "A gumball comes rolling out the slot...\n"
						 "Oops, out of gumballs\n"
						 "You can't insert a quarter, the machine is sold out\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
							"C++-enabled Standing Gumball Model #2016 (with state)\n"
							"Inventory: 0 gumballs\n"
							"Bank: 0 quarters\n"
							"Machine is sold out\n");
}

SCENARIO("test state gumble machine turn without a coin")
{
	ostringstream out;
	with_state::CGumballMachine m(1);
	auto stdoutBuffer = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	m.TurnCrank();
	std::cout.rdbuf(stdoutBuffer);
	REQUIRE(out.str() == "You turned but there's no quarter\n"
						 "You need to pay first\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
							"C++-enabled Standing Gumball Model #2016 (with state)\n"
							"Inventory: 1 gumball\n"
							"Bank: 0 quarters\n"
							"Machine is waiting for quarter\n");
}

SCENARIO("test eject not insertet quarter")
{
	ostringstream out;
	with_state::CGumballMachine m(5);

	auto stdoutBuffer = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	m.InsertQuarter();
	m.EjectQuarter();
	m.EjectQuarter();
	std::cout.rdbuf(stdoutBuffer);
	REQUIRE(out.str() == "You inserted a quarter\n"
						 "Quarter returned\n"
						 "You haven't inserted a quarter\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
							"C++-enabled Standing Gumball Model #2016 (with state)\n"
							"Inventory: 5 gumballs\n"
							"Bank: 0 quarters\n"
							"Machine is waiting for quarter\n");
}
