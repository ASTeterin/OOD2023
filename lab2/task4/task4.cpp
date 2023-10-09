#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "WeatherData.h"


SCENARIO("test duo station")
{
	CWeatherData wdIn("inside");
	CWeatherData wdOut("outside");
	CDisplay display;
	CStatsDisplay statDisplay;

	wdIn.RegisterObserver(display);
	wdOut.RegisterObserver(display);
	wdIn.RegisterObserver(statDisplay);
	wdOut.RegisterObserver(statDisplay);

	wdIn.SetMeasurements(20, 0.7, 760);
	wdOut.SetMeasurements(0, 0.5, 740);
	wdIn.SetMeasurements(26, 0.4, 750);
	wdOut.SetMeasurements(-10, 0.2, 766);
	
	REQUIRE(statDisplay.GetTemperature(wdIn.GetName()).GetMaxValue() == 26);
	REQUIRE(statDisplay.GetTemperature(wdIn.GetName()).GetMinValue() == 20);
	REQUIRE(statDisplay.GetTemperature(wdIn.GetName()).GetAvarageValue() == 23);

	REQUIRE(statDisplay.GetHumidity(wdIn.GetName()).GetMaxValue() == 0.7);
	REQUIRE(statDisplay.GetHumidity(wdIn.GetName()).GetMinValue() == 0.4);
	REQUIRE(statDisplay.GetHumidity(wdIn.GetName()).GetAvarageValue() == 0.55);

	REQUIRE(statDisplay.GetPressure(wdIn.GetName()).GetMaxValue() == 760);
	REQUIRE(statDisplay.GetPressure(wdIn.GetName()).GetMinValue() == 750);
	REQUIRE(statDisplay.GetPressure(wdIn.GetName()).GetAvarageValue() == 755);

	REQUIRE(statDisplay.GetTemperature(wdOut.GetName()).GetMaxValue() == 0);
	REQUIRE(statDisplay.GetTemperature(wdOut.GetName()).GetMinValue() == -10);
	REQUIRE(statDisplay.GetTemperature(wdOut.GetName()).GetAvarageValue() == -5);

	REQUIRE(statDisplay.GetHumidity(wdOut.GetName()).GetMaxValue() == 0.5);
	REQUIRE(statDisplay.GetHumidity(wdOut.GetName()).GetMinValue() == 0.2);
	REQUIRE(statDisplay.GetHumidity(wdOut.GetName()).GetAvarageValue() == 0.35);

	REQUIRE(statDisplay.GetPressure(wdOut.GetName()).GetMaxValue() == 766);
	REQUIRE(statDisplay.GetPressure(wdOut.GetName()).GetMinValue() == 740);
	REQUIRE(statDisplay.GetPressure(wdOut.GetName()).GetAvarageValue() == 753);
}