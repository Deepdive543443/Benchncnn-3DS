#include "3ds.h"
#include "net.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>



#include "utils.h"
#include "menu.h"

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

    consoleSelect(&bottomScreen);
    Menu menu("menu.txt");
    menu.printMenuItems();
    menu.printMenuState();

    Randn randn;

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
            consoleSelect(&topScreen);
            ncnn::Mat mat = randn.randn_ncnn(2, 2, 3);
            mat.reshape(3, 2, 2);  // <- Error
            // printf("Matric shape [C, H, W]: [%d, %d, %d]\n", mat.c, mat.h, mat.w);
            pretty_print(mat);
            consoleSelect(&bottomScreen);
        }
    }

    gfxExit();
    return 0;
}