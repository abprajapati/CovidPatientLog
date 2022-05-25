

#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include "TriagePatient.h"

namespace sdds
{

	int nextTriageTicket = 1;

	char TriagePatient::type() const
	{

		return 'T';
	}
	TriagePatient::TriagePatient() : Patient(nextTriageTicket)
	{

		symptomsTriage = nullptr;
		nextTriageTicket++;
	}

	std::ostream& TriagePatient::write(std::ostream& ostr) const
	{
		if (fileIO())
		{
			csvWrite(ostr);
		}
		else
		{
			ostr << "TRIAGE" << std::endl;
			Patient::write(ostr);
			ostr << std::endl << "Symptoms: " << symptomsTriage << std::endl;

		}

		return ostr;
	}

	std::ostream& TriagePatient::csvWrite(std::ostream& ostr) const
	{

		Patient::csvWrite(ostr);
		ostr << "," << symptomsTriage;
		return ostr;
	}

	TriagePatient::~TriagePatient()
	{

		delete[] symptomsTriage;
		symptomsTriage = nullptr;
	}

	std::istream& TriagePatient::csvRead(std::istream& istr)
	{

		char current[1000];
		delete[] symptomsTriage;
		symptomsTriage = nullptr;
		Patient::csvRead(istr);
		nextTriageTicket = number() + 1;
		istr.ignore(1000, ',');
		istr.getline(current, 1000, '\n');
		symptomsTriage = new char[strlen(current) + 1];
		strcpy(symptomsTriage, current);
		return istr;
	}

	std::istream& TriagePatient::read(std::istream& istr)
	{


		if (fileIO())
		{
			csvRead(istr);
		}
		else
		{
			char currect[1000];
			delete[] symptomsTriage;
			symptomsTriage = nullptr;
			Patient::read(istr);
			std::cout << "Symptoms: ";
			istr.getline(currect, 1000, '\n');
			symptomsTriage = new char[strlen(currect) + 1];
			strcpy(symptomsTriage, currect);

		}
		return istr;
	}

}
   