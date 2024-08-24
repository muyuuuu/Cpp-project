#ifndef DUMP_MY_CLASS_H__
#define DUMP_MY_CLASS_H__

#include "dump_common.h"
#include "dump_serial.h"
#include "dump_deserial.h"

struct Benchmark
{
    std::string name;
    int white_level;
    float scale;
    double noise[4];
    std::vector<int> black_level;
};

struct DumpBenchmark : public Serializable
{
    Benchmark bench;         // 把 benchmark 中的参数放到这里作为成员

    std::string Serialize()
    {
        OutStream os;
        os << bench.name << bench.white_level << bench.scale
        << bench.noise[0] << bench.noise[1] << bench.noise[2] << bench.noise[3]
        << bench.black_level;
        return os.Str();
    }

    std::size_t DeSerialize(std::string &str)
    {
        InStream os{str};
        os >> bench.name >> bench.white_level >> bench.scale
        >> bench.noise[0] >> bench.noise[1] >> bench.noise[2] >> bench.noise[3]
        >> bench.black_level;
        return os.size();
    }

    void PrintParam()
    {
        std::cerr << " white_level = " << bench.white_level << std::endl;
    }
};

#endif // DUMP_MY_CLASS_H__