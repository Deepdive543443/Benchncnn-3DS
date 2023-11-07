#ifndef BENCH_H
#define BENCH_H

#include "datareader.h" // NCNN
#include "net.h"

class DataReaderFromEmpty : public ncnn::DataReader
{
public:
    virtual int scan(const char* format, void* p) const;
    virtual size_t read(void* buf, size_t size) const;
};

double get_current_time();
void benchmark(const char* comment, const ncnn::Mat &_in, const ncnn::Option& opt);

#endif