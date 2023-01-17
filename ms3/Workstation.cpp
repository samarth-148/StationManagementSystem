// Name: Samarth Shaileshkumar Patel
// Seneca Student ID: 143147213
// Seneca email: sspatel74@seneca.ca
// Date of completion: 11/16/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Workstation.h"

using namespace std;
namespace sdds
{
	deque<CustomerOrder> g_pending{};
	deque<CustomerOrder> g_completed{};
	deque<CustomerOrder> g_incomplete{};

	Workstation::Workstation(const string &record) : Station(record) {}

	void Workstation::fill(std::ostream &os)
	{
		if (m_orders.size() > 0)
		{ // !=0
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		if (!m_orders.empty())
		{
			if (m_orders.front().isItemFilled(getItemName()) || !getQuantity())
			{
				if (m_pNextStation)
				{
					*m_pNextStation += (std::move(m_orders.front()));
				}
				else
					m_orders.front().isOrderFilled() ? g_completed.push_back(std::move(m_orders.front())) : g_incomplete.push_back(std::move(m_orders.front()));
				m_orders.pop_front();
				return true;
			}
		}
		return false;
	}

	void Workstation::setNextStation(Workstation *station)
	{
		m_pNextStation = station;
	}

	Workstation *Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream &os) const
	{
		m_pNextStation ? os << getItemName() << " --> " << m_pNextStation->getItemName() << std::endl : os << getItemName() << " --> "
																										   << "End of Line" << std::endl;
	}

	Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}