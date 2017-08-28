# 1 Introduction

This document lists C++ coding recommendations for Eden.

The main reason is for these guidles are to help me stick to a set style of coding. My ideas on coding style changes all the time. I am trying to get a set of guidlines that I can refer to and help me stick to them.

This guidelines were modified from [here](https://github.com/ethz-asl/programming_guidelines/wiki/Cpp-Coding-Style-Guidelines).

## 1.1 Layout of the Recommendations.

The recommendations are grouped by topic and each recommendation is numbered to make it easier to refer to.

Layout of the recommendations is as follows:

### n. Guideline short description
```c++
Example if applicable
```
Motivation, background and additional information.
The motivation section is important. Coding standards are a divisive topic and everyone has their own opinions. It is important to read the reasonf for the rule/guidline.

## 1.2 Recommendation Importance

In the guideline sections the terms must, should and can have special meaning. A must requirement must be followed, a should is a strong recommendation, and a can is a general guideline.

# 2 General Recommendations

### 1. Any violation to the guide is allowed if it enhances readability.
The main goal of the recommendation is to improve readability and thereby the understanding and the maintainability and general quality of the code. It is impossible to cover all the specific cases in a general guide and the programmer should be flexible.

### 2. The rules can be violated if there are strong personal objections against them.
The attempt is to make a guideline, not to force a particular coding style onto individuals.

# 3 Naming Conventions

# 3.1 General Naming Conventions

### 3. Nameing chart

| Notation                          | Example      |
| :-------------------------------- | :----------- |
| Snake case Standard C notation    | mouse_weight |
| Hungarian notation                | iMouseWeight |
| Camel case (or lower Camel case)  | mouseWeight  |
| Pascal case (or upper Camel case) | MouseWeight  |
| All capitals case                 | MOUSE_WEIGHT |

### 4. Names representing types must be in mixed case starting with upper case.
```c++
Line, Application, Controller
```
Common practice in the C++ development community.
### 5. Variable names must be all lower-case with underscores separating words.
```c++
line, savings_account
```
Common practice in the C++ development community. Makes variables easy to distinguish from types, and effectively resolves potential naming collision as in the declaration Line line;
### 6. Names representing methods or functions must be verbs and written in snake case.
```c++
get_name(), compute_width()
```
Common practice in the C++ development community. This is identical to variable names, but functions in C++ are already distinguishable from variables by their specific form.
### 7. Names representing namespaces should be all lowercase.
```c++
model::analyzer, io::iomanager, common::math::geometry
```
### 8. Names representing typedefs/using should be written like type names.
```c++
using PointVector std::vector<Point>; //NOT: PointVector_t, NOT: PointVector_type
using CameraPtr = std::shared_ptr<Camera>; //NOT: Camera_ptr
```
Using the same naming convention as for types allows easier exchange in cases where a typename is replaced by an actual type later.

### 9. Names representing template parameters should be named like types but with an trailing underscore or with a single capital letter in case there are few arguments and their meaning is clear.
While their use is exchangeable for template parameters, `typename` should be preferred to `class` as template parameter specifier.

```c++
template<typename T> ...
template<int Rows_, bool RowMajor_, typename SortingFunctor_, typename ValueType_> ...
```
Common practice in the C++ development community. This makes template names stand out relative to all other names used.

### 10. Abbreviations and acronyms must not be uppercase when used as name [4].
```c++
export_html_source(); // NOT: expor_HTML_source();
open_dvd_player();    // NOT: open_DVD_player();
```
Using all uppercase for the base name will give conflicts with the naming conventions given above.
### 11. Global variables should always be referred to using the :: operator.
```c++
::main_window.open(), ::application_context.get_name()
```
In general, the use of global variables should be avoided. Consider using singleton objects instead.
### 12. Generic variables should have the same name as their type.
```c++
void set_topic(Topic* topic) // NOT: void set_topic(Topic* value)
                             // NOT: void set_topic(Topic* aTopic)
                             // NOT: void set_topic(Topic* t)

void connect(Database* database) // NOT: void connect(Database* db)
                                 // NOT: void connect (Database* oracleDB)
```
Reduce complexity by reducing the number of terms and names used. Also makes it easy to deduce the type given a variable name only.
If for some reason this convention doesn't seem to fit it is a strong indication that the type name is badly chosen.

Non-generic variables have a role. These variables can often be named by combining role and type:
```c++
  Point  starting_point, center_point;
  Name   login_name;
```
### 13. Variables with a large scope should have long names, variables with a small scope can have short names.
Scratch variables used for temporary storage or indices are best kept short. A programmer reading such variables should be able to assume that its value is not used outside of a few lines of code. Common scratch variables for integers are i, j, k, m, n and for characters c and d.
### 14. The name of the object is implicit, and should be avoided in a method name.
```c++
line.get_length();   // NOT: line.get_line_length();
```
The latter seems natural in the class declaration, but proves superfluous in use, as shown in the example.
## 1.2 Specific Naming Conventions

### 15. The terms get/set must be used where an attribute is accessed directly. Use get_variable_ref() if a reference is returned:
```c++
employee.get_name();
employee.set_name(name);

matrix.get_element(2, 4);
matrix.set_element(2, 4, value);

person.get_age_ref();
```
Common practice in the C++ development community.

### 16. The term compute can be used in methods where something is computed.
```c++
valueSet->compute_average();
matrix->compute_inverse()
```
Give the reader the immediate clue that this is a potentially time-consuming operation, and if used repeatedly, he might consider caching the result. Consistent use of the term enhances readability.
### 17. Plural form should be used on names representing a collection of objects.
```c++
vector<Point>  points;
int            values[];
```
Enhances readability since the name gives the user an immediate clue of the type of the variable and the operations that can be performed on its elements.
### 18. Iterator variables should be called i, j, k if the loop is rather small (less than 10 lines) For larger loops it makes sense to use names sufficed by idx:
```c++
for (int i = 0; i < nTables); ++i)
{
  :
}
for (int pointIdx = 0; pointIdx < nPoints); ++pointIdx)
{
  :
//potentially lots of code
  :
}
```
The notation is taken from mathematics where it is an established convention for indicating iterators.
Variables named j, k etc. should be used for nested loops only. This also follows the rule of having longer names for variables with larger scope.

Iterators should be called `it`
```c++
for (vector<MyClass>::iterator it = list.begin(); it != list.end(); ++it)
{
  Element element = *it;
  ...
}
```

### 19. The prefix is should be used for boolean variables and methods.
```c++
is_set, is_visible, is_finished, is_found, is_open
```
Common practice in the C++ development community.
Using the is prefix solves a common problem of choosing bad boolean names like status or flag. `is_status` or `is_flag` simply doesn't fit, and the programmer is forced to choose more meaningful names.

There are a few alternatives to the is prefix that fit better in some situations. These are the has, can and should prefixes:

```c++
  bool has_license();
  bool can_evaluate();
  bool should_sort();
```
### 20. Complement names must be used for complement operations.
```c++
get/set, add/remove, create/destroy, start/stop, insert/delete,
increment/decrement, old/new, begin/end, first/last, up/down, min/max,
next/previous, open/close, show/hide, suspend/resume, etc.
```
Reduce complexity by symmetry.
### 21. Abbreviations in names should be avoided.
```c++
compute_average();   // NOT: comp_avg();
```
There are two types of words to consider. First are the common words listed in a language dictionary. These must never be abbreviated. Never write:
```
cmd   instead of   command
cp    instead of   copy
pt    instead of   point
comp  instead of   compute
init  instead of   initialize
etc.
```
Then there are domain specific phrases that are more naturally known through their abbreviations/acronym. These phrases should be kept abbreviated. Never write:
```
HypertextMarkupLanguage  instead of   html
CentralProcessingUnit    instead of   cpu
PriceEarningRatio        instead of   pe
etc.
```

### 22. Naming pointers specifically should be avoided.
```c++
Line* line; // NOT: Line* p_line;
            // NOT: LIne* line_ptr;
```
Many variables in a C/C++ environment are pointers, so a convention like this is almost impossible to follow. Also objects in C++ are often oblique types where the specific implementation should be ignored by the programmer. Only when the actual type of an object is of special significance, the name should emphasize the type.

### 23. Negated boolean variable names must be avoided.
```c++
bool is_error; // NOT: is_no_error
bool is_found; // NOT: is_not_found
```
The problem arises when such a name is used in conjunction with the logical negation operator as this results in a double negative. It is not immediately apparent what !isNotFound means.
### 24. Enum should always be enum classes without dedeclaring the name.
```c++
enum class Color
{
  Red,
  Green,
  Blue
};
```
Enums should always be enum classes. When this is the case it will avoid name collisions.

```c++
enum class Enumeration
{
    Val1,
    Val2,
    Val3 = 100,
    Val4 // = 101
};
```

### 25. Exception classes should be suffixed with Exception.
```c++
class AccessException
{
  :
}
```
Exception classes are really not part of the main design of the program, and naming them like this makes them stand out relative to the other classes.

### 26. Functions (methods returning something) should be named after what they return and procedures (void methods) after what they do.
Increase readability. Makes it clear what the unit should do and especially all the things it is not supposed to do. This again makes it easier to keep the code clean of side effects.
