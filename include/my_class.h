#ifndef MY_CLASS_H__
#define MY_CLASS_H__

#include "common.h"
#include "serial.h"
#include "deserial.h"

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
    Benchmark bench;

    std::string Serialize();
    std::size_t DeSerialize(std::string &);
};

#endif // MY_CLASS_H__