#ifndef UTILS_H
#define UTILS_H

void pretty_print(const ncnn::Mat& m);

ncnn::Mat randn_ncnn(int h, int w, int c);

#endif // utils.h