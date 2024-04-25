
# 模板类型转换

函数模板的实参可以被用来初始化函数的形参，并且如果这个函数的形参类型使用了模板类型参数，根据特殊的初始化规则，同样会初始化模板类型参数

只有两种转换可以：
- **const 转换**：非 const 对象的引用或指针传递给一个 const 的引用或指针形参
- **数组或函数指针的转换**：如果形参不是引用类型，会对数组或函数类型的实参进行指针转换，前者为指向首元素的指针，后者为对应函数类型的指针

其他转换：
- 算术转换
- 派生类到基类的转换
- 用户定义的转换
都不能应用于函数模板

```cpp
template <typename T> T fobj(T, T) {}
template <typename T> T fref(const T&, const T&) {}


void Test()
{
	std::string s1("a value");
	const std::string s2("another value");
	fobj(s1, s2);
	fref(s1, s2);

	int a[10], b[42];
	fobj(a, b);
	//fref(a, b); // a 类型为 int[10]，b 类型为 int[42]
	using a_type = decltype(a);
	using b_type = decltype(b);
	constexpr bool result = std::is_same_v<a_type, b_type>;
}
```

# 显式指定实参的类型转换

如果模板类型参数已经显式指定，也可以像普通函数一样进行类型转换

```cpp
template<typename T>
void TestClassFunction(T in_class) {}

class A {};
class B : public A {};

void Test()
{
    A a;
    B b;
    TestClassFunction<A>(a);
    TestClassFunction<A>(b);
}
```

像是使用父类实例化，传入形参是子类同样可以

# 利用显式指定实参的类型转换，传入两个不同的类型

使用方式，标准库的 `max`，接收两个参数返回较大的实参

```cpp
int i = 0, j = 1;
double d = 3.0;
std::max(i, j);
std::max<double>(i, d); // 直接传入 i 和 d 会报错，但是显式指定 double 再传入就可以，因为可以从 int 转换到 double
// 写成 int 也不会报错（只是提一句）
```

# 有的模板要求显式传入模板实参

例如：`std::make_shared`，就要求显式传入实参，因为需要根据传入的模板实参计算需要分配多大的空间






