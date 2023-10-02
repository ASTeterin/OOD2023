#pragma once

#include <set>
#include <functional>
#include <map>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, int priority) override
	{
		if (m_observers.find(&observer) == m_observers.end())
		{
			m_observersMap.insert({ priority, &observer });
			m_observers.insert(&observer);
			return;
		}

		throw std::runtime_error("Observer already reristred.");
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		for (auto iter = m_observersMap.rbegin(); iter != m_observersMap.rend(); ++iter)
		{
			iter->second->Update(data);
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		for (auto iter = m_observersMap.begin(); iter != m_observersMap.end(); ++iter)
			if (iter->second == &observer)
			{
				m_observersMap.erase(iter->first);
				return;
			}

		m_observers.erase(&observer);
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::set<ObserverType *> m_observers;
	std::multimap<int, ObserverType*> m_observersMap;
};
