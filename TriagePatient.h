

#ifndef TRIAGEPATIENT_H
#define TRIAGEPATIENT_H
#include "Patient.h"
namespace sdds {
     class TriagePatient : public Patient
     {
         char *symptomsTriage;
     public:
         virtual char type() const;
         TriagePatient();
         ~TriagePatient();
         std::ostream& write(std::ostream&) const;
         std::ostream& csvWrite(std::ostream&) const;
         std::istream& csvRead(std::istream&);
         std::istream& read(std::istream&);
        
             
      };
}
#endif 