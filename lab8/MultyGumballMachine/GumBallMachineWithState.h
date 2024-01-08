#pragma once
#include <iostream>
#include <sstream>
#include <string>

namespace with_state
{
const int MAX_QUARTERS = 5;
struct IState
{
	virtual void InsertQuarter() = 0;
	virtual void EjectQuarter() = 0;
	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;
	virtual std::string ToString() const = 0;
	virtual ~IState() = default;
};

struct IGumballMachine
{
	virtual void ReleaseBall() = 0;
	virtual unsigned GetBallCount() const = 0;
	virtual unsigned GetQuartersAmount() const = 0;
	virtual void IncreaseQuartersAmount() = 0;
	virtual void DecreaseQuartersAmount() = 0;
	virtual void EmptyBank() = 0;

	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual ~IGumballMachine() = default;
};

class CSoldState : public IState
{
public:
	CSoldState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}
	void InsertQuarter() override
	{
		std::cout << "Please wait, we're already giving you a gumball\n";
	}
	void EjectQuarter() override
	{
		std::cout << "Sorry you already turned the crank\n";
	}
	void TurnCrank() override
	{
		std::cout << "Turning twice doesn't get you another gumball\n";
	}
	void Dispense() override
	{
		m_gumballMachine.ReleaseBall();
		if (m_gumballMachine.GetBallCount() == 0)
		{
			std::cout << "Oops, out of gumballs\n";
			m_gumballMachine.SetSoldOutState();
		}
		else if (m_gumballMachine.GetQuartersAmount() != 0)
			m_gumballMachine.SetHasQuarterState();
		else
			m_gumballMachine.SetNoQuarterState();
	}
	std::string ToString() const override
	{
		return "delivering a gumball";
	}

private:
	IGumballMachine& m_gumballMachine;
};

class CSoldOutState : public IState
{
public:
	CSoldOutState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You can't insert a quarter, the machine is sold out\n";
	}
	void EjectQuarter() override
	{
		if (m_gumballMachine.GetQuartersAmount() != 0)
		{
			std::cout << "Returning quarter";
			m_gumballMachine.EmptyBank();
		}
		else
			std::cout << "You can't eject, you haven't inserted a quarter yet\n";
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no gumballs\n";
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "sold out";
	}

private:
	IGumballMachine& m_gumballMachine;
};

class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		if (m_gumballMachine.GetQuartersAmount() == MAX_QUARTERS)
		{
			std::cout << "You can't insert another quarter\n";
			return;
		}
		std::cout << "You inserted a quarter\n";
		m_gumballMachine.IncreaseQuartersAmount();
	}
	void EjectQuarter() override
	{
		std::cout << "Quarter returned\n";
		m_gumballMachine.EmptyBank();
		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank() override
	{
		std::cout << "You turned...\n";
		m_gumballMachine.DecreaseQuartersAmount();
		m_gumballMachine.SetSoldState();
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "waiting for turn of crank";
	}

private:
	IGumballMachine& m_gumballMachine;
};

class CNoQuarterState : public IState
{
public:
	CNoQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You inserted a quarter\n";
		m_gumballMachine.IncreaseQuartersAmount();
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarter() override
	{
		std::cout << "You haven't inserted a quarter\n";
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no quarter\n";
	}
	void Dispense() override
	{
		std::cout << "You need to pay first\n";
	}
	std::string ToString() const override
	{
		return "waiting for quarter";
	}

private:
	IGumballMachine& m_gumballMachine;
};

class CGumballMachine : private IGumballMachine
{
public:
	CGumballMachine(unsigned numBalls)
		: m_soldState(*this)
		, m_soldOutState(*this)
		, m_noQuarterState(*this)
		, m_hasQuarterState(*this)
		, m_state(&m_soldOutState)
		, m_count(numBalls)
	{
		if (m_count > 0)
		{
			m_state = &m_noQuarterState;
		}
	}
	void EjectQuarter()
	{
		m_state->EjectQuarter();
	}
	void InsertQuarter()
	{
		m_state->InsertQuarter();
	}
	void TurnCrank()
	{
		m_state->TurnCrank();
		m_state->Dispense();
	}
	std::string ToString() const
	{
		return "Mighty Gumball, Inc.\n"
			   "C++-enabled Standing Gumball Model #2016 (with state)\n"
			   "Inventory: "
			+ std::to_string(m_count) + " gumball" + (m_count != 1 ? "s" : "") + "\n"
			"Bank: "
			+ std::to_string(m_quartersAmount) + " quarter" + (m_quartersAmount != 1 ? "s" : "") + "\n"
			"Machine is "
			+ m_state->ToString() + "\n";
	}

private:
	unsigned GetBallCount() const override
	{
		return m_count;
	}

	unsigned GetQuartersAmount() const override
	{
		return m_quartersAmount;
	}

	void IncreaseQuartersAmount() override
	{
		m_quartersAmount++;
	}

	void DecreaseQuartersAmount() override
	{
		m_quartersAmount--;
	}

	void EmptyBank() override
	{
		m_quartersAmount = 0;
	}

	void ReleaseBall() override
	{
		if (m_count != 0)
		{
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_count;
		}
	}
	void SetSoldOutState() override
	{
		m_state = &m_soldOutState;
	}
	void SetNoQuarterState() override
	{
		m_state = &m_noQuarterState;
	}
	void SetSoldState() override
	{
		m_state = &m_soldState;
	}
	void SetHasQuarterState() override
	{
		m_state = &m_hasQuarterState;
	}

private:
	unsigned m_count = 0;
	unsigned m_quartersAmount = 0;
	CSoldState m_soldState;
	CSoldOutState m_soldOutState;
	CNoQuarterState m_noQuarterState;
	CHasQuarterState m_hasQuarterState;
	IState* m_state;
};
} // namespace with_state