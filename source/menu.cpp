#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include "dirent.h"

#include "menu.h"

Menu::Menu(std::vector<std::string> models, int8_t init_line)
{
    this->init_line = init_line;
    menu_items = models;

    arrow = -1;
    num_items = (int8_t) menu_items.size();
}

Menu::Menu(const char* menu_file, int8_t init_line)
{
    this->init_line = init_line;

    std::fstream file;
    // Load menu
    file.open(menu_file, std::ios::in);
    if (file.is_open())
    {
        std::string str;
        while (std::getline(file, str))
        {
            menu_items.push_back(str);
        }
    }
    else
    {
        std::cout << "Didn't find the files." << std::endl;
    }
    file.close();
    arrow = -1;
    num_items = (int8_t) menu_items.size();
}

// User input
void Menu::MenuDOWN()
{
    if (arrow < num_items - 1) arrow++;
}

void Menu::MenuUP()
{
    if (arrow > 0) arrow--;
}

void Menu::MenuTouch(u16 touch_y)
{
    // Menu start from line 4
    int8_t line = (int8_t) floor((touch_y / 8.0f) + 1) - 4;
    if (line <= num_items -1 && line >= 0)
    {
        arrow = line;
    }
}

// Update menu
void Menu::printMenuState()
{
    for (int8_t i = 0; i < num_items; i++)
    {
        std::string str;
        if (i == arrow)
        {
            str = "\x1b[" + std::to_string(i + init_line) + ";0H->[*]";
        }
        else
        {
            str = "\x1b[" + std::to_string(i + init_line) + ";0H  [ ]";
        }
        std::cout << str << std::endl;
    }
}

void Menu::printMenuItems()
{
    std::string output;
    int i = 0;

    for (std::string item : menu_items)
    {
        output = "\x1b[" + std::to_string(i + init_line) + ";7H" + item;
        std::cout << output << std::endl;
        i++;
    }
}

std::string Menu::getItem()
{
    return menu_items[arrow];
}