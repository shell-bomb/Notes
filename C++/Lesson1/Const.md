The const function is used to declare variables that cannot be changed,
to protect this data from being changed

```
// C++ program to demonstrate the above concept
#include <iostream>

//driver code
int main()
{
	//const intx: CTE error
	// x = 9; CTE error
	const int y = 10;
	cout << y;
	
	return 0;
}
```
If an attempt is made to initialise the const variable without assigning an explicit value to it, a compile-time error is generated.
(CTE)

Syntax:

const data_type*var_name;

Syntax when the const pointer points to a const variable:

const data_type* const var_name;

Syntax when calling class name and object name

const class_name object_name;
