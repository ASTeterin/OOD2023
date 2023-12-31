﻿#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "WeatherData.h"

class CMockDisplay : public IObserver<SWeatherInfo>
{
public:
	CMockDisplay(CWeatherData& wd)
		: m_wd(&wd)
	{
	}

private:
	void Update(SWeatherInfo const& data) override
	{
		m_wd->RemoveObserver(*this);
	}

	CWeatherData* m_wd;
};

SCENARIO("Delete during update test")
{
	CWeatherData wd;
	CMockDisplay mockDisplay(wd);
	wd.RegisterObserver(mockDisplay);

	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);

	REQUIRE_NOTHROW(wd.SetMeasurements(10, 0.8, 761));
	REQUIRE_NOTHROW(wd.SetMeasurements(-10, 0.3, 756));
}