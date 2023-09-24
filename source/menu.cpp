#include <stdlib.h>
#include <iostream>
#include "menu.h"


Menu::Menu(int num_items)
{
  arrow = -1;
  this->num_items = num_items;
  std::string str;

  for (int i = 0; i < this->num_items; i++)
  {
    str = "\x1b[" + std::to_string(i + 4) + ";7HItem " + std::to_string(i + 1);
    std::cout << str << std::endl;
  }

  for (int i = 0; i < this->num_items; i++)
  {
    str = "\x1b[" + std::to_string(i + 4) + ";0H  [ ]";
    std::cout << str << std::endl;
  }
}

void Menu::MenuDOWN()
{
  if (arrow < num_items - 1) arrow++;
}

void Menu::MenuUP()
{
  if (arrow > 0) arrow--;
}

void Menu::printMenuState()
{
  for (int i = 0; i < num_items; i++)
  {
    std::string str;

    if (i == arrow)
    {
      str = "\x1b[" + std::to_string(i + 4) + ";0H->[*]";
    }
    else
    {
      str = "\x1b[" + std::to_string(i + 4) + ";0H  [ ]";
    }

    std::cout << str << std::endl;
  }
}