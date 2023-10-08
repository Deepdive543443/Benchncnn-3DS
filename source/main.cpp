#include "3ds.h" // 3DS Devkit

#include "datareader.h" // NCNN
#include "net.h"
#include "cpu.h"

#include <iostream> // STD
#include <stdlib.h>
#include <vector>
#include <float.h>
#include <stdio.h>
#include <string.h>
#include <chrono>


#include "utils.h" // Self
#include "menu.h"

static int g_warmup_loop_count = 8;
static int g_loop_count = 4;
// static bool g_enable_cooling_down = true;

static ncnn::UnlockedPoolAllocator g_blob_pool_allocator;
static ncnn::PoolAllocator g_workspace_pool_allocator;

class DataReaderFromEmpty : public ncnn::DataReader
{
public:
    virtual int scan(const char* format, void* p) const
    {
        return 0;
    }
    virtual size_t read(void* buf, size_t size) const
    {
        memset(buf, 0, size);
        return size;
    }
};

void benchmark(const char* comment, const ncnn::Mat &_in, const ncnn::Option& opt, bool fixed_path = true)
{
    g_blob_pool_allocator.clear();
    g_workspace_pool_allocator.clear();

    std::cout << "Initialize model..." << std::endl;
    ncnn::Net net;
    net.opt = opt;

    std::cout << "Loading model..." << std::endl;
    // Load weight
    net.load_param(comment);

    DataReaderFromEmpty dr;
    net.load_model(dr);


    const std::vector<const char*>& input_names = net.input_names();
    const std::vector<const char*>& output_names = net.output_names();

    ncnn::Mat in = _in;
    in.fill(0.01f);
    // _in.fill(0.01f);

    std::cout << "Warm up..." << std::endl;
    // warm up
    for (int i = 0; i < g_warmup_loop_count; i++)
    {
        ncnn::Extractor ex = net.create_extractor();
        for (size_t j = 0; j < input_names.size(); ++j)
        {
            ncnn::Mat in = _in;
            ex.input(input_names[j], in);
        }

        for (size_t j = 0; j < output_names.size(); ++j)
        {
            ncnn::Mat out;
            ex.extract(output_names[j], out);
        }
    }

    std::cout << "Forwarding..." << std::endl;
    double time_min = DBL_MAX;
    double time_max = -DBL_MAX;
    double time_avg = 0;

    for (int i = 0; i < g_loop_count; i++)
    {
        // double start = ncnn::get_current_time();
        {
            ncnn::Extractor ex = net.create_extractor();
            for (size_t j = 0; j < input_names.size(); ++j)
            {
                ncnn::Mat in = _in;
                ex.input(input_names[j], in);
            }

            for (size_t j = 0; j < output_names.size(); ++j)
            {
                ncnn::Mat out;
                ex.extract(output_names[j], out);
            }
        }

        // double end = ncnn::get

        // double time = end - start;

        // time_min = std::min(time_min, time);
        // time_max = std::max(time_max, time);
        // time_avg += time;
    }

    time_avg /= g_loop_count;
    fprintf(stderr, "%20s  min = %7.2f  max = %7.2f  avg = %7.2f\n", comment, 114.514, 1919.810, time_avg);
    // fprintf(stderr, "%20s  min = %7.2f  max = %7.2f  avg = %7.2f\n", comment, time_min, time_max, time_avg);
}

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
            // ncnn::Mat mat = randn.randn_ncnn(128, 2, 2);
            // mat = mat.reshape(1, 1, 512);
            // pretty_print(mat);

            benchmark("shufflenet_v2.param", ncnn::Mat(128, 128, 3), opt);
            consoleSelect(&bottomScreen);
        }
    }

    gfxExit();
    return 0;
}