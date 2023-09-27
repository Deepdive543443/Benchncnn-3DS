#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "menu.h"


Menu::Menu(std::string menu_file)
{
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

void Menu::printMenuItems()
{
  std::string output;
  int i = 0;

  for (std::string item : menu_items)
  {
    output = "\x1b[" + std::to_string(i + 4) + ";7H" + item;
    std::cout << output << std::endl;
    i++;
  }
}