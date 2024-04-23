
类模板实例化后定义了一个特定的类类型，因此可以使用`typedef`来引用实例化的类：

```cpp
typedef MyClass<int> IntMyClass;
```

`typedef`无法引用模板，因为模板并不是一个类型，即`typedef MyClass<T> TemplateMyClass;`是不允许的

但是可以这样，**给类模板定义一个类型别名**

```cpp
template<typename T> using twin = pair<T, T>;
twin<int> test; // 这样 test 就是一个 pair<int ,int>类型的对象
```




