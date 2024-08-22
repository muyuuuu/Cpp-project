#include "my_class.h"

std::string DumpBenchmark::Serialize()
{
    OutStream os;
    os << bench.name << bench.white_level << bench.scale
       << bench.noise[0] << bench.noise[1] << bench.noise[2] << bench.noise[3]
       << bench.black_level;
    return os.Str();
}

std::size_t DumpBenchmark::DeSerialize(std::string &str)
{
    InStream os{str};
    os >> bench.name >> bench.white_level >> bench.scale
       >> bench.noise[0] >> bench.noise[1] >> bench.noise[2] >> bench.noise[3]
       >> bench.black_level;
    return os.size();
}