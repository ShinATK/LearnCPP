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
    // ��������
    MyVector(const MyVector& obj);

    // ��̬����
    void resize();

    // ���Ԫ��
    void push_back(const T& new_ele);

    // ���ز�����
    T& operator[](int index);
    const T& operator[](int index) const; // ע���ʵ��һ��const�汾���ṩ��const MyVector<T>����
    void operator=(const MyVector& obj); 
};



template<typename T>
inline MyVector<T>::MyVector()
{
    myArray = (T*)malloc(capacity * sizeof(T));
}

template<typename T>
inline MyVector<T>::~MyVector()
{
    for (std::size_t index = 0; index < size; index++)
    {
        myArray[index].~T();
    }
    free(myArray);
}

// ��������
template<typename T>
inline MyVector<T>::MyVector(const MyVector<T>& obj)
{
    this->size = obj.size;
    this->capacity = obj.capacity;
    myArray = (T*)malloc(capacity * sizeof(T));
    for (std::size_t index = 0; index < size; index++)
    {
        new (&myArray[index]) T(obj[index]);
    }
}

// ��̬����
template<typename T>
inline void MyVector<T>::resize()
{
    T* temp = (T*)malloc(capacity * sizeof(T) * 2);
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

// ���Ԫ��
template<typename T>
inline void MyVector<T>::push_back(const T& new_ele)
{
    if (size == capacity)
    {
        resize();
    }
    new (&myArray[size++]) T(new_ele);
}


// ���ز�����
template<typename T>
inline const T& MyVector<T>::operator[](int index) const
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
inline void MyVector<T>::operator=(const MyVector<T>& obj)
{
    if (this == &obj)
    {
        return *this;
    }
    for (std::size_t index = 0; index < size; index++)
    {
        myArray[index].~T();
    }
    free(myArray);

    this->capacity = obj.capacity;
    this->size = obj.size;
    myArray = (T*)malloc(capacity * sizeof(T));
    for (std::size_t index = 0; index < size; index++)
    {
        new (&myArray[index]) T(obj[index]);
    }
}




#endif