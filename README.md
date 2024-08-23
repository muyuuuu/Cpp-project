# 项目中的 load dump 序列化

> 背景：项目中每次对精度需要使用 fwrite 和 fread，比较难用。

于是自己实现了一个序列化和反序列化的接口。**keypoint**：模板特化和 SFINAE 实现类型无感，字节流处理实现序列化和反序列化。

- 支持 POD 类型
- 支持 string
- 支持 vector
- 支持自定义结构体参数

## build

linux 端测试执行：

```
mkdir build
cd build
cmake ..
make
./main
```

## use

如果项目需要，把 include 目录搬走就行。注意：里面的代码不符合 mage 的代码规范。

使用方式可以参考 `main.cpp`。

### POD， string 和 vector

```cpp
OutStream output;
std::vector<double> vec;
int a = 13;
char c = 'c';
vec.push_back(3.14);
vec.push_back(9);
output << a << vec << c;         // benchmark 端，序列化数据并保存
output.Save("para.raw");
```

```cpp
InStream input;
input.Read("para.raw");          // develop 端，读取序列化数据，反序列化到数据中
input >> b >> vec1 >> d;
```

### 自定义类

```cpp
OutStream output;
Benchmark ben;                      // benchmark 端的参数

DumpBenchmark dump_bench;           // DumpBenchmark 是自定义的序列化子类，
dump_bench.bench = ben;             // DumpBenchmark 包含 benchmark 的参数

output << dump_bench;               // 序列化 benchmark 端的参数
output.Save("para.raw");
```

```cpp
InStream input;                     // develop 端代码
DumpBenchmark dump_bench1;          // develop 端全流程测试时，直接反序列化 benchmark 端的参数
input.Read("para.raw");
input >> dump_bench1;               // develop 端一步拿到 benchmark 的参数
```