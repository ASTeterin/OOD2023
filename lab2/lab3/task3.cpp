#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "WeatherData.h"

class CMockDisplay : public IObserver<SWeatherInfo>
{
public:
	CMockDisplay(std::string name, std::vector<std::string>& priorities)
		: m_name(name)
		, m_priorities(&priorities)
	{
	}

private:
	void Update(SWeatherInfo const& data) override
	{
		m_priorities->push_back(m_name);
	}

	std::string m_name;
	std::vector<std::string>* m_priorities;
};

SCENARIO("test priority")
{
	CWeatherData wd;

	std::vector<std::string> priorities;
	CMockDisplay display1("test1", priorities);
	CMockDisplay display2("test2", priorities);
	CMockDisplay display3("test3", priorities);
	wd.RegisterObserver(display1, 1);
	wd.RegisterObserver(display3, 10);
	wd.RegisterObserver(display2, 2);
	

	wd.SetMeasurements(20, 0.7, 760);

	REQUIRE(priorities[0] == "test3");
	REQUIRE(priorities[1] == "test2");
	REQUIRE(priorities[2] == "test1");
}