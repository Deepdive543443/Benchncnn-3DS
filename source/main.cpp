#include "3ds.h"
#include "net.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>


#include "utils.h"
#include "menu.h"

int main(int argc, char** argv)
{
    // Load ncnn model

    // Initialize services
    gfxInitDefault();

    //In this example we need one PrintConsole for each screen
    PrintConsole topScreen, bottomScreen;

    //Initialize console for both screen using the two different PrintConsole we have defined
    consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &bottomScreen);

    // Initialize top screen
    consoleSelect(&topScreen);


    std::cout << "\x1b[26;16HLoading ProGAN" << std::endl;
    ncnn::Net progan;
    progan.load_param("script_pro.ncnn.param");
    progan.load_model("script_pro.ncnn.bin");

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
            ncnn::Mat mat = randn.randn_ncnn(128, 2, 2);
            mat = mat.reshape(1, 1, 512);
            pretty_print(mat);
            consoleSelect(&bottomScreen);
        }
    }

    gfxExit();
    return 0;
}