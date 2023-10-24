#pragma once

#include "IBeverage.h"
#include <stdexcept>

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

enum class TeaType
{
	BLACK_TEA,
	GREEN_TEA,
	ULUN,
	PUER_TEA,
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(TeaType type = TeaType::BLACK_TEA) 
		: CBeverage(GetTeaDescription(type)) 
	{}

	double GetCost() const override 
	{
		return 30; 
	}
	std::string GetTeaDescription(TeaType type) const
	{
		std::string description;
		switch (type)
		{
		case TeaType::BLACK_TEA:
			description = "Black tea";
		case TeaType::GREEN_TEA:
			description = "Green tea";
		case TeaType::ULUN:
			description = "Ulun";
		case TeaType::PUER_TEA:
			description = "Puer";
		default:
			throw std::invalid_argument("Invalid tee type.");
		}
	}
};


enum class MilkshakeType
{
	SMALL,
	STANDARD,
	BIG,
};
// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakeType type = MilkshakeType::STANDARD)
		: CBeverage(GetMilkshakeDescription())
		, m_type(type)
	{
	}

	double GetCost() const override
	{
		switch (m_type)
		{
		case MilkshakeType::SMALL:
			return 50;
		case MilkshakeType::STANDARD:
			return 60;
		case MilkshakeType::BIG:
			return 80;
		default:
			throw std::invalid_argument("Invalid milshake size.");
		}
	}

	std::string GetMilkshakeDescription() const
	{
		std::string description;
		switch (m_type)
		{
		case MilkshakeType::SMALL:
			description = "Small milkshake";
		case MilkshakeType::STANDARD:
			description = "Medium milkshake";
		case MilkshakeType::BIG:
			description = "Big milkshake";
		default:
			throw std::invalid_argument("Invalid milshake size.");
		}
	}

private:
	MilkshakeType m_type;
};
