#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "3ds.h"


class Menu
{
    int8_t arrow;
    int8_t num_items;
    int8_t init_line;
    std::vector<std::string> menu_items;
    public:
        Menu(std::vector<std::string> models, int8_t init_line);
        Menu(const char* menu_file, int8_t init_line);

        // user input
        virtual void MenuDOWN();
        virtual void MenuUP();
        virtual void MenuTouch(u16 touch_y);

        // Print Menu
        virtual void printMenuState();
        virtual void printMenuItems();
        virtual std::string getItem();
};

#endif