

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "IOAble.h"

using namespace std;

namespace sdds {

	std::istream& IOAble::read(std::istream& istr)
	{
		return istr;
	}

	std::ostream& IOAble::write(std::ostream& ostr)const
	{
		return ostr;
	}
	
	std::istream& IOAble::csvRead(std::istream& istr)
	{
		return istr;
	}

	std::ostream& IOAble::csvWrite(std::ostream& ostr)const 
	{
		return ostr;
	}
   
	std::ostream& operator<<(std::ostream& ostr, const IOAble& object1)
	{
		object1.write(ostr);

		return ostr;
	}

	std::istream& operator>>(std::istream& istr, IOAble& object2)
	{
		object2.read(istr);

		return istr;
	}
		
}