#include <iostream>
using namespace std;

class Car { //Class Name 
    public: //Access
        string brand; //Attribute
        string model; //Attribute
        int year; //Attribute
        Car(string x, string y, int z) {
            brand = x;
            model = y;
            year = z;
        }
};

int main() {
     // Create Car objects and call the constructor with different values
    Car carObj1("BMW", "X5", 1965);
    Car carObj2("Ford","Mustang",1658);

    cout << carObj1.brand << " " << carObj1.model << " " << carObj1.year << "\n";
    cout << carObj2.brand << " " << carObj2.model << " " << carObj2.year << "\n";
    return 0;
}