#include <iostream>

#include "MyVector.h"

class MyClass
{
public:
	int count = 0;
	MyClass(int _count) : count(_count) {}

	friend std::ostream& operator<<(std::ostream& o, const MyClass& obj)
	{
		o << obj.count;
		return o;
	}
	
};

template<typename T>
void printVec(const MyVector<T>& obj);

int main()
{
	MyClass class01(1);
	MyClass class02(2);
	MyClass class03(3);
	
	// 插入元素
	std::cout << "Insert Elements" << std::endl;
	MyVector<MyClass> vec1;
	vec1.push_back(class01);
	vec1.push_back(class02);
	vec1.push_back(class03);
	printVec<MyClass>(vec1);

	// 下标运算符
	vec1[0] = 4;
	vec1[1] = 5;
	vec1[2] = 6;
	std::cout << "Subscript Operator" << std::endl;
	std::cout << vec1[0] << std::endl;
	std::cout << vec1[1] << std::endl;
	std::cout << vec1[2] << std::endl;

	// 拷贝构造
	vec1[0] = 7;
	vec1[1] = 8;
	vec1[2] = 9;
	std::cout << "Copy Constructor" << std::endl;
	MyVector<MyClass> vec2(vec1);
	printVec<MyClass>(vec2);

	// 重载赋值操作符
	std::cout << "Overloaded Assignment Operator" << std::endl;
	MyVector<MyClass> vec3;
	vec3 = vec1;
	printVec<MyClass>(vec3);

}

template<typename T>
void printVec(const MyVector<T>& obj)
{
	for (std::size_t index = 0; index < obj.size; index++)
	{
		std::cout << obj[index] << std::endl;
	}
}

