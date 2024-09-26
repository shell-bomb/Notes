//Overloaded Constructor example

#include <iostream>
using namespace std;

class Persona {
    public:
        string name;
        int age;

    // Default constructor (no argument)
    Persona() {
        name = "john Doe";
        age = 0; 
    }

    //Constructor with only one parameter
    Persona(string _name) {
        name = _name;
        age = 0;
    }

    //Constructor with 2 parameters
    Persona(string _name, int _age) {
        name = _name;
        age = _age;
    }

    //Method to display the information
    void informacion() {
        cout << "Name: " << name << ", Age: " << age << endl;

    }
};

int main() {
    //Creating objects with different constructors
    Persona persona1;
    persona1.informacion();

    Persona persona2("Juan"); //Constructor with one argument
    persona2.informacion();

    Persona persona3("GABE NEWELL", 29); //Constructor with 2 arguments
    persona3.informacion();
    return 0;

}