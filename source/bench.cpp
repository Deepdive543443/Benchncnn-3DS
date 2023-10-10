#include "bench.h"
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

// Credit: NCNN-Benchncnn
static int g_warmup_loop_count = 8;
static int g_loop_count = 4;
// static bool g_enable_cooling_down = true;

static ncnn::UnlockedPoolAllocator g_blob_pool_allocator;
static ncnn::PoolAllocator g_workspace_pool_allocator;

int DataReaderFromEmpty::scan(const char* format, void* p) const
{
    return 0;
}

size_t DataReaderFromEmpty::read(void* buf, size_t size) const
{
    memset(buf, 0, size);
    return size;
}

double get_current_time()
{
#if (__cplusplus >= 201103L || (defined(_MSVC_LANG) && _MSVC_LANG >= 201103L)) && !defined(__riscv) && !NCNN_SIMPLESTL
    auto now = std::chrono::high_resolution_clock::now();
    auto usec = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
    return usec.count() / 1000.0;
#else
#ifdef _WIN32
    LARGE_INTEGER freq;
    LARGE_INTEGER pc;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&pc);

    return pc.QuadPart * 1000.0 / freq.QuadPart;
#else  // _WIN32
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
#endif // _WIN32
#endif
}

void benchmark(const char* comment, const ncnn::Mat &_in, const ncnn::Option& opt)
{
    g_blob_pool_allocator.clear();
    g_workspace_pool_allocator.clear();

    ncnn::Net net;
    net.opt = opt;

    // Load weight
    net.load_param(comment);
    DataReaderFromEmpty dr;
    net.load_model(dr);

    const std::vector<const char*>& input_names = net.input_names();
    const std::vector<const char*>& output_names = net.output_names();

    ncnn::Mat in = _in;
    in.fill(0.01f);


    printf("\x1b[22;1H");
    printf("\x1b[0J"); // Clear line

    // warm up
    printf("\x1b[22;1HInput shape:[H:%d, W:%d, C:%d]\n", in.h, in.w, in.c);
    printf("\x1b[23;1HWarm up...");
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
        printf("\x1b[23;20H[%2d/%2d]\n",i + 1, g_warmup_loop_count);
    }

    double time_min = DBL_MAX;
    double time_max = -DBL_MAX;
    double time_avg = 0;

    printf("\x1b[24;1HBenchmarking...");

    int out_w;
    int out_h;
    int out_c;

    for (int i = 0; i < g_loop_count; i++)
    {
        double start = get_current_time();
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
                
                //
                out_w = out.w;
                out_h = out.h;
                out_c = out.c;
            }
        }
        double end = get_current_time();
        double time = end - start;

        time_min = std::min(time_min, time);
        time_max = std::max(time_max, time);
        time_avg += time;
        printf("\x1b[24;20H[%2d/%2d] Time:%7.2f\n",i + 1, g_loop_count, time);
    }
    printf("\x1b[25;1HOutput shape:[H:%d, W:%d, C:%d]\n\n", out_h, out_w, out_c);

    time_avg /= g_loop_count;
    fprintf(stderr, "min = %7.2f  max = %7.2f  avg = %7.2f\n", time_min, time_max, time_avg);
}