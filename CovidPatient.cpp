

#include "CovidPatient.h"

namespace sdds 
{
   int nextCovidTicket = 1;

   CovidPatient::CovidPatient() : Patient(nextCovidTicket)
   {

	   nextCovidTicket++;
   }

   std::istream& CovidPatient::csvRead(std::istream& istr)
   {

	   Patient::csvRead(istr);
	   int record = number() + 1;
	   nextCovidTicket = record;
	   istr.ignore(1000, '\n');
	   return istr;
   }

   std::ostream& CovidPatient::write(std::ostream& ostr) const
   {
	   if (fileIO())
	   {

		   Patient::csvWrite(ostr);
	   }
	   else
	   {

		   ostr << "COVID TEST\n";
		   Patient::write(ostr);
		   ostr << std::endl;

	   }

	   return ostr;
   }

   std::istream& CovidPatient::read(std::istream& istr)
   {

	   if (fileIO())
	   {

		   csvRead(istr);
	   }
	   else
	   {

		   Patient::read(istr);
	   }

	   return istr;
   }

   char CovidPatient::type() const
   {

	   return 'C';
   }
}