

#include "Time.h"
#include "utils.h"
using namespace std;

namespace sdds {

	Time& Time::setToNow()
	{

		this->m_min = getTime();
		return *this;
	}

	Time::Time(unsigned int min)
	{

		m_min = min;
	}


	std::istream& Time::read(std::istream& istr) {
		int noOfHour = 0;
		int noOfMinute = 0;
		char symbolColon;
		int record = 0;

		istr >> noOfHour;
		istr >> symbolColon;
		istr >> noOfMinute;
		if (noOfHour <= 0)
		{
			if (noOfMinute <= 0)
			{
				record = 1;
			}
		}

		if ((record != 1) && !(cin.fail())) {
			if (symbolColon != ':' || cin.fail())
			{
				istr.setstate(ios::failbit);
			}
			else
			{

				if (record == 1 || cin.fail())
				{
					istr.setstate(ios::failbit);
				}
				else
				{
					m_min = (noOfHour * 60) + noOfMinute;
				}
			}
			
		}
		else {

			istr.setstate(ios::failbit);
		}

		return istr;
	}


	std::ostream& Time::write(std::ostream& ostr) const
	{

		int timeInHours;
		timeInHours = m_min / 60;
		ostr.fill('0');
		ostr.width(2);
		ostr << timeInHours << ":";

		int timeInMinutes;
		timeInMinutes = m_min % 60;
		ostr.fill('0');
		ostr.width(2);
		ostr << timeInMinutes;
		return ostr;
	}

	Time Time::operator-(const Time& D)const
	{

		Time duration;
		duration.m_min = this->m_min;
		while (duration.m_min < D.m_min)
		{
			duration.m_min += 1440;
		}

		duration.m_min = duration.m_min - D.m_min;

		return duration;
	}

	Time& Time::operator-=(const Time& D)
	{

		while (this->m_min < D.m_min)
		{
			this->m_min += 1440;
		}

		this->m_min -= D.m_min;

		return *this;
	}


	Time& Time::operator+=(const Time& D)
	{

		this->m_min += D.m_min;
		return *this;
	}

	Time& Time::operator=(unsigned int val)
	{

		this->m_min = val;

		return *this;
	}

	Time& Time::operator *= (unsigned int val)
	{

		this->m_min = this->m_min * val;

		return *this;
	}

	Time& Time::operator /= (unsigned int val)
	{

		this->m_min = this->m_min / val;

		return *this;
	}

	Time Time::operator+(const Time& D)const
	{

		Time duration;

		duration.m_min = this->m_min;
		duration.m_min += D.m_min;
		return duration;
	}


	Time Time::operator /(unsigned int val)const
	{

		Time duration;

		duration.m_min = this->m_min;
		duration.m_min = duration.m_min / val;
		return duration;
	}

	Time Time::operator *(unsigned int val)const
	{

		Time duration;

		duration.m_min = this->m_min * val;
		return duration;
	}

	Time::operator int()const
	{

		return (int)m_min;
	}

	Time::operator unsigned int()const
	{

		return m_min;
	}


	std::istream& operator>>(std::istream& istr, Time& D)
	{

		D.read(istr);

		return istr;
	}

	std::ostream& operator<<(std::ostream& ostr, const Time& D)
	{

		D.write(ostr);

		return ostr;
	}
}

	