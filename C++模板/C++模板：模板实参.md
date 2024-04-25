
有这么一个模板：

```cpp
template<class T = int>
class TestClass
{
public:
    T value;
};

TestClass<float> test1; // 使用传入的 float 类型实例化
TestClass<> test2; // 使用默认的 int 类型实例化
```


