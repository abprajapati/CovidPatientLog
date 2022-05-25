

#define _CRT_SECURE_NO_WARNINGS

#include "Patient.h"

#include <iostream>
#include <cstring>

using namespace std;

namespace sdds {
	
	Patient::Patient(int ticketNumber, bool IOFlag) :m_patientTicket(ticketNumber)
	{
		m_OHIPInsureNum = 0;
		m_patientName = nullptr;
		m_flagIO = IOFlag;
	}

	bool Patient::fileIO() const
	{

		return m_flagIO;
	}

	void Patient::fileIO(bool IOFlag)
	{

		m_flagIO = IOFlag;
	}

	char Patient::type() const
	{

		return char(0);
	}

	void Patient::setArrivalTime()
	{

		m_patientTicket.resetTime();
	}

	Patient::~Patient()
	{

		delete[] m_patientName;
		m_patientName = nullptr;
	}

	Patient::operator Time() const
	{

		return Time(m_patientTicket);
	}

	int Patient::number()const
	{

		return m_patientTicket.number();
	}
	
	bool Patient::operator==(const Patient& patientObj)const
	{
		bool record = false;
		if (patientObj.type() == this->type())
		{
			record = true;
		}
		else
		{
			record = false;
		}
		return record;
	}

	bool Patient::operator==(const char characterCompare)const
	{

		bool record = false;

		if (!type())
		{
			record = false;
		}
		else
		{
			record = true;
		}		
		return record;
	}

	std::istream& Patient::csvRead(std::istream& istr)
	{

		char recent[100];

		delete[] m_patientName;
		m_patientName = nullptr;
		istr.get(recent, 100, ',');
		int count = strlen(recent) + 1;
		m_patientName = new char[count];
		strcpy(m_patientName, recent);
		istr.ignore(100, ',');
		istr >> m_OHIPInsureNum;
		istr.ignore(1000, ',');
		m_patientTicket.csvRead(istr);
		return istr;
	}
	
	std::ostream& Patient::csvWrite(std::ostream& ostr)const
	{

		ostr << this->type();
		ostr << ","<< m_patientName << "," << m_OHIPInsureNum << ",";

		m_patientTicket.csvWrite(ostr);
		return ostr;
	}

	std::istream& Patient::read(std::istream& istr)
	{
		char info[100];
		cout << "Name: ";
		delete[] m_patientName;
		m_patientName = nullptr;
		istr.get(info, 100, '\n');
		int count = strlen(info) + 1;
		m_patientName = new char[count];
		strcpy(m_patientName, info);
		istr.ignore(1000, '\n');
		cout << "OHIP: ";
		m_OHIPInsureNum = getInt(100000000, 999999999, nullptr, "Invalid OHIP Number, ", true);
		return istr;
	}
	
	std::ostream& Patient::write(std::ostream& ostr) const 
	{		

		m_patientTicket.write(ostr);
		cout << "\n";

		int i = 0;
		if (strlen(m_patientName) > 25)
		{
			
			for (i = 0; i < 25; i++)
			{
				ostr << m_patientName[i];
			}
			
		}
		else
		{
			ostr << m_patientName;
		}
		ostr << ", OHIP: " << m_OHIPInsureNum;

		return ostr;
	}
	
}