

#ifndef _SDDS_PATIENT_H_
#define _SDDS_PATIENT_H_

#include "utils.h"
#include "Ticket.h"
#include "IOAble.h"
#include <fstream> 

namespace sdds 
{
	class Patient : public IOAble
	{
		char* m_patientName;
		int m_OHIPInsureNum;
		Ticket m_patientTicket;
		bool m_flagIO;
		
	public:
				
		Patient(int ticketNumber = 0, bool IOFlag = false);
		Patient(const Patient&) = delete;		
		~Patient();
		Patient& operator=(const Patient&) = delete;
		int number()const;
		void setArrivalTime();
		void fileIO(bool IOFlag);
		virtual char type() const = 0;		
		operator Time() const;	
		bool fileIO() const;
		bool operator==(const Patient& patientObj)const;
		bool operator==(const char characterCompare)const;
		std::ostream& write(std::ostream&) const;
		std::ostream& csvWrite(std::ostream&) const;
		std::istream& read(std::istream&);
		std::istream& csvRead(std::istream&);
	};
}
#endif 
