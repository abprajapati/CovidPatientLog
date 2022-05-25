

#ifndef COVIDPATIENT_H_
#define COVIDPATIENT_H_
#include "Patient.h"
namespace sdds {
	class CovidPatient : public Patient 
	{
	public:	
		CovidPatient();
		virtual char type() const;
		std::ostream& write(std::ostream&) const;
		std::istream& read(std::istream&);
		std::istream& csvRead(std::istream&);		
	};
}
#endif 