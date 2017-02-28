# Note!
this is something that I will be adding to and not adopting yet. Have to think abou this and how I want to
code in c++. 

# 1 Intro
[something here]

# 2 Naming Conventions

## 2.0 Naming notation
| Notation                          | Example      |
| :-------------------------------- | :----------- |
| Snake case Standard C notation    | mouse_weight |
| Hungarian notation                | iMouseWeight |
| Camel case (or lower Camel case)  | mouseWeight  |
| Pascal case (or upper Camel case) | MouseWeight  |
| All capitals case                 | MOUSE_WEIGHT |

## 2.1 Type
Names repersenting 'Type' must be mixed case with upper case (Pascal case).
``` c++
struct MyStruct { };
class MyClass { };
```

## 2.2 Variables
Public variables must be all lowercase with underscore seperations (snake case). 
Private variables must start with an underscore and be all lowercase with underscore seperators (snake case).
``` c++
class SomeClass
{
public:
  int some_public_member = 0;

private:
  int _some_private_member = 0;
}
```

## 2.3 Functions and methods
Names repersenting methods and functions must be verbs and written using snake case.
``` c++
String get_name() { return name; }
void compute_total();
u32 max(u32 first_number, u32 second_number);
```

## 2.4 Constants
Named constants including enums must be all capitals using underscores as seperators.
``` c++
#define EDN_PASTE( _, __ )  _##__
enum class WindowFlags
{
    FULLSCREEN = 1 << 0,
    WINDOWED = 1 << 1,
    ...
}
```

## 2.5 Namespaces
Names repersenting namespaces should all be lowercase. Namespaces should be abbrviated when at all possible.
``` c++
edn::ecs::Component();
```

## 2.6 Typedefs and using statements
The use of 'using' statements should be used instead of 'typedef' statements. Global typedefs should be writen like 
type names. This allows for easier exchanges in cases where typenames will be replaced with actual types
later. If the using or typedef is part of a class then it should be written the same as a variable.
``` c++
#if defined(EDN_WINDOWS)
	using Window = win32::Window;
#endif

template<typename T>
class MyClass
{
public:
    using value_type = T;
};
```

## 2.7 Template parameters
Names repersenting template parameters should be named the same as types. In the case where there are
few template parameters single letters can be used if the meaning is clear.
``` c++
template<typename T> // Use of T as the meaning of T is clear
template<int Rows, bool RowMajor, typename SortingFunctor, typename ValueType> // Use of type names as to distinguish differences
```
## 2.8 Example
``` c++
namespace edn
{
#if defined(EDN_WINDOWS)
    using Window = win32::Window;
#endif

    enum class WindowFlags
    {
        FULLSCREEN = 1 << 0,
        WINDOWED = 1 << 1,
    }

    template<typename T>
    class MyClass
    {
    public:
        using value_type = T;

        int some_public_member;
        void some_public_method();

    protected:
        int _some_protected_member;
        void _some_protected_method();

    private:
        int _some_private_member;
        void _some_private_method();
    };
}
```

# 3 Formating

## 3.1 Class formatting
Classes are structured in the order of public, protected, and then private. This is because:

 * Programmers should care about the class' interface more than the implementation
 * When programmers need to use a class they need the interface of the class

Within each access level section code is ordered as followed:
 - Life cycle
   - The life cycle section is for methods that control the life cycle of an object. Typically these methods include constructors, destructors, and state machine methods.
 - Operations
   - Non access and inquery methods here. A programmer will look here for the meat of a class's interface.
 - Operators
   - Place all operators and overloads here
 - Access
   - Attribute accessors here.
 - Inqueries
   - These are is_* methods. When you are asking a question if a value or state is 'something'. Ex: is_open()

## 3.2 Accessor style
Getters and setters can be the same name and determined if there are parameters passed or not.
``` c++
class MyClass
{
public:
    u32 age();
    void age(u32 age);
private:
    u32 _age;
};

MyClass mc;
auto age = mc.age();
mc.age(23);

```

Getters and setters should preform some sort of task besides just getting and setting a private variable.