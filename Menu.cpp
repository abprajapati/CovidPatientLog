


#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

#include "utils.h"
#include "Menu.h"

using namespace std;

namespace sdds {

	Menu::Menu(const char* MenuContent, int NoOfSelections) 
	{
		int record = strlen(MenuContent) + 1;

		m_text = new char[record];
		m_noOfSel = NoOfSelections;
		strcpy(m_text, MenuContent);
		
	}

	Menu::~Menu() 
	{
		delete[] m_text;
		m_text = nullptr;
	}	

	int& Menu::operator>>(int& Selection)
	{
		display();
		int userSelection = getInt(0, m_noOfSel, "> ", "Invalid option ", true);
		Selection = userSelection;

		return Selection;
	}

	Menu& Menu::operator=(const Menu& objectOfMenu) 
	{
		int keep = objectOfMenu.m_noOfSel != 0 && objectOfMenu.m_text != nullptr && *this;

		if (keep)
		{

			int record = strlen(objectOfMenu.m_text) + 1;

			delete[] m_text;
			m_text = nullptr;
			m_text = new char[ record];
			m_noOfSel = objectOfMenu.m_noOfSel;
			strcpy(m_text, objectOfMenu.m_text);
			
		}

		return *this;
	}

	Menu::Menu(const Menu& objectOfMenu)
	{
		m_noOfSel = 0;
		m_text = nullptr;

		int keep = objectOfMenu.m_noOfSel != 0 && objectOfMenu.m_text != nullptr;
		if (keep)
		{

			int record = strlen(objectOfMenu.m_text) + 1;
			m_text = new char[record];
			m_noOfSel = objectOfMenu.m_noOfSel;
			strcpy(m_text, objectOfMenu.m_text);
		}
	}

	void Menu::display()const
	{
		cout << m_text;
		cout << endl;
		cout << "0- Exit";
		cout << endl;
	}

	Menu::operator bool() const 
	{
		bool record = m_text != nullptr && m_noOfSel != 0;
		return record;
	}
	
	
}