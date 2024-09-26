Simple Classes

Create a class
```c
// Create a Car class with some attributes
class Car {
  public:
    string brand;   
    string model;
    int year;
};



int main () {
    Car carObj1;
    carObj1.brand = "BMW";
    carObj1.model = "X5";
    carObj1.year = 1999;

    //Create another object in a car
    Car carObj2;
    carObj2.brand = "GHOST"
    carObj1.model = "ORB";
    carObj1.year = 1969;

    cout << carObj1.brand << " " << carObj1.model << " " << carObj1.year << "\n";
    cout << carObj2.brand << " " << carObj2.model << " " << carObj2.year << "\n";
    return 0;

}
```
