#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string.h>

int main()
{
    std::ofstream file("cameratestin.txt");
    std::vector<double> data;

    static const int maxsize = 1200001;
    const int datacount = 50;

    int datasize = 100;
    int count = 0;
    bool Flag = true;

    while (Flag)
    {
        if (datasize > maxsize)
        {
            std::cout << "finish" << std::endl;
            Flag = false;
            return 0;
        }

        unsigned char* data1 = new unsigned char[datasize];
        unsigned char* data2 = new unsigned char[datasize];

        auto start = std::chrono::system_clock::now().time_since_epoch();

        memcpy(data1, data2, datasize);

        auto end = std::chrono::system_clock::now().time_since_epoch();
        double diff = std::chrono::duration<double>(end - start).count();

        data.push_back(diff);

        delete data1;
        delete data2;

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
        }
    }
    return 0;
}


