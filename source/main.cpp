#include "3ds.h"
#include "menu.h"
#include <iostream>
#include <stdlib.h>


int main(int argc, char** argv)
{
  // Initialize services
  gfxInitDefault();

  //In this example we need one PrintConsole for each screen
  PrintConsole topScreen, bottomScreen;

  //Initialize console for both screen using the two different PrintConsole we have defined
  consoleInit(GFX_TOP, &topScreen);
  consoleInit(GFX_BOTTOM, &bottomScreen);

  //Select the top screen
  consoleSelect(&topScreen);
  
  // Print Opening message
  std::cout << "\x1b[26;16HHello, Menu demo!" << std::endl;
  std::cout << "\x1b[27;16HPress START to exit" << std::endl;
  // FILE* menu_ptr = fopen("menu.txt", "r");

  // if (menu_ptr == NULL) std::cout << "Cannot open file." << std::endl;

  // char ch;
  // while ((ch=fgetc(menu_ptr) != EOF)) printf("%c", ch);

  consoleSelect(&bottomScreen);
  Menu menu("menu.txt");
  menu.printMenuItems();
  menu.printMenuState();

  u32 kDown;
	u32 kHeld;
  
  // Main loop
  while(aptMainLoop())
  {
    hidScanInput();
    kDown = hidKeysDown();
		kHeld = hidKeysHeld();

    if(kHeld & KEY_START) break;

    // Update Menu by input
    if(kDown & KEY_UP)
    {
      menu.MenuUP();
      menu.printMenuState();
    }
    if(kDown & KEY_DOWN)
    {
      menu.MenuDOWN();
      menu.printMenuState();
    } 
    if(kDown & KEY_A)
    {
      std::string str = "\x1b["+std::to_string(14)+";20HSelected"; 
      std::cout << str << std::endl;
    }
  }

  // fclose(menu_ptr);
  // Exit services
	gfxExit();

	return 0;
}