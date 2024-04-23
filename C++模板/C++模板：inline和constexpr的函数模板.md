
函数模板可以声明为 inline 或 constexpr，方式如下：

```cpp
template<typename T>
inline T GetMin(const T&, const T&);
```

即，inline 或 constexpr 要放在模板参数之后，返回值类型之前

