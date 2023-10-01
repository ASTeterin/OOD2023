#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

using Strategy = function<void()>;

class Duck
{
public:
	Duck(Strategy&& flyBehavior,
		Strategy&& quackBehavior,
		Strategy&& danceBehavior) : m_quackBehavior(quackBehavior)
		, m_danceBehavior(danceBehavior)
	{
		assert(quackBehavior);
		assert(danceBehavior);
		SetFlyBehavior(flyBehavior);
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Fly() const
	{
		m_flyBehavior();
	}
	void Dance() const
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(Strategy& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = flyBehavior;
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	Strategy m_flyBehavior;
	Strategy m_quackBehavior;
	Strategy m_danceBehavior;
};

Strategy FlyWithWings()
{
	int numberOfFlight = 0;
	return [numberOfFlight]() mutable {
		std::cout << "Number of fligth: " << ++numberOfFlight << std::endl;
	};
}

void FlyNoWay() 
{}

void QuackBehavior()
{
	cout << "Quack Quack!" << endl;
};

void SqueekBehavior()
{
	cout << "Squeek!" << endl;
};

void MuteQuackBehavior()
{};

void DanceWaltz()
{
	cout << "I'm dancing waltz!" << endl;
};

void DanceMinuet()
{
	cout << "I'm dancing minuet!" << endl;
};

void CanNotDance()
{
	std::cout << "I can not dance!" << std::endl;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings(), QuackBehavior, DanceWaltz)
	{}

	void Display() const override
	{
		cout << "I'm mallard duck!" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWings(), QuackBehavior, DanceMinuet)
	{}

	void Display() const override
	{
		cout << "I'm redhead duck!" << endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWay, SqueekBehavior, CanNotDance)
	{}

	void Display() const override
	{
		cout << "I'm rubber duck!" << endl;
	}
};

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(FlyNoWay, MuteQuackBehavior, CanNotDance)
	{}

	void Display() const override
	{
		cout << "I'm rubber duck!" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);
	
	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);
}
