# Conventions #

In this file we will discuss the conventions used in this project.

## File Structure ##

### Header Files (`.h`) ###
All the header files must end with `.h` and be in the folder `include/`.  
The header files must start with the line `#pragma once`.  
All `class`\ `struct`\ `enum`\ `namespace` must be declared in a header file.

Header files must start with the includes:
first the header that not in the project (like `#include <iostream>`),    
then the headers that in the project (like `#include "MyHeader.h"`),  
then declare needed classes (like `class MyClass;`) (to avoid include loops).


### Code Files (`.cpp`) ###
All the code files must end with `.cpp` and be in the folder `src/`.
All `class` there must be a `.cpp` file (with the same name as the class).  
`namespace` may have a `.cpp` file (with the same name as the namespace).

The Code files must start with the includes:  
first the header that not in the project (like `#include <iostream>`),  
then the headers that in the project (like `#include "MyHeader.h"`).  

## Naming ##

### Files ###
Almost all the files must be named in `PascalCase`, except for special files 
like `README.md` and `LICENSE`. or files of classes that contain acronyms that
are usually written in UPPERCASE (like `SFML`).

### Classes ###
All the classes must be named in `PascalCase`.  
Classes data members must be declared `private` and must be named in 
`camelCase` and start with `m_`.  
Classes methods must be named in `camelCase`.
 
for example:
```cpp
class MyClass {
private:
    int m_MyDataMember;
public:
    void myMethod();
};
```

### Structs ###
All the structs must be named in `PascalCase`.
All the structs data members must be declared `public` and must be named in
`camelCase` (without `m_`).  
Structs methods must be named in `camelCase`, if the struct have more than 
just a constructor consider using a class instead.

for example:
```cpp
struct MyStruct {
public:
    int myDataMember;
    MyStruct(int myDataMember): myDataMember(myDataMember) {};
};
```

### Enums and Constants ###
All the enums must be named in `PascalCase` as Singular form.
All the enums values and the constants must be named in `UPPERCASE`.

for example:
```cpp
enum class VehicleType {
    CAR,
    TRUCK,
    MOTORCYCLE
};
const int MAX_VEHICLES = 10;
```

### namespaces ###
All the namespaces must be named in `snake_case`.