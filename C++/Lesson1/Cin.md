Cin is an iostream library object used for data input/output.

It allows capturing user input and storing it in a variable.

Syntax: std:cin >> Variable

Basic Example:
```
#include <iostream>

int main() {
	int age;
	std::cout << “Enter your age: ”;
	std::cin >> age
	std::cout << “Your age is: ” << age;
	return 0;
}
```
Cin features.

1* Cin can read data of different types such as:
	* int
	* float
	* double
	* char
	* std::string

2* Input chaining:
String entries on a single line

int a,b;
std::cin >> a >> b;

Translated with DeepL.com (free version)
