# 自动化测试

> 见过很多诸如 `NEW_TESTCASE` 自定义测试样例并执行的写法，于是想着自己实现一个。

而且写项目的时候一定要自动化测试，不然难以测到一些边边角角的错误。

## 介绍

```c
TestCase(main, tese1)
```

会添加一个测试样例，注册一个类到 `test_funcs` 中，在 `RunAllTestCases` 的时候会执行全部被注册的测试类的 `Run` 方法。

执行这个方法时，会返回一个 `TestOp` 对象，如果测试失败，对象析构时会直接调用 `exit(1)` 退出程序，并打印错误日志。


# 参考

https://github.com/tangyibo/serialize