#include "menu.hpp"
#include <iostream>
#include <cassert>
#include <conio.h>

int getMenuNumber()
{
    const auto key_code = _getch();
    const int key = (key_code)-48;

    return (key < 0 || 9 < key) ? 666 : key;
}


Menu::Menu(int _start_condition, const string& _condition_name /* = "" */)
: m_condition(_start_condition)
, m_root_condition_name(_condition_name)
{}

void Menu::run()
{
    initialize();

    m_is_working = true;
    while (m_is_working)
    {
        system("cls");
        welcomeTitle(m_root_condition_name);

        auto callback = m_functions_condition.find(m_condition);
        if (callback != m_functions_condition.end())
            callback->second();
    }
}

void Menu::welcomeTitle(const string& _condition_name)
{
    std::cout << _condition_name.c_str() << std::endl;
    std::cout << "_______________________________________________________________" << std::endl << std::endl;
}

void Menu::changeState(int _key, std::initializer_list<int> _list)
{
    for (auto elem:_list)
        if (elem == _key)
        {
            m_condition = _key;
            return;
        }
}

void Menu::writeMenuItem(int _state, const string& _desc)
{
    std::cout << _state << "." << _desc << std::endl;
}

void Menu::chooseCondition(std::initializer_list< std::pair< int, const string&> > _list)
{
    int count = 0;
    for (auto elem:_list)
        std::cout << ++count << "." << elem.second << std::endl;

    const auto pos = getMenuNumber();

    count = 0;
    for (auto elem : _list)
    {
        count++;
        if (pos == count)
        {
            m_condition = elem.first;
            return;
        }
    }
}

void Menu::exitMenu()
{
    m_is_working = false;
}

void Menu::setCondition(int _condition)
{
    m_condition = _condition;
}
