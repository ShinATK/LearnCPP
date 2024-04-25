
源代码：

```cpp
_EXPORT_STD template <class _Ty = void>
struct less {
    using _FIRST_ARGUMENT_TYPE_NAME _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS  = _Ty;
    using _SECOND_ARGUMENT_TYPE_NAME _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS = _Ty;
    using _RESULT_TYPE_NAME _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS          = bool;

    _NODISCARD constexpr bool operator()(const _Ty& _Left, const _Ty& _Right) const
        noexcept(noexcept(_Fake_copy_init<bool>(_Left < _Right))) /* strengthened */ {
        return _Left < _Right;
    }
};
```

使用如下

```cpp
const int a = 1, b = 2;
constexpr bool result = std::less<int>{}(a, b);
```

这里的 `std::less<int>{}` 表示创建了一个 `std::less<int>` 类型的临时变量，从而能够使用其内部的 `()` 重载
