
# 尾置返回类型的类型转换

假如有如下模板：

```cpp
template<typename _Iterator>
??? &fcn(_Iterator beg, _Iterator end)
{
    return *beg;
}
```

我们希望让这个函数接收容器的一对迭代器，并返回序列中一个元素的引用

但是这里我们只设置了一个接收迭代器了类型的模板参数，而不知道容器内部元素的具体类型

在调用点的语法为：

```cpp
vector<int> vi{0};
auto ele = fcn(vi.begin(), vi.end());
```

`decltype(*beg)`可以获取到元素对类型，但是在函数调用点`auto &ele = fcn(vi.begin(), vi.end());`所能提供给编译器的信息，只有传入的迭代器类型，在真正开运行进入迭代之前，我们都无法得到这个`*beg`，自然也就无法在编译阶段让编译器得知这个元素的类型

这时就需要用到**尾置返回类型**

```cpp
template<typename _Iterator>
auto fcn(_Iterator beg, _Iterator end) -> decltype(*beg)
{
    return *beg;
}
```

对迭代器解引用后得到一个左值，**再经过`decltype`后推断出是一个元素类型的引用**，最后经过`auto`，会将引用去掉，从而得到元素的类型

参考：[auto 关键字的推导原则](../C++关键字/C++关键字：auto.md)

这里的 `fcn_ret` 实际上是一个 `int` 类型


# 不要返回引用，要返回值

`std::remove_reference`

使用方式：

```cpp
std::remove_reference<int&> // 得到 int
std::remove_reference<string&> // 得到 string
```

