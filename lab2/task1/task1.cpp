#include "WeatherData.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display);

	WeatherIndicatorStorage temperatureStorage;
	WeatherIndicatorStorage pressureStorage;
	WeatherIndicatorStorage humidityStorage;
	CStatsDisplay statsDisplay(temperatureStorage, pressureStorage, humidityStorage);
	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760);
	wd.SetMeasurements(4, 0.8, 761);
	wd.SetMeasurements(8, 0.2, 750);

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761);
	wd.SetMeasurements(-10, 0.8, 761);
	return 0;
}