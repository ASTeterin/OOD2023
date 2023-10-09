#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	std::string stationName;
};

struct StatData
{
	double maxValue = -std::numeric_limits<double>::infinity();
	double minValue = std::numeric_limits<double>::infinity();
	double averageVlue = 0;
};

//выделить в отдельный класс 
class WeatherIndicatorStorage
{
public:
	void UpdateMaxValue(double currentValue)
	{
		if (m_maxValue < currentValue)
		{
			m_maxValue = currentValue;
		}
	}

	double GetMaxValue()
	{
		return m_maxValue;
	}

	void UpdateMinValue(double currentValue)
	{
		if (m_minValue > currentValue)
		{
			m_minValue = currentValue;
		}
	}

	double GetMinValue()
	{
		return m_minValue;
	}

	void UpdateAverageValue(double currentValue)
	{
		m_accumulatedValue += currentValue;
		++m_measurementsNumber;
	}

	double GetAvarageValue()
	{
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
		std::cout << "Station name " << data.stationName << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	WeatherIndicatorStorage GetTemperature(std::string name)
	{
		return m_temperatureStorage[name];
	}

	WeatherIndicatorStorage GetPressure(std::string name)
	{
		return m_pressureStorage[name];
	}

	WeatherIndicatorStorage GetHumidity(std::string name)
	{
		return m_humidityStorage[name];
	}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		if (m_temperatureStorage.find(data.stationName) == m_temperatureStorage.cend())
		{
			m_temperatureStorage[data.stationName] = WeatherIndicatorStorage();
		}
		if (m_humidityStorage.find(data.stationName) == m_humidityStorage.cend())
		{
			m_humidityStorage[data.stationName] = WeatherIndicatorStorage();
		}
		if (m_pressureStorage.find(data.stationName) == m_pressureStorage.cend())
		{
			m_pressureStorage[data.stationName] = WeatherIndicatorStorage();
		}
		std::cout << "Station name: " << data.stationName << std::endl;
		std::cout << "Temperature: " << std::endl;
		UpdateIndicator(m_temperatureStorage[data.stationName], data.temperature);

		std::cout << "Humidity: " << std::endl;
		UpdateIndicator(m_humidityStorage[data.stationName], data.humidity);

		std::cout << "Pressure: " << std::endl;
		UpdateIndicator(m_pressureStorage[data.stationName], data.pressure);
	}

	void UpdateIndicator(WeatherIndicatorStorage& storage, double indicatorValue)
	{
		storage.UpdateMaxValue(indicatorValue);
		storage.UpdateMinValue(indicatorValue);
		storage.UpdateAverageValue(indicatorValue);
		std::cout << "Max value " << storage.GetMaxValue() << std::endl;
		std::cout << "Min value " << storage.GetMinValue() << std::endl;
		std::cout << "Average value " << storage.GetAvarageValue() << std::endl;
		std::cout << "----------------" << std::endl;
	}

	std::map<std::string, WeatherIndicatorStorage> m_temperatureStorage;
	std::map < std::string, WeatherIndicatorStorage> m_pressureStorage;
	std::map < std::string, WeatherIndicatorStorage> m_humidityStorage;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:

	CWeatherData(std::string name)
		: m_stationName(name)
	{
	}
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

	std::string GetName() const
	{
		return m_stationName;
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
		info.stationName = GetName();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
	std::string m_stationName;
};
