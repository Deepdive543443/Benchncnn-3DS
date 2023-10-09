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
    std::vector<std::string> menu_items;
    public:
        Menu(std::string menu_file);

        // user input
        virtual void MenuDOWN();
        virtual void MenuUP();
        virtual void MenuTouch(u16 touch_y);

        // Print Menu
        virtual void printMenuState();
        virtual void printMenuItems();
        std::string getItem();
};

#endif