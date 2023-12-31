﻿#pragma once
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

//выделить в отдельный класс 
class WeatherIndicatorStorage
{
public:
	double GetMaxValue(double currentValue)
	{
		if (m_maxValue < currentValue)
		{
			m_maxValue = currentValue;
		}

		return m_maxValue;
	}

	double GetMinValue(double currentValue)
	{
		if (m_minValue > currentValue)
		{
			m_minValue = currentValue;
		}
		return m_minValue;
	}

	double GetAvarageValue(double currentValue)
	{
		m_accumulatedValue += currentValue;
		++m_measurementsNumber;
		return m_accumulatedValue / m_measurementsNumber;
	}

private:
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_minValue = std::numeric_limits<double>::infinity();;
	double m_accumulatedValue = 0;
	double m_measurementsNumber = 0;
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
public:
	CStatsDisplay(WeatherIndicatorStorage temperatureStorage, WeatherIndicatorStorage pressureStorage, WeatherIndicatorStorage humidityStorage)
	{
		m_temperatureStorage = temperatureStorage;
		m_pressureStorage = pressureStorage;
		m_humidityStorage = humidityStorage;
	}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Temperature: " << std::endl;
		UpdateIndicator(m_temperatureStorage, data.temperature);

		std::cout << "Humidity: " << std::endl;
		UpdateIndicator(m_humidityStorage, data.humidity);

		std::cout << "Pressure: " << std::endl;
		UpdateIndicator(m_pressureStorage, data.pressure);
	}

	void UpdateIndicator(WeatherIndicatorStorage& storage, double indicatorValue)
	{
		std::cout << "Max value " << storage.GetMaxValue(indicatorValue) << std::endl;
		std::cout << "Min value " << storage.GetMinValue(indicatorValue) << std::endl;
		std::cout << "Average value " << storage.GetAvarageValue(indicatorValue) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	WeatherIndicatorStorage m_temperatureStorage;
	WeatherIndicatorStorage m_pressureStorage;
	WeatherIndicatorStorage m_humidityStorage;
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
