

#ifndef _SDDS_IOABLE_H_
#define _SDDS_IOABLE_H_

#include <iostream>
namespace sdds {

	class IOAble{
	public:

		virtual ~IOAble()
		{
		};

		virtual std::istream& read(std::istream&) = 0;
		virtual std::ostream& write(std::ostream&) const = 0;
		virtual std::istream& csvRead(std::istream&) = 0;
		virtual std::ostream& csvWrite(std::ostream&) const = 0 ;
	};
	std::ostream& operator<<(std::ostream& ostr, const IOAble& object1);
	std::istream& operator>>(std::istream& istr, IOAble& object2);
	
	
}

#endif 