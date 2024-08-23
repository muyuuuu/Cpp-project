#include "dump_my_class.h"
#include "dump_serial.h"
#include "dump_deserial.h"
#include <iostream>

int main() {
    {
        OutStream output;
        std::vector<double> vec;
        int a = 13;
        char c = 'c';
        vec.push_back(3.14);
        vec.push_back(9);
        output << a << vec << c;
        output.Save("para.raw");

        int b;
        char d;
        std::vector<double> vec1;

        InStream input;
        input.Read("para.raw");

        input >> b >> vec1 >> d;

        std::cerr << b << std::endl;
        std::cerr << d << std::endl;
        std::cerr << vec1[0] << std::endl;
        std::cerr << vec1[1] << std::endl;
    }

    {
        OutStream output;
        Benchmark ben;
        ben.black_level.resize(10);
        for (int i = 0; i < 10; i++)
        {
            ben.black_level[i] = i + 3;
        }
        ben.name = "snsc";
        ben.noise[0] = 0.123;
        ben.noise[1] = 0.312;
        ben.noise[2] = 8.89;
        ben.noise[3] = 9.36;
        ben.scale = 2;
        ben.white_level = 16383;

        DumpBenchmark dump_bench, dump_bench1;
        dump_bench.bench = ben;

        output << dump_bench;
        output.Save("para.raw");

        InStream input;
        input.Read("para.raw");
        input >> dump_bench1;

        for (int i = 0; i < 10; i++)
        {
            std::cerr << "black_level " << dump_bench1.bench.black_level[i] << "\t";
            std::cerr << "black_level " << ben.black_level[i] << std::endl;
        }

    }

    return 0;
}
