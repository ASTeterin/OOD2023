﻿#pragma once
#include <iostream>
#include <string>

namespace naive
{
const int MAX_QUARTERS = 5;
class CGumballMachine
{
public:
	enum class State
	{
		SoldOut,		// Жвачка закончилась
		NoQuarter,		// Нет монетки
		HasQuarter,		// Есть монетка
		Sold,			// Монетка выдана
	};

	CGumballMachine(unsigned count)
		: m_count(count)
		, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
	{
	}

	void InsertQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			cout << "You inserted a quarter\n";
			m_state = State::HasQuarter;
			break;
		case State::HasQuarter:
			if (m_quartersAmount == MAX_QUARTERS)
			{
				cout << "You can't insert another quarter\n";
				break;
			}
			cout << "You inserted a quarter\n";
			m_quartersAmount++;
			break;
		case State::Sold:
			cout << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}

	void EjectQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::HasQuarter:
			cout << "Quarter returned\n";
			m_quartersAmount = 0;
			m_state = State::NoQuarter;
			break;
		case State::NoQuarter:
			cout << "You haven't inserted a quarter\n";
			break;
		case State::Sold:
			cout << "Sorry you already turned the crank\n";
			break;
		case State::SoldOut:
			if (m_quartersAmount != 0)
			{
				cout << "Returning quarter";
				m_quartersAmount--;
			}
			else
				cout << "You can't eject, you haven't inserted a quarter yet\n";
			break;
		}
	}

	void TurnCrank()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			cout << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
			cout << "You turned...\n";
			m_quartersAmount--;
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			cout << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}

	std::string ToString() const
	{
		std::string state = (m_state == State::SoldOut) ? "sold out" : (m_state == State::NoQuarter) ? "waiting for quarter"
			: (m_state == State::HasQuarter)														 ? "waiting for turn of crank"
																									 : "delivering a gumball";
		return "Mighty Gumball, Inc.\n"
			   "C++-enabled Standing Gumball Model #2016\n"
			   "Inventory: "
			+ std::to_string(m_count) + " gumball" + (m_count != 1 ? "s" : "") + "\n"
			"Bank: "
			+ std::to_string(m_quartersAmount) + " quarter" + (m_quartersAmount != 1 ? "s" : "") + "\n"
			"Machine is "
			+ state + "\n";
	}

private:
	void Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::Sold:
			cout << "A gumball comes rolling out the slot\n";
			--m_count;
			if (m_count == 0)
			{
				cout << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else if (m_quartersAmount == 0)
				m_state = State::NoQuarter;
			else
			{
				m_state = State::NoQuarter;
			}
			break;
		case State::NoQuarter:
			cout << "You need to pay first\n";
			break;
		case State::SoldOut:
		case State::HasQuarter:
			cout << "No gumball dispensed\n";
			break;
		}
	}

	unsigned m_count;
	unsigned m_quartersAmount = 0;
	State m_state = State::SoldOut;
};
}