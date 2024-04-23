
用于获取表达式类型，举例：
```cpp
int x = 5;
decltype(x) y; // 使用x的类型声明了一个y
```

在模板编程中，`decltype` 常和 `std::declval` 结合使用

在 [[C++模板：判断类中是否存在某个成员函数]]中，有个判断重载操作符的代码：
```cpp
class A
{
public:
    int operator()(float&);
};
template<typename T, typename Ret, typename ... Args>
struct THasOperatorParentheses 
{
    template<typename U, typename RR = decltype(std::declval<U>()(std::forward<Args>(std::declval<Args>())...))>
    static constexpr bool Check(U*)
    {
        return std::is_same_v<RR, Ret>;
    }  
    static constexpr bool Check(...) { return false; }
    enum
    {
        value = Check(static_cast<T*>(nullptr))
    };
};
constexpr bool test = THasOperatorParentheses<A, int, float&>::value;
```

在模板参数列表中 `typename ... Args`，表示 Args 是一个可变参数列表，接收任意类型或任意个数的参数

接下来大概整理一下 `template<typename U, typename RR = decltype(std::declval<U>()(std::forward<Args>(std::declval<Args>())...))>` 这里的细节

-  `decltype` 用于获取一个表达式的类型
-  `std::declaval<U>()` 则是创建了一个类型 U 的假想对象
- `std::forward<Args>(std::declval<Args>())` 内部的 `std::declval<Args>()` 同理创建了一个假想的参数列表，通过 `std::forward<Args>` 保持参数的值类别（左值还是右值）
- `(std::forward<Args>(std::declval<Args>())...)` 最后的 `...` 表示将参数包 `Args` 展开

综上，通过 `std::declaval<U>()` 创建一个假想 U 类型的对象，利用 `std::forward<Args>(std::declval<Args>())` 创建假想 Args 参数列表并通过 `std::forward<Args>` 保持值类别，`...` 将参数包展开从而传入类型 U 的假想对象的参数列表中



