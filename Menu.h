

#ifndef _MENU_H_
#define _MENU_H_

namespace sdds {

    class Menu {

        char* m_text; 
        int m_noOfSel; 
        void display()const;

    public:

        Menu(const char* MenuContent, int NoOfSelections);
        virtual ~Menu();
        int& operator>>(int& Selection);

        operator bool() const;
        Menu(const Menu& objectOfMenu);
        Menu& operator=(const Menu&);
    };
}

#endif 