#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

struct WeatherIndicatorInfo
{
	double maxValue = -std::numeric_limits<double>::infinity();
	double minValue = std::numeric_limits<double>::infinity();;
	double accumulatedValue = 0;
	double measurementsNumber = 0;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Temperature: " << std::endl;
		UpdateIndicator(m_temperature, data.temperature);

		std::cout << "Humidity: " << std::endl;
		UpdateIndicator(m_humidity, data.humidity);


		std::cout << "Pressure: " << std::endl;
		UpdateIndicator(m_pressure, data.pressure);

	}

	void UpdateIndicator(WeatherIndicatorInfo& statData, double indicatorValue)
	{
		if (statData.minValue > indicatorValue)
		{
			statData.minValue = indicatorValue;
		}
		if (statData.maxValue < indicatorValue)
		{
			statData.maxValue = indicatorValue;
		}
		statData.accumulatedValue += indicatorValue;
		++statData.measurementsNumber;

		std::cout << "Max value " << statData.maxValue << std::endl;
		std::cout << "Min value " << statData.minValue << std::endl;
		std::cout << "Average value " << (statData.accumulatedValue / statData.measurementsNumber) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	WeatherIndicatorInfo m_temperature;
	WeatherIndicatorInfo m_pressure;
	WeatherIndicatorInfo m_humidity;

};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
};
