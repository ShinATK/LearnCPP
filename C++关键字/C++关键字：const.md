

# 函数参数声明为`const`，保证函数适用于不能拷贝的类型，避免了费事的拷贝过程

```cpp
template<typename T>
int Compare(T& x, T& y);
```

`Compare()`接收两个类型`T`对象的引用，避免了传参过程中的拷贝

