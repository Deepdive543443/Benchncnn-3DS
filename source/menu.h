#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <iostream>
#include <vector>


class Menu
{
  int8_t arrow;
  int8_t num_items;
  std::vector<std::string> menu_items;
  public:
    Menu(std::string menu_file);

    // Update for menu update
    virtual void MenuDOWN();
    virtual void MenuUP();
    virtual void printMenuState();
    virtual void printMenuItems();
};

#endif