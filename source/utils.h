#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <vector>


void pretty_print(const ncnn::Mat& m);
std::vector<std::string> scan_models(const char* path);

class Randn{

    std::default_random_engine generator;
    std::normal_distribution<float> distribution;

    public:
        Randn();
        virtual ncnn::Mat randn_ncnn(int h, int w, int c);
};
#endif // utils.h