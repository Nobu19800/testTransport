#include "test_func.h"
#include <chrono>
#include <cstring>

double testfunc(unsigned char* data1, unsigned char* data2, int datasize)
{
        auto start = std::chrono::system_clock::now();

        std::memcpy(data1, data2, datasize);

        auto end = std::chrono::system_clock::now();
        double diff = std::chrono::duration<double>(end - start).count();
        return diff;
}
