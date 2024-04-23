
假如有以下代码：

```cpp
class A;
void ff(A&)
{
	std::cout << "LF" << std::endl;
}
void ff(A&&)
{
	std::cout << "RF" << std::endl;
}
void gg(A& L)
{
	std::cout << "G LF" << std::endl;
	ff(L);
}
void gg(A&& R)
{
	std::cout << "G RF" << std::endl;
	ff(R);
}

int main()
{
	gg(A());
	auto&& Test = A();
	gg(Test);
}
```

运行后的结果为：
```cpp
G RF
LF
G LF
LF
```

可以看到，
- 第一次调用函数 `gg(A());` 时，调用的是*右值版本的 GG 与左值版本的 FF*：说明传入的右值在函数内部变成了一个左值
- 第二次调用函数 `gg(Test)` 时，调用的是左值版本的 GG 与左值版本的 FF：说明右值引用本身是一个左值

以及从这里可以看到：
![[Pasted image 20240416174201.png]]

**右值引用，其实是一个左值。右值引用首先是一个引用！** 当一个右值赋给一个右值引用时，这个右值的生命周期就和这个右值引用一致了。

为了保持传入参数的这个右值性质，就需要用到完美转发 `std::forward()`

```cpp
void gg(A&& R)
{
	std::cout << "G RF" << std::endl;
	ff(std::forward<A>(R)); // 利用完美转发传一个右值进去
}
```

**思考：`std::forward` 如何实现？**

```cpp
_EXPORT_STD template <class _Ty>
_NODISCARD _MSVC_INTRINSIC constexpr _Ty&& forward(remove_reference_t<_Ty>& _Arg) noexcept {
    return static_cast<_Ty&&>(_Arg);
}
```

可以看到，forward 内部对右值引用进行了一次强制转换，转换为了右值

不过具体的实现涉及到引用折叠等更深的东西。这里暂时先不过度深入。

