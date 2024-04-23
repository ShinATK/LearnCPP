# C++ 的容器：vector

Vector 的好处：
- 空间大小可变
- 支持随机存取
不好的地方：
- 频繁的调整大小会影响性能
- **需要注意 Vector 的迭代器失效问题，因为 vector 的大小改变后其内存地址会发生变化，原来的迭代器会失效**
## STL 中的实现

通过维护三个迭代器：`_First` `_Finish` `_End_Of_Sotrage`


## 自己实现

需要实现的内容有：
- 数据成员：
	- 大小 `int size`
	- 容量 `int capacity`
	- 指针 `T* myArray`
- 成员函数：
	- 构造函数 `MyVector<T>::MyVector()`
	- 析构函数 `MyVector<T>::~MyVector()`
	- 拷贝构造函数 `MyVector<T>::MyVector(const MyVector<T>& obj);`
	- 添加元素 `MyVector<T>::push_back(T& new_ele);`
	- 动态扩容 `MyVector<T>::resize();`
	- 重载
		- 下标运算符 `T& MyVector<T>::operator[](int index);` 注意多实现一个 const 版本的
		- 赋值运算符 `MyVector<T>& MyVector<T>::operator=(const MyVector<T>& obj);`
```cpp
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <iostream>

static constexpr int DEFAULT_SIZE = 2;

template<typename T>
class MyVector
{
public:
    int size = 0;
    int capacity = DEFAULT_SIZE;
    T* myArray = nullptr;

    MyVector();
    ~MyVector();
    // 拷贝构造
    MyVector(const MyVector& obj);

    // 动态扩容
    void resize();

    // 添加元素
    void push_back(const T& new_ele);

    // 重载操作符
    T& operator[](int index);
    const T& operator[](int index) const; // TODO: 注意多实现一个 const 版本，提供给 const MyVector<T>对象
    MyVector<T>& operator=(const MyVector<T>& obj);
};
#endif
```

代码实现：[[MyVector.h]]

### 构造函数和析构函数

```cpp
template<typename T>
inline MyVector<T>::MyVector()
{
    myArray = (T*)malloc(capacity * sizeof(T));
    if (myArray == nullptr)
    {
        throw std::bad_alloc();
    }
}
template<typename T>
inline MyVector<T>::~MyVector() // TODO: 记住涉及到指针的，针对性实现一个析构
{
    for (std::size_t index = 0; index < size; index++)
    {
        myArray[index].~T();
    }
    free(myArray);
}
```

### 拷贝构造函数

```cpp
// 拷贝构造
template<typename T>
inline MyVector<T>::MyVector(const MyVector<T>& obj)
{
    myArray = (T*)malloc(obj.capacity * sizeof(T)); // TODO：先 malloc，再改变 capacity，防止 malloc 失败但 capacity 已经改变
    if (myArray == nullptr)
    {
        throw std::bad_alloc();
    }

    this->size = obj.size;
    this->capacity = obj.capacity;
    for (std::size_t index = 0; index < size; index++)
    {
        new (&myArray[index]) T(obj[index]);
    }
}
```

### 移动构造函数


### 动态扩容： `resize()`

注意事项：
- `malloc` 不一定成功，注意判断是否为空指针，并抛出异常
- 先 `malloc` 再修改容量，防止 `malloc` 失败而容量却已经被修改

```cpp
// 动态扩容
template<typename T>
inline void MyVector<T>::resize()
{
    T* temp = (T*)malloc(capacity * sizeof(T) * 2); // TODO：涉及到 malloc 的，多个心眼
    if (temp == nullptr) // 判断下有没有分配到内存
    {
        throw std::bad_alloc();
    }

    for (std::size_t index = 0; index < size; index++)
    {
        new (&temp[index]) T(myArray[index]);
    }
    for (std::size_t index = 0; index < size; index++)
    {
        myArray[index].~T();
    }
    free(myArray);
    capacity *= 2;
    myArray = temp;
}
```

### 添加元素：`push_back()`

```cpp
// 添加元素
template<typename T>
inline void MyVector<T>::push_back(const T& new_ele)
{
    if (size == capacity)
    {
        resize();
    }
    new (&myArray[size++]) T(new_ele);
}
```

### 操作符重载：`operator[]`
注意事项：
- 多实现一个 `const` 版本的，提供给 `const` 对象使用
```cpp
// 重载操作符
template<typename T>
inline const T& MyVector<T>::operator[](int index) const // TODO：记住多设置一个 const 版本给 const 对象使用
{
    if (index < size)
    {
        return myArray[index];
    }
    else
    {
        throw std::out_of_range("Index out of range!");
    }
}
template<typename T>
inline T& MyVector<T>::operator[](int index)
{
    if (index < size)
    {
        return myArray[index];
    }
    else
    {
        throw std::out_of_range("Index out of range!");
    }
}
```

### 操作符重载：`operator=`

注意事项：
- 先检查是否是自我赋值

```cpp
template<typename T>
inline MyVector<T>& MyVector<T>::operator=(const MyVector<T>& obj)
{
    if (this != &obj) // TODO: 注意排除自我赋值
    {
        for (std::size_t index = 0; index < size; index++)
        {
            myArray[index].~T();
        }
        free(myArray);

		myArray = (T*)malloc(capacity * sizeof(T));
		if(myArray == nullptr)
		{
			throw std::bad_alloc();
		}
        for (std::size_t index = 0; index < obj.size; index++)
        {
            new (&myArray[index]) T(obj[index]); 
        }
        this->capacity = obj.capacity;
        this->size = obj.size;
    }

    return *this;
}
```

# 可参考链接

- [vector 使用及简单实现【STL】【附题】 - shawyxy - 博客园](https://www.cnblogs.com/shawyxy/p/16961587.html)
- [从零开始，打造自己的 STL（二。vector） - 知乎](https://zhuanlan.zhihu.com/p/34171833)

