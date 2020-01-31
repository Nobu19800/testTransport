#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string.h>
#include <thread>
#include <random>
#include "test_func.h"




int main()
{
    std::random_device rnd;

    std::ofstream file("cameratestin.txt");
    std::vector<double> data;

    static const int maxsize = 10000001;
    const int datacount = 50;

    int datasize = 100;
    int count = 0;
    bool Flag = true;

    unsigned char* data1 = new unsigned char[datasize];
    unsigned char* data2 = new unsigned char[datasize];

    while (Flag)
    {
        if (datasize > maxsize)
        {
            std::cout << "finish" << std::endl;
            Flag = false;
            return 0;
        }

        
        
        
#if 1
        int loop = datasize > 100 ? 100 : datasize;
        for(int i=0;i < datasize;i++)
        {
            data1[i] = 0;
            data2[i] = 0;
        }
        for(int i=0;i < loop;i++)
        {
            data2[i] = rnd();
        }
#else
    
        for(int i=0;i < datasize;i++)
        {
            data1[i] = 0;
            data2[i] = rnd();
        }
        
#endif



        double diff = testfunc(data1, data2, datasize);

        data.push_back(diff);
        



        static double logmul[] = { 2.0, 2.5, 2.0 };
        ++count;

        if (count%datacount == 0)
        {
            double avg = 0;
            for (const auto &d : data)
            {
                avg += d;
            }

            avg /= data.size();
            std::cout << datasize << "\t" << avg << "\t" << data.size() << std::endl;
            file << datasize << "\t" << avg << "\t" << data.size() << std::endl;
            data.clear();
            datasize = static_cast<int>(static_cast<double>(datasize)*logmul[(count / datacount) % 3]);

            delete[] data1;
            delete[] data2;

            data1 = new unsigned char[datasize];
            data2 = new unsigned char[datasize];
        }


    }

    delete[] data1;
    delete[] data2;
    return 0;
}


