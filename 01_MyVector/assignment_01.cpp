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
	
	MyVector<MyClass> vec1;
	vec1.push_back(class01);
	vec1.push_back(class02);
	vec1.push_back(class03);

	printVec<MyClass>(vec1);

	MyVector<MyClass> vec2(vec1);
	printVec<MyClass>(vec2);
	vec2[0].count = -1;
	printVec<MyClass>(vec2);

}

template<typename T>
void printVec(const MyVector<T>& obj)
{
	for (std::size_t index = 0; index < obj.size; index++)
	{
		std::cout << obj[index] << std::endl;
	}
}

