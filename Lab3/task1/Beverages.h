#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

enum class CoffeeType
{
	STANDARD,
	DOUBLE,
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee", CoffeeType type = CoffeeType::STANDARD)
		:CBeverage(description) 
	{
		m_type = type;
	}

	double GetCost() const override 
	{
		return 60; 
	}

	CoffeeType GetType() const
	{
		return m_type;
	}

private:
	CoffeeType m_type;
};

// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino(CoffeeType type = CoffeeType::STANDARD) 
		:CCoffee("Cappuccino", type) 
	{}

	double GetCost() const override 
	{
		switch (this->GetType())
		{
		case CoffeeType::DOUBLE:
			return 120;
		default:
			return 80;
		}
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeeType type = CoffeeType::STANDARD) 
		:CCoffee("Latte", type) 
	{}

	double GetCost() const override
	{
		switch (this->GetType())
		{
		case CoffeeType::DOUBLE:
			return 130;
		default:
			return 90;
		}
	}
};

// Чай
class CTea : public CBeverage
{
public:
	CTea() 
		:CBeverage("Tea") 
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake() 
		:CBeverage("Milkshake") 
	{}

	double GetCost() const override 
	{ 
		return 80; 
	}
};
