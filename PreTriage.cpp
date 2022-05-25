

#define _CRT_SECURE_NO_WARNINGS
#include "PreTriage.h"
#include<iostream>
#include <fstream>
#include <cstring>
using namespace std;
namespace sdds {
	PreTriage::PreTriage(const char* dataFilename) :  m_averCovidWait(15),
		m_averTriageWait(5),
		m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2),
		m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2)
	{
		int record = strlen(dataFilename) + 1;
		m_dataFilename = new char[record];
		strcpy(m_dataFilename, dataFilename);
		load();
	}

	PreTriage::~PreTriage() {
		ofstream info;
		info.open(m_dataFilename);
		if (info.is_open())
		{
			m_averCovidWait.write(info);
			info << ",";
			m_averTriageWait.write(info);
			info << endl;
			cout << "Saving Average Wait Times,";
			cout << endl;
			cout << "   COVID Test: ";
			m_averCovidWait.write(cout);
			cout << endl;
			cout << "   Triage: ";
			m_averTriageWait.write(cout);
			cout << endl;
			cout << "Saving m_lineup...";
			cout << endl;
			
			int i = 0;
			while (i < m_lineupSize) {
				cout << i + 1 << "- ";
				m_lineup[i]->csvWrite(info);
				m_lineup[i]->csvWrite(cout);
				info << endl;
				cout << endl;
				i++;
			}
		}
		info.close();

		
		int i = 0;
		while (i < m_lineupSize) {
			delete m_lineup[i];
			m_lineup[i] = nullptr;
			i++;
		}
		delete[] m_dataFilename;
		m_dataFilename = nullptr;
		cout << "done!" << endl;
	}

	const Time PreTriage::getWaitTime(const Patient& p)const {
		unsigned int record = 0;
		Time object;
		
		int i = 0;
		while (i < m_lineupSize) {
			if (this->m_lineup[i]->type() != p.type())
			{
				;
			}
			else {
				record++;
			}
			i++;
		}

		if (p.type() == 'T')
			object = m_averTriageWait * (record);
		else if (p.type() == 'C')
			object = m_averCovidWait * (record);

		return object;
	}

	void PreTriage::setAverageWaitTime(const Patient& p) {
		Time CT = getTime();
		Time PTT = Time(p);
		Time* AWT;
		unsigned int PTN = p.number();
		if (p.type() == 'C')
		{
			AWT = &m_averCovidWait;
		}
		else
		{
			AWT = &m_averTriageWait;
		}

		*AWT = ((CT - PTT) + (AWT->operator*(PTN - 1))) / PTN;

	}

	void PreTriage::removePatientFromLineup(int index) {
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}

	int PreTriage::indexOfFirstInLine(char type) const {
		
		int i = 0;
		while (i < m_lineupSize)
		{
			if (type == this->m_lineup[i]->type())
			{
				return i;
			}
			i++;
		}

		return -1;
	}



	void PreTriage::load() {
		cout << "Loading data..." << endl;
		ifstream info;
		info.open(m_dataFilename);
		if (info.is_open())
		{
			m_averCovidWait.read(info);
			info.ignore(1000, ',');
			m_averTriageWait.read(info);
			info.ignore(1000, '\n');
			Patient* obj = 0;
			char fcharacter;
			int count = 0;
			
			int i = 0;
			int keep = 1;
			while ((i < maxNoOfPatients) && keep)
			{
				fcharacter = 0;
				count = 0;
				info >> fcharacter;
				info.ignore(1000, ',');
				if (cin.fail())
				{
					count = 1;
				}
				else
				{
					if (fcharacter == 'T')
					{
						obj = new TriagePatient;
					}
					else if (fcharacter == 'C') {
						obj = new CovidPatient;
					}
					else
					{
						count = 1;
					}
				}
				if (count != 0)
				{
					keep = 0;
				}
				else
				{
					obj->fileIO();
					obj->csvRead(info);
					obj->fileIO(false);
					m_lineup[i] = obj;
					m_lineupSize++;
				}
				i++;
			}
		}
		if (!info.eof())
		{
			cout << "Warning: number of records exceeded 100";
			cout << endl;
		}
		if (m_lineupSize == 0)
		{
			cout << "No data or bad data file!";
			cout << endl;
			cout << endl;
		}
		else
		{
			cout << m_lineupSize << " Records imported...";
			cout << endl;
			cout << endl;
		}


		info.close();
	}

	void PreTriage::reg() {
		if (m_lineupSize == maxNoOfPatients)
		{
			cout << "Line up full!";
			cout << endl;
		}
		else
		{
			int option, keep = 0;
			m_pMenu >> option;

			if (option == 1)
			{
				m_lineup[m_lineupSize] = new CovidPatient;
			}
			else if (option == 2)
			{
				m_lineup[m_lineupSize] = new TriagePatient;
			}
			else
			{
				keep = 1;
			}

			if (keep == 1)
			{
				;
			}
			else
			{
				m_lineup[m_lineupSize]->setArrivalTime();
				cout << "Please enter patient information: ";
				cout << endl;
				m_lineup[m_lineupSize]->fileIO(false);
				m_lineup[m_lineupSize]->read(cin);
				cout << endl;
				cout << "******************************************";
				cout << endl;
				m_lineup[m_lineupSize]->write(cout);
				cout << "Estimated Wait Time: ";
				cout << getWaitTime(*m_lineup[m_lineupSize]);
				cout << endl;
				cout << "******************************************";
				cout << endl;
				cout << endl;
				m_lineupSize++;
			}
		}
	}

	void PreTriage::admit() {

		int option;
		int keep = 0;
		m_pMenu >> option;
		int indexNumber = 0;


		if (option == 1)
		{
			indexNumber = indexOfFirstInLine('C');
		}
		else if (option == 2)
		{
			indexNumber = indexOfFirstInLine('T');
		}
		else
		{
			keep = 1;
		}

		if (keep != 1)
		{
			char type = m_lineup[indexNumber]->type();
			int index = indexOfFirstInLine(type);

			if (index != -1)
			{
				cout << endl;
				cout << "******************************************" << endl;
				m_lineup[index]->fileIO(false);
				cout << "Calling for ";
				m_lineup[index]->write(cout);
				cout << "******************************************" << endl << endl;
				setAverageWaitTime(*m_lineup[index]);
				removePatientFromLineup(index);
			}
			else
			{
				;
			}
		}
		else
		{
			;
		}
	}

	void PreTriage::run(void) {
		int option;

		do {
			m_appMenu >> option;

			if (option == 1)
			{
				reg();
			}
			else if (option == 2)
			{
				admit();
			}
		} while (option != 0);
	}
}