
注意这里和 malloc 与 new 不同，后两个是申请到一个指针，这个指针指向一个内存空间，而此时需要的就是这么大的空间。

在 C++ 中，可以使用 `std::aligned_storage_t<sizeof(int)> storage;`，这样申请到了一块和 int 类型大小相同的 4 字节空间

```cpp
template<class _Ty, size_t _Len>
union _Align_type // 让联合体有_Ty 的对齐，有大小为_Len 字节的空间
{
	_Ty _Val;
	char _Pad[_Len];_
};
```
