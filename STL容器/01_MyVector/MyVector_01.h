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
    const T& operator[](int index) const; // TODO: 注意多实现一个const版本，提供给const MyVector<T>对象
    MyVector<T>& operator=(const MyVector<T>& obj);
};


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
inline MyVector<T>::~MyVector() // TODO: 涉及到指针的，针对性实现一个析构
{
    for (std::size_t index = 0; index < size; index++)
    {
        myArray[index].~T();
    }
}

// 拷贝构造
template<typename T>
inline MyVector<T>::MyVector(const MyVector<T>& obj)
{
    myArray = (T*)malloc(obj.capacity * sizeof(T)); // TODO：先malloc，再改变capacity，防止malloc失败但capacity已经改变
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

// 动态扩容
template<typename T>
inline void MyVector<T>::resize()
{
    T* temp = (T*)malloc(capacity * sizeof(T) * 2); // TODO：涉及到malloc的，多个心眼
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


// 重载操作符
template<typename T>
inline const T& MyVector<T>::operator[](int index) const // TODO：记住多设置一个const版本给const对象使用
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
        for (std::size_t index = 0; index < obj.size; index++)
        {
            new (&myArray[index]) T(obj[index]); 
        }
        this->capacity = obj.capacity;
        this->size = obj.size;
    }

    return *this;
}


#endif