// PolymorphExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int GetSize(int x)
{
	return x;
}

int GetSize(std::string x)
{
	return x.length();
}

class Animal
{
public:

	int requestId = 0;

	virtual void MakeNoise()
	{
	std::cout << "Animal noise." << std::endl;
	}

	bool ChangeValue(int&) const;

};

class Dog : public Animal
{
public:
	void MakeNoise() override
	{
		std::cout << "Woof woof." << std::endl;
	}
};

class Cat : public Animal
{
public:
	void MakeNoise() override
	{
		std::cout << "Meow meow." << std::endl;
	}
};


void Stroke(Animal& animal)
{
	animal.MakeNoise();
}


bool Animal::ChangeValue(int& outVal) const
{
	if (outVal)
	{
		outVal += 10;
		return true;
	}
	else {
		return false;
	

	}
};

int main()
{


	//std::cout << GetSize(5) << std::endl;
	//std::cout << GetSize(10) << std::endl;

	//std::cout << GetSize("Hello World") << std::endl;

	Dog dog;
	Cat cat;
	Stroke(dog);
	Stroke(cat);

	int outVal = 100;
	auto res = dog.ChangeValue(outVal);
	if (res)
	{
		std::cout << "dog out " << outVal << std::endl;
	}
	else
	{

		std::cout << "dog out nothing " << outVal << std::endl;
	}
	return 0;
}

