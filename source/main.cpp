#include "3ds.h" // 3DS Devkit

// #include "datareader.h" // NCNN
#include "net.h"
#include "cpu.h"

#include <iostream> // STD
// #include <stdlib.h>
// #include <vector>
// #include <float.h>
// #include <stdio.h>
// #include <string.h>
// #include <chrono>


#include "utils.h" // Self
#include "menu.h"

#include "bench.h"


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
    // "shufflenet_v2.param"

    ncnn::Option opt;
    opt.lightmode = true;
    opt.num_threads = 1;
    opt.use_winograd_convolution = true;
    opt.use_sgemm_convolution = true;
    opt.use_int8_inference = true;
    opt.use_vulkan_compute = false;
    opt.use_fp16_packed = true;
    opt.use_fp16_storage = true;
    opt.use_fp16_arithmetic = true;
    opt.use_int8_storage = true;
    opt.use_int8_arithmetic = true;
    opt.use_packing_layout = true;
    opt.use_shader_pack8 = false;
    opt.use_image_storage = false;

    // Print Opening message
    std::cout << "\x1b[10;16HCPU count: " << ncnn::get_cpu_count() << std::endl;
    std::cout << "\x1b[11;16HCPU count(BIG): " << ncnn::get_big_cpu_count() << std::endl;
    std::cout << "\x1b[12;16HCPU count(SML): " << ncnn::get_little_cpu_count() << std::endl;
    std::cout << "\x1b[13;16HCPU powersave: " << ncnn::get_cpu_powersave() << std::endl;

    std::cout << "\x1b[16;16HHello, NCNN bench demo!" << std::endl;
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
        // User input
        hidScanInput();
        kDown = hidKeysDown();
        kHeld = hidKeysHeld();
        touchPosition touch;
        hidTouchRead(&touch);

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
        if(touch.py != 0)
        {
            // printf("\x1b[2;0H%03d; %03d; Menu item: %03d", touch.px, touch.py, menu.MenuTouch(touch.py));
            menu.MenuTouch(touch.py);
            menu.printMenuState();
            // consoleSelect(&topScreen);
            // std::cout << menu.getItem() << std::endl;
            // consoleSelect(&bottomScreen);
        }

        if(kDown & KEY_A)
        {
            consoleSelect(&topScreen);
            // ncnn::Mat mat = randn.randn_ncnn(128, 2, 2);
            // mat = mat.reshape(1, 1, 512);
            // pretty_print(mat);

            benchmark("shufflenet_v2.param", ncnn::Mat(64, 64, 3), opt);
            consoleSelect(&bottomScreen);
        }

        // Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}