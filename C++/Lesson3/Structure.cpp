// Basic Structure
#include <iostream>
using namespace std;

struct Persona {
    string name;
    int age;
    float height;

};

int main() {
    //Declare a variable calles "Guy"
    Persona p1;

    //Assing values to the members of the structure
    p1.name = "Juan";
    p1.age = 25;
    p1.height = 1.65;

    //Access and show the values
    cout << "Name: " << p1.name << endl;
    cout << "Age: " << p1.age << endl;
    cout << "Height: " << p1.age << endl;
    return 0;
}
