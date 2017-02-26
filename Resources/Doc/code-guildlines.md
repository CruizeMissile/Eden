# Note!
this is something that I will be adding to and not adopting yet. Have to think abou this and how I want to
code in c++. 


# 3 Naming Conventions

## 3.0 Naming notation
```
Notation                            Example
----------------------------------------------------
Snake case Standard C notation     |  mouse_weight
Hungarian notation                 |  iMouseWeight
Camel case (or lower Camel case)   |  mouseWeight
Pascal case (or upper Camel case)  |  MouseWeight
All capitals case                  |  MOUSE_WEIGHT
```

## 3.1 Type
Names repersenting 'Type' must be mixed case with upper case (Pascal case).
``` c++
struct MyStruct { };
class MyClass { };
```

## 3.2 Variables
Variables must be all lowercase with underscore seperations (snake case).
``` c++
int value;
Buffer frame_buffer;
```

## 3.3 Constants
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

## 3.4 Functions and Methods
Names repersenting methods and functions must be verbs and written using camel case.
``` c++
String getName() { return name; }
void computeTotal();
u32 max(u32 first_number, u32 second_number);
```

## 3.5 Namespaces
Names repersenting namespaces should all be lowercase. Namespaces should be abbrviated when at all possible.
``` c++
edn::ecs::Component();
```

## 3.6 Typedefs and using statements
Names repersenting typedefs and using statements should be written like type names. This allows
for easier exchanges in cases where typenames will be replaced with actual types later.
``` c++
typedef std::vector<std::String> StringList; // Not: _t to denote type
using EntityPtr = std::unique_ptr<Entity>;
```

## 3.7 Template parameters
Names repersenting template parameters should be named the same as types. In the case where there are
few template parameters single letters can be used if the meaning is clear
``` c++
template<typename T>
template<int Rows, bool RowMajor, typename SortingFunctor, typename ValueType>
```

## 3.8 Abbreviations and acronyms
Abbreviations and acronyms must not be uppercase when used as name.
``` c++
exportHtmlSource(); // NOT: exportHTMLSource();
openDvdPlayer();    // NOT: openDVDPlayer();
```