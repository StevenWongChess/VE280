# Lecture 12: Exception

## Exception propagation

1. the remaining part of the function, if not found, proceed to step 2
2. caller of the function, if not found, proceed to step 3
3. caller of the caller... 

```cpp
void foo() {
    throw 1;
}
void bar() {
    foo();
}
int main() {
    try {
        bar();
    }
    catch (...) {
        //default constructor
        std::cout << "Caught!";
        return 0;
    }
    return 0;
}
```

## Examples

1. the **first** catch block with the **same** type as the thrown exception object will handle the exception
2. `catch(...) {}` is the default handler that matches any exception type

```cpp
int foo(int i) {
    try {
        if (foo) throw 2.0;
        if (bar) throw 1;
        if (baz) throw 'a';
    }
    catch (double v) {
        // catch exceptions thrown by if (foo)
    }
    catch (int a) {}
    catch (char c) {}
    catch (...) {
        //default handler
    }
    ...// Do something next
}
```

1. Use EFFECTS clause to tell the caller that a function can throw an exception:

```cpp
int factorial (int n) {
    // EFFECTS: return n! if n >=0, throws int n if n < 0
}
```

# Lecture 13: Abstract Data Type

### `struct` Type

1. Concrete Implementation: every detail is known to all users.

2. Example

   ```c++
   struct Grades{
       char name[9];
       int mid;
       int final;
   };
   ```

3. Disadvantages of `struct`

   A change to the definition will make change throughout the program, and recompile everything.

### Abtract Data Types

1. An ADT provides an abstract description of **values** and **operations**.
2. Advantages
   1. Information hiding: Leave off details of objects and operations on objects.
   2. Encapsulation: Define objects and their operations in the same place in one entity.
3. Benefits:
   1. Local: The implementation of other components are independent of the implementation of the ADT.
   2. Substitutional: Changing the implementation of ADT will not be detected.
4. Concrete Representation:
   1. Definition: The way that values are represented and how operations are implemented;
   2. Availability: Operation defined in the ADT.

### Class Types

#### Structure

Comments to explain things

- **OVERVIEW** 
  Short description of class
- **RME** 
  What the function does
- **REP INVARIANT** 
  What the variable stands for

```c++
class Name{
    
	//Overview: xxx
	int v;//parameters
    
public:
	int get_v();//operations
    //Requires: xxx
    //Effects: xxx
    
    void set_v(int newValue);
	//Requires: xxx
    //Modifies: this
    //Effects: xxx
    
};
```

1. Do not forget `;`
2. `this` = this object.

1. Availability
   1. Private:
      1. Default: Every member (data member + function member) is private;
      2. Private member is visible only to other members; 
      3. Private hides implementation to type users.
   2. Public:
      1. After the `public:` keyword is visible to others;
      2. Usually, we write `set` and `get` functions to get private data members;
      3. Do not implement functions in the class definition because it exposes information. Do it in a `.cpp`

```c++
int Name::get_v(){
    return v;
}
```

#### Instantiate

1. Declare an object `Name foo;`
2. Call functions `foo.set_v(1);`
3. Difference between normal function call and member function call: Other members of the object is visible to the member functions, but not to the normal functions.

#### Passing a class

1. Classes are passed by value;
2. To pass by reference:
   1. Use a pointer: `*ptr.get_v(); ` == `ptr->get_v();`
   2. Use a reference.

#### Data

Variables to store information

- **Representation** 
  *“The user want a set, so it can be an array, or maybe a linked list.”*
- **Representation Invariant** 
  What the variable stands for and can be taken as granted immediately before and after an operation 
  *“numElts always equals to the number of elements in the set, so size() can use this and doesn’t need to count every time!”*

#### Method

Functions to get things done

- **Maintenance** 
  Constructor for initialization
- **Operation** 
  For users to use
- **Helper** 
  Useful because other methods may want to use the same functionality
- **Const Qualifier** 
  const object, const function, const this
- **Implementation** 
  Detect error, get things done, 
  repair invariant

1. Constructor
   1. Default constructor

   ```c++
   ClassName();
   	//EFFECTS: Create a default class;
   
   ClassName::ClassName(): variable1(value1), variable2(value2){}
   ```

   1. Normal Constructor

   ```c++
   ClassName(int v);
   
   ClassName::ClassName(int v){
       int Num = v; 
   }
   ```

2. `const` Member Functions
   1. `this`: Each member function of a class has a an extra implicit parameter `this`, which is a pointer to current instance on which the funtion is invoked. 
   2. `in size() const;` modifies the implicit `this` pointer to a const instance, therefore the funcition `size()` no longer modifies the object.
   3. A `const` object can only call its `const` member funcitons.

   ```c++
   Class Name{
       int[10] array;
       int num;
       
   public:
       int size() const;
       bool insert(int new);
   };
   
   Const Name my_name;
   int NameSize = my_name.size(); // √
   bool isInserted = my_name.insert(i); // ×
   ```

3. A `const` member function can only call other `const` member functions.

#### Example: Mutable Set.

```c++
const int MAXELTS = 100;
class IntSet {
   public:
    IntSet();
    void insert(int v);
    void remove(int v);
    bool query(int v) const;
    int size() const;

   private:
    int elts[MAXELTS];
    int numElts;
    int indexOf(int v) const;
};
```



# Credit

SU2019 & SU2020 VE280 Teaching Groups.

VE 280 Lecture 12-13
