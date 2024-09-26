Strings, what is strings

In C++ a string is a data type used to store and manipulate character sequences.
Example: “Hello World” is a string

Variable of type string assigned to a value:
string greeting = “Hello”;


What you can do with this:

Code example: print “Hello, World” with cout, store it in string in variable greeting.
```
#include <iostream>
#include <string>

int main() {
	std::string greeting = “Hello, World”:
	std::cout << greeting << std::endl;
	return 0;
}
```
* Easy Concatenation:
You can concatenate other string strings.

std::string name = “John”;
std::string message = “Hello, ” + name;


* Useful functions:
You can concatenate other functions to the string

std::string text = “Hello, World”;
int length = text.lenght(); // Returns 11.

Safety and ease:

Takes care of memory management, avoiding memory handling errors with C.

Se encarga de la gestion de memoria, evitando errores de manejo de memoria con C
