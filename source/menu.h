#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <iostream>


class Menu
{
  int arrow;
  int num_items;
  public:
    Menu(int num_items);

    // Update for menu update
    virtual void MenuDOWN();
    virtual void MenuUP();
    virtual void printMenuState();
};

#endif