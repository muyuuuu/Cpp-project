> 收录一下写过的 Cpp 代码

# Serializate 库

> 背景：不同设备之间传输数据时，如果结构体成员内只有数组或者 `POD` 类型，可以使用 `fwrite` 和 `fread`。当存在 `string` 或者 `vector` 类型时，手动 `fwrite` 和 `fread` 就会导致代码冗余。

![](Serializate/imgs/model.png)

于是自己实现了一个序列化和反序列化的接口，适用于单次传输数据，`host` 端导出数据后，在 `device` 端导入数据并检查或者做点其他的什么计算。

- 模板特化和 `SFINAE` 实现类型无感
- 字节流处理实现序列化和反序列化
- 支持 `POD` 类型，`string`，`vector`，自定义结构体参数
