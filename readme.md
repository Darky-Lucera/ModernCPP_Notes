# Modern C++

- [preprocessor directives](#preprocessor-directives)
- [Constants](#constants)
  - [nullptr_t and nullptr [C++11]](#nullptr_t-and-nullptr-C11)
  - [constexpr [C++11]](#constexpr-C11)
  - [constinit [C++20]](#constinit-C20)
  - [consteval [C++20]](#consteval-C20)
  - [std::is_constant_evaluated [C++20]](#stdis_constant_evaluated-C20)
- [Literals](#literals)
  - [Binary Literals [C++14]](#binary-literals-C14)
  - [Digit separators [C++14]](#digit-separators-C14)
  - [Standard literals](#standard-literals)
    - [Integer literals](#integer-literals)
    - [Floating point literals](#floating-point-literals)
    - [Character literals](#character-literals)
    - [String literals](#string-literals)
    - [Raw string literal](#raw-string-literal)
    - [Complex numbers literals](#complex-numbers-literals)
    - [Chrono literals](#chrono-literals)
  - [User-defined literals [C++11]](#user-defined-literals-C11)
- [Initialization](#initialization)
  - [Initializer lists [C++11]](#Initializer-lists-C11)
  - [Uniform initialization [C++11]](#Uniform-initialization-C11)
  - [Designated Initializers [C++20]](#Designated-Initializers-C20)
- [Type inference](#type-inference)
  - [auto [C++11]](#auto-C11)
  - [decltype(...) [C++11]](#decltype-C11)
  - [decltype(auto) [C++14]](#decltypeauto-C14)
  - [Tail type [C++11]](#tail-type-C11)
- [Control flow enhancements](#control-flow-enhancements)
  - [Range-based for loop [C++11]](#range-based-for-loop-C11)
  - [Range-based for loop with initializer [C++20]](#range-based-for-loop-with-initializer-C20)
  - [if with initializer [C++17]](#if-with-initializer-C17)
  - [if constexpr [C++17]](#if-constexpr-C17)
  - [if consteval [C++23]](#if-consteval-C23)
  - [switch with initializer [C++17]](#switch-with-initializer-C17)
- [Lambdas](#lambdas)
  - [Lambda Expressions [C++11]](#Lambda-Expressions-C11)
  - [Default parameters [C++14]](#Default-parameters-C14)
  - [Template parameters [C++14]](#Template-parameters-C14)
  - [Generalised capture [C++14]](#Generalised-capture-C14)
  - [Returning a lambda from a function [C++14]](#Returning-a-lambda-from-a-function-C14)
  - [Capture of this [C++17]](#Capture-of-this-C17)
  - [Constexpr Lambda Expressions [C++17]](#Constexpr-Lambda-Expressions-C17)
  - [Templatized lambdas [C++20]](#Templatized-lambdas-C20)
- [Other interesting parts](#other-interesting-parts)
  - [R-Values [C++11]](#R-Values-C11)
  - [Static assertions [C++11]](#Static-assertions-C11)
  - [Allow sizeof to work on members of classes without an explicit object [C++11]](#Allow-sizeof-to-work-on-members-of-classes-without-an-explicit-object-C11)
  - [Control and query object alignment [C++11]](#Control-and-query-object-alignment-C11)
  - [Thread Local Storage (TLS) [C++11]](#Thread-Local-Storage-TLS-C11)
  - [Attributes [C++11]](#Attributes-c11)
- [Object Oriented](#object-oriented)
  - [Initializing class member variables [C++11]](#initializing-class-member-variables-C11)
  - [Initializing static class member variables [C++17]](#initializing-static-class-member-variables-C17)
  - [Delegate constructor [C++11]](#delegate-constructor-C11)
  - [Inherit constructors [C++11]](#inherit-constructors-C11)
  - [Move constructors [C++11]](#Move-constructors-C11)
  - [Explicit conversion operators [C++11]](#Explicit-conversion-operators-C11)
  - [Explicit virtual function override [C++11]](#explicit-virtual-function-override-C11)
  - [final [C++11]](#final-C11)
  - [Operator spaceship <=> (3 way comparator) [C++20]](#operator-spaceship--3-way-comparator-C20)
  - [Generate default function [C++11]](#generate-default-function-C11)
  - [Explicit delete default function [C++11]](#explicit-delete-default-function-C11)
  - [Ref qualifiers [C++11]](#Ref-qualifiers-c11)
  - [Explicit object member functions [C++23]](#Explicit-object-member-functions-c23)
  - [Strongly typed enumerations [C++11]](#strongly-typed-enumerations-C11)
  - [Multidimensional subscript operator [C++23]](#Multidimensional-subscript-operator-C23)
- [Templates](#templates)
  - [Extern templates [C++11]](#Extern-templates-C11)
  - [Right angle bracket [C++11]](#Right-angle-bracket-C11)
  - [Template aliases [C++11]](#Template-aliases-C11)
  - [Variadic template [C++11]](#Variadic-template-C11)
- [Deprecated Features](#deprecated-features)

# Preprocessor directives

Since the additions in this section are very few, I have decided to add most of the directives in this section.

[**Conditionally compile**](https://en.cppreference.com/w/cpp/preprocessor/conditional):

```cpp
#if     expression
#ifdef  id      // #if  defined(id)
#ifndef id      // #if !defined(id)
#elif   expression
#else
#endif

// New
#elifdef    id  // #elif  defined(id)   [C++23]
#elifndef   id  // #elif !defined(id)   [C++23]
```

[**Macros**](https://en.cppreference.com/w/cpp/preprocessor/replace):

```cpp
#define id              [expressions]
#define id(params)      [expressions]
#define id(params, ...) [expressions] // [C++11] We can use __VA_OPT__() and __VA_ARGS__ to manage the ellipsis
#define id(...)         [expressions] // [C++11] We can use __VA_OPT__() and __VA_ARGS__ to manage the ellipsis
#undef  id

// __VA_ARGS__ is not always available before C++11.
// __VA_OPT__ is available since C++20.

#define LOG(msg, ...) printf("[" __FILE__ ":%s:%d] " msg, __func__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
```

**Operators**

- Operator Stringification **#**: Converts a token to a string.
- Operator Concatenation  **##**: Concatenates two strings.

```cpp
#define kStringify(x)    #x
#define kConcat(x, y)    x##y

int result = kConcat(num, 1) + kConcat(num, 2);

printf("%s = %d\n", kStringify(result), result);
```

[**Include**](https://en.cppreference.com/w/cpp/preprocessor/include):

```cpp
#include <header>           // global
#include "header"           // local
#__has_include(<header>)    // global [C++17]
#__has_include("header")    // local  [C++17]

#if defined(__has_include)
  #if __has_include (<stdatomic.h>)
    #include <stdatomic.h>
  #endif
#endif
```

[**Diagnostic directives**](https://en.cppreference.com/w/cpp/preprocessor/error):

```cpp
#warning    "message"   //                      [C++23]
#error      "message"   //                      [C++98]
```

[**Implementation defined behavior control**](https://en.cppreference.com/w/cpp/preprocessor/impl):

```cpp
#pragma name                // Usually name is compiler specific
_Pragma(string)             // Allows using pragma inside macros [C++11]

#pragma once

#pragma pack(value)         // Sets the current alignment to value
#pragma pack()              // Sets the current alignment to the default value
#pragma pack(push)          // Stores the current alignment value
#pragma pack(push, value)   // Stores the current alignment and sets it to 'value'
#pragma pack(pop)           // Restores the last alignment value
```

[**Predefined macros**](https://en.cppreference.com/w/cpp/preprocessor/replace#Predefined_macros):

Sadly, not all compilers define them. So we cannot trust them.

[List of some of non-standard predefined macros](https://sourceforge.net/p/predef/wiki/Home/)
[C++ Macros](https://en.cppreference.com/w/cpp/symbol_index/macro)

```
__cplusplus
__STDC_HOSTED__                     [C++11]
__LINE__
__FILE__
__DATE__
__TIME__
__func__                            Current function name. GCC, Clang, MSVC 2012+, Intel
__FUNCTION__                        Current function name. Not standard
__FUNCDNAME__                       Current function name. Not standard
__PRETTY_FUNCTION__                 Current function name. Not standard [GCC]
__FUNCSIG__                         Current function name. Not standard [MSVC]
__STDCPP_DEFAULT_NEW_ALIGNMENT__    [C++17]
__STDCPP_­BFLOAT16_T__               [C++23]
__STDCPP_­FLOAT16_T__                [C++23]
__STDCPP_FLOAT32_T__                [C++23]
__STDCPP_FLOAT64_T__                [C++23]
__STDCPP_FLOAT128_T__               [C++23]
__STDC__
__STDC_VERSION__                    [C++11]
__STDC_ISO_10646__                  [C++11]
__STDC_MB_MIGHT_NEQ_WC__            [C++11]
__STDCPP_THREADS__                  [C++11]
__STDCPP_STRICT_POINTER_SAFETY__    [C++11]
```

# Constants

## nullptr_t and nullptr [C++11]

- The type of nullptr is nullptr_t.
- It replaces the macro ```NULL```, adding semantic meaning.
- ```nullptr``` is not ```0, 0x0, ((void *) 0), ...```.

**Benefits**:

- Improves code readability and maintainability.

Example:

```cpp
void foo(char *);
void foo(int);

foo(NULL);      // Which function is called?
foo(nullptr);   // foo(char *) is called
```

## constexpr [C++11]

- ```constexpr``` **values** are evaluated only at compile time and cannot be modified.
- ```constexpr``` **functions** can be executed at compile or at execution time.
- C++11 allows only non-complex computations.
- Later versions (C++14 and beyond) introduced more freedom, allowing for:
  - If statements.
  - Multiple returns.
  - Loops.
  - Comma separated expressions.
  - Exceptions.
  - Access static members.
- C++20 allows use constexpr in constructors, destructors, virtual functions and lambdas.

**Benefits**:

- Improves performance by pre-computing values.
- Enables compile-time checks and optimizations.
- Facilitates metaprogramming techniques.

Example:

```cpp
constexpr float pi = 3.14f;         // constexpr value

constexpr double earthGravity = 9.8;
constexpr double moonGravitay = earthGravity / 6.0; // We cannot do this with const in c++03

// C++11 allows only non-complex computations
constexpr int add(int a, int b) {
    return a + b;
}

// Can be also be used in classes
struct S {
    constexpr void foo(int) {};        // Can be executed at compile or execution time
              void foo(int) {};        // Error: Collides with prior function
              void foo(int) const {};  // Ok: constexpr does not imply const
};

// C++14 adds common syntax such as if statements, multiple returns, loops, etc.
constexpr int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int v = 5;
constexpr int resultA = factorial(add(2, 3));   // Solved at compile time
constexpr int resultB = add(v, v);              // Error (because v)
const int resultC = add(v, v);                  // Solved at execution time (because v)
int resultD = add(1, 1);                        // Solved at compile time
int arrayA[resultA];                            // OK
int arrayB[resultB];                            // Error
int arrayC[resultC];                            // Error

// C++17 allows constexpr lambda functions (see #lambdas)
auto identity = [](int n) constexpr { return n; };

// C++20 allows constexpr virtual functions
struct A {
    virtual int foo() const = 0;
};

struct B : public A {
  constexpr virtual int foo() const { return 42; }
};
```

## constinit [C++20]

- ```constinit``` guarantees that a variable with static storage duration is initialized at compile time.
- The variable is still mutable.
- It can be used in global objects or objects declared with static or extern.
- Solves the static initialization order fiasco.

**Benefits**:

- Improves code safety by avoiding undefined behavior.
- Facilitates static analysis and optimizations.

Example:

```cpp
constexpr int valueCE = 3;
constinit int valueCI = valueCE;
constinit int error   = valueCI;  // Error: valueCI is not usable in constant expressions

void foo() {
    valueCE++;  // Error: valueCE is constexpr
    valueCI++;  // Ok
}
```

## consteval [C++20]

- Generates an inmediate function.
- Cannot be executed at runtime.

**Benefits**:

- Improves performance by pre-computing values.
- Enables compile-time checks and optimizations.

Example:

```cpp
consteval int add(int a, int b) {
    return a + b;
}

constinit int ci = add(2,  3);
constexpr int ce = add(2,  3);
const int c      = add(ce, 3);
int i            = add(c,  3);
//--
int e1 = add(ce, ce);
int e2 = add(ci, 1);    // Error: The value of ci is not known at compile time
int e3 = add(i,  1);    // Error: The value of i is not known at compile time
```

## std::is_constant_evaluated [C++20]

Detects whether the function call occurs within a constant-evaluated context.

Example:

```cpp
constexpr double
power(double b, int x)
{
    if (std::is_constant_evaluated()) {
        //
    }
    else {
         return std::pow(b, double(x));
    }
}
```

# Literals

## Binary Literals [C++14]

- 0b or 0B followed by one or more binary digits (0, 1).

Example:

```cpp
int             a = 0b0001;
unsigned int    b = 0B0010;
```

## Digit separators [C++14]

- The single-quote character ' may be used arbitrarily as a digit separator in numeric literals.
- Useful to make numbers more 'human readable'.

Example:

```cpp
int     bin = 0b0000'0011'1110'1000;
int     oct = 0'17'50;
int     dec = 1'23'456'7890;
int     hex = 0x03'E8;
float   flt = 0.1234'5678f;
double  dbl = 0.12'34'56'78f;
```

## Standard literals

### Integer literals

```
0b / 0B         Binary                          0b1001 / 0B1001     [C++14]
0               Octal                           0123
0x / 0X         Hexadecimal                     0x123 / 0X123
u / U           unsigned                        123u / 123U
l / L           long                            123l / 123L
lu / ul         unsigned long                   123ul / 123lu
LU / UL         unsigned long                   123UL / 123LU
ll / LL         long long                       123ll / 123LL
llu / ull       unsigned long long              123ull / 123llu     [C++11] (officially)
LLU / ULL       unsigned long long              123ULL / 123LLU     [C++11] (officially)
z / Z           signed size_t                   123z / 123Z         [C++23]
uz / UZ         size_t                          123uz / 123UZ       [C++23]
```

### Floating point literals

```
f / F           float                           2f, 2.0f
l / L           long double                     2.0l / 2.0L
e / E           Exponent                        2e2 / 2E2 == 2 * 10^2 == 200
0x / 0X         Hexadecimal float
p / P           Hexadedimal exponent            0x2.1p0 = (2 + 1/16) * 2^0 = 2.0625
```

**Hexadecimal float regex:**<br>

```
[+-]? 0 [xX] ( [0-9a-f]* . [0-9a-f]+ | [0-9a-f]+ .? ) [pP] [+-]? [0-9]+ [flL]?

0x2p1f    = 2 * 2^1 = 4.0f
-0x2.1p0  = (2 + 1/16) * 2^0 = -2.0625
0x1.0p10L = 1024.0L
0x0.8p-1  = 0.25
```

### Character literals

```
L               wchar_t                         L'a'
u8              char8_t  (UTF-8)                u8'a'           Range [0x0, 0x7F]       [C++17]
u               char16_t (UTF-16)               u'a'            Range [0x0, 0xFFFF]     [C++11]
U               char32_t (UTF-32)               U'a'            Range [0x0, 0xFFFFFFFF] [C++11]
```

_Note: Does not work pretty well on some compilers._

### String literals

Example:

```cpp
using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

std::string         str0 = "str"s;      // C++14. Defined in std::literals::string_literals
std::string_view    str1 = "str"sv;     // C++17. Defined in std::literals::string_view_literals

wchar_t             str2 = L'a';
std::wstring        str3 = L"str";

char8_t             str4 = u8'a';       // C++20 (UTF-8)
std::u8string       str5 = u8"str";     // C++20 (UTF-8)

char16_t            str6 = u'a';        // C++11 (UTF-16)
std::u16string      str7 = u"str";      // C++11 (UTF-16)

char32_t            str8 = U'a';        // C++11 (UTF-32)
std::u32string      str9 = U"str";      // C++11 (UTF-32)
```

### Raw string literal

```R"delimiter( raw characters )delimiter"```

- Delimiter can be any character except the single quote and double quote.
- Allows for flexibility in escaping nested quotes within the raw string.

Example:

```cpp
const char *raw = R"(
<html>
    <body>
    </body>
</html>
)";
```

### Complex numbers literals

Defined in inline namespace ```std::literals::complex_literals``` [C++14]

A ```std::complex``` literal representing pure imaginary number

Example:

```cpp
if          std::complex<float>              5if
i           std::complex<double>             5i
il          std::complex<long double>        5il
```

### Chrono literals

Defined in inline namespace ```std::literals::chrono_literals``` [C++14]

```
h           A std::chrono::duration literal representing hours
min         A std::chrono::duration literal representing minutes
s           A std::chrono::duration literal representing seconds
ms          A std::chrono::duration literal representing milliseconds
us          A std::chrono::duration literal representing microseconds
ns          A std::chrono::duration literal representing nanoseconds

y           A std::chrono::year literal representing a particular year [C++20]
d           A std::chrono::day literal representing a day of a month [C++20]
```

Example:

```cpp
using namespace std::literals::chrono_literals;

auto timeout = 5min + 30s;
```

## User-defined literals [C++11]

Allows the user to define his own suffixes and define conversion rules.

Rules:

- All the user defined literals must begin always with the underscore '_'.
- The system libraries must not use underscores to define its own literals.
- Only the following parameter lists are allowed on literal operators:

```cpp
// Numeric
( unsigned long long int )
( long double )

// Characters
( char )
( wchar_t )
( char8_t )         // C++20
( char16_t )
( char32_t )

// Strings
( const char * )
( const char * ,     std::size_t )
( const wchar_t * ,  std::size_t )
( const char8_t * ,  std::size_t )      // C++20
( const char16_t * , std::size_t )
( const char32_t * , std::size_t )
```

Example:

```cpp
constexpr float
operator "" _deg ( long double deg ) {
    return float(deg * 3.141592 / 180.0);
}

constexpr float
operator "" _deg ( unsigned long long int deg ) {
    return float(deg * 3.141592 / 180.0);
}

sprite.Rotate(180_deg);
```

# Initialization

## Initializer lists [C++11]

- ```std::initializer_list<T>``` is a standard library container that represents a sequence of elements. It's primarily used for initializing standard library containers.
- It allows you to initialize these containers with a list of elements in a convenient and concise way.
- Cannot be directly modified or accessed by index.

**Benefits**:

- Improves code readability and conciseness.
- Can be more efficient than manual element addition.
- Enables features like uniform initialization.
- Copying an initializer_list doesn't copy the actual elements, only references them.

Example:

```cpp
#include <initializer_list>

std::initializer_list<int> values = {1, 2, 3, 4, 5};
std::vector<float>         vec    = {1, 2.0, 3.0f};   // Automatic conversion.

void printValues(std::initializer_list<int> values) {
    for (auto it = values.begin(); it != values.end(); ++it) {
        std::cout << *it << " ";
    }
}
```

## Uniform initialization [C++11]

- Provides a consistent and concise syntax for initializing objects in various contexts.
- It allows you to initialize objects using braces {} regardless of the type of object being initialized, whether it's a fundamental type, user-defined type, or an aggregate type.
- Uniform initialization prevents narrowing conversions. The type in braces must be the same of the variable.

Example:

```cpp
int     x     { 42 };
double  y     { 3.14 };
int     z     { 3.14 }; // Error: narrowing conversion
int     w     { };      // 0
int     *p    { };      // nullptr
int     arr[] { 1, 2, 3, 4 };

struct Struct {
    std::string name;
    int data;
};

Struct obj1 { "Carlos", 10 };

std::vector<float> vec {1, 2, 3};
```

## Designated Initializers [C++20]

- This is a C99 standard feature that was not included in C++.
- Prior to C++20, aggregate initialization relied on the order of members in the class or struct definition. However, this could lead to errors if the order changed or if some members were added or removed.

Example:

```cpp
struct Point {
    int x;
    int y;
    int z;
};

Point p1 = { .x = 10, .y = 20, .z = 30 };
Point p2 = { .x = 10,          .z = 30 };   // .y = {}
Point p3 = { .z = 30, .x = 10 };            // Error: Order is important
```

# Type inference

Type inference helps reduce boilerplate code by letting the compiler automatically deduce the type of a variable or function return value from its context.

## auto keyword [C++11]

- Replaces explicit type declarations, especially for long or complex types.
- Very useful with long type names.
- Improves code readability and reduces verbosity.

```cpp
auto itr = std::find(begin(vec), end(vec), 4);

// instead of

std::vector<int>::iterator itr = std::find(begin(vec), end(vec), 4);

// C++14 allows also deduce return type but no function arguments
template<typename T, typename U>
auto add(A a, B b) {
    return x + y;
}

// C++20 allows use auto as function arguments
auto
add(auto a, auto b) {
    return (a + b);
}
```

## decltype(...) [C++11]

```cpp
auto          a = 2.3f;
auto          b = 1;
decltype(a+b) c;

if (std::is_same<decltype(c), int>::value)
    std::cout << "type c == int" << std::endl;
if (std::is_same<decltype(c), float>::value)
    std::cout << "type c == float" << std::endl
```

## decltype(auto) [C++14]

Deduces types keeping their references and cv-qualifiers, while auto will not.

```cpp
int             y  = 0;
const int &     y2 = y;

const auto      y3 = y2;    // const int
decltype(auto)  y4 = y2;    // const int &
```

## Tail type [C++11]

- In template functions, specifies the return type based on the operations performed.
- Enables template functions to return types based on their arguments and operations.

```cpp
template<typename A, typename B>
auto add(A a, B b) -> decltype(a + b) {
    return a + b;
}
```

# Control flow enhancements

## Range-based for loop [C++11]

```cpp
// std::vector vec;
for(auto &value : vec) {
    value += 3;
}
```

## Range-based for loop with initializer [C++20]

```cpp
for(size_t index = 0; const auto &value : vec) {
    printf("- %d: %s\n", index++, value.c_str());
}
```

## if with initializer [C++17]

Reduces variable scope.

```cpp
if(auto it = std::find(begin(vec), end(vec), 4); it != end(vec)) {
    *it = -4;
}
```

## if constexpr [C++17]

- Evaluates at compile time if all conditions and branches are constexpr.
- Used for constant expressions within templates or compile-time calculations.
- Suitable for conditions based on known values at compile time.
- Can be used for template specialization based on constant checks.
- Limited by the constexpr restrictions.

```cpp
template<typename T>
auto getValue(T t) {
    if constexpr (std::is_pointer_v<T>)
        return *t;
    else
        return t;
}
```

## if consteval [C++23]

Evaluates to true if we are at compile time.
Notice that braces are mandatory: ```if consteval { } else { }```

```cpp
// Used by ipow
consteval uint64_t ipow_ct(uint64_t base, uint8_t exp) {
    if (base == 0)
        return base;

    uint64_t res{1};
    while (exp) {
        if (exp & 1) res *= base;
        exp /= 2;
        base *= base;
    }
    return res;
}

constexpr uint64_t ipow(uint64_t base, uint8_t exp) {
    if consteval { // use a compile-time friendly algorithm
        return ipow_ct(base, exp);
    }

    // use runtime evaluation
    return std::pow(base, exp);
}
```

**Note**: The alternative for C++20 if using the function [std::is_constant_evaluated()](https://en.cppreference.com/w/cpp/types/is_constant_evaluated)

## switch with initializer [C++17]

Reduces variable scope.

```cpp
switch(auto status = GetStatus(); status) {
    case Init:
        break;

    case Run:
        break;
}
```

# Lambdas

## Lambda Expressions [C++11]

Lambda expressions provide a concise way to create anonymous functions.

**Structure**:

```cpp
[captureList](parameters) mutable -> returnType { body }
```

**Example**:

```cpp
auto lambda = [foo](int a, int b) -> decltype(a + b) { return foo + a + b; };

// The lambda code generated by the compiler would be something like this:
class __RandomName {
  public:
    __RandomName(int & _ex) : ex{_ex} { }

    inline int operator()(int a, int b) const { return ex + a + b; }

  private:
    int ex;
};
```

- **captureList**: is optional.
  - **[&]**: capture **all** by reference.
  - **[=]**: capture **all** by value _(default)_.
  - **[&foo, bar]**: Capture ```foo``` by reference and ```bar``` by value.
- **parameters**: is optional.
- **mutable**: is optional.<br/>By default, the generated operator() is const, so if we want to be able to modify the captured variables we need to add ```mutable``` after parameters.<br/>

```cpp
auto lambda = [foo](int a, int b) mutable { return ++foo + a + b; }; // Increment local lambda variable foo on every call
```

- **returnType**: is optional and can be deduced.
- **body**: is the body of the function to execute.

**_Note_**: _Lambda type must be auto._

## Default parameters [C++14]

In C++14, lambdas can take default values for parameters, like any other function:

```cpp
auto lambda = [](int a, int b=1) -> int { return a + b; };
```

## Template parameters [C++14]

In C++14, lambda parameters can accept generic types:

```cpp
auto lambda = [](auto a, auto b=1) -> int { return a + b; };
```

## Generalised capture [C++14]

In C++14, we can initialise captured values:

```cpp
auto lambda = [foo=0](auto a, auto b=1) -> int { return ++foo + a + b; };
```

**_Note_**: _I find it especially useful to capture ```std::shared_from_this()``` / ```std::enable_shared_from_this<>```._

## Returning a lambda from a function [C++14]

Since the lambda type must be auto, in C++11 we cannot return a lambda from a function. This is fixed in C++14 as functions are allowed to return auto following the deduction guidelines.

## Capture of this [C++17]

Prior to C++17, capturing ```this``` by value in a lambda, inside a member function, was not allowed. C++17 relaxed this restriction, allowing lambdas to capture a copy of this.

```cpp
class Cls {
    public:
        Cls(int v) : value(v) {}
        auto getLambda() const { return [this]() { return value * value; }; }
    protected:
        int value;
};

std::function<int()> func;

{
    Cls cls { 10 };
    func = cls.getLambda();
}

printf("%d\n", func());   // 100
```

## Constexpr Lambda Expressions [C++17]

C++17 extended the capabilities of ```constexpr``` functions to include lambda expressions, allowing them to be evaluated at compile-time if their arguments are constexpr and their bodies are constexpr-evaluable.

```cpp
constexpr auto lambda = [](auto a, auto b) { return a + b; };
static_assert(lambda(2, 1) == 3);
```

## Templatized lambdas [C++20]

This makes it easier to access the template parameter type.

```cpp
//-------------------------------------
template<typename... Args>
int add(Args &&...args) {
    auto lambda = [...args = std::forward<Args>(args)]() {
        return (args + ...);
    };

    return lambda();
}

//-------------------------------------
template <typename T>
auto Pow = [](T base, T exponent) {
    if constexpr (std::is_integral_v<T>) {
        return ipow(base, exponent);    // Optimized for integer types
    }
    else if constexpr (std::is_floating_point_v<T>) {
        return fpow(base, exponent);    // Optimized for float and double
    }
    else {
        return std::pow(base, exponent); // Default (maybe imaginary numbers?)
    }
};
```

# Other interesting parts

## R-Values [C++11]

- An **rvalue** reference is a special type of reference that can bind to **temporary objects**.
- Rvalue references are denoted by the double ampersand (**&&**).
- They allow you to identify and distinguish temporary objects from regular ones.

```cpp
int a = 3;
int b = 4;
int &&rvalue = a + b;
```

## Static assertions [C++11]

Before C++11, there were two ways to check assertions, macro assert in the header ```<assert.h>``` / ```<cassert>```, and the preprocessor word ```#error``` but they didn't work well with templates.
The checks happened either too early (before templates were set up) or too late (after the program was running).

C++11 introduces the keyword ```static_assert``` to solve this issues.

```cpp
static_assert(sizeof(void *) == sizeof(uint32_t), "We store pointers in uint32_t fields")

template<class Integral>
Integral foo(Integral x) {
    static_assert(std::is_integral<Integral>::value, "foo() parameter must be an integral type.");
}
```

## Allow sizeof to work on members of classes without an explicit object [C++11]

```cpp
struct A {
    ...
    Class   cls;
    ...
};

ptr += sizeof(A::cls);
```

## Control and query object alignment [C++11]

C++11 allows variable alignment to be queried ```alignof``` and controlled ```alignas```.

The ```alignof``` operator takes the type and returns the power of 2 byte boundary on which the type instances must be allocated.
For references, it returns the referenced type's alignment.
For arrays, it returns the element type's alignment.

The ```alignas``` specifier controls the memory alignment for a variable.
```alignas(T)``` is shorthand for ```alignas(alignof(T))```.

```cpp
alignas(float) unsigned char matrix4x4[sizeof(float) * 16]
```

## Thread Local Storage (TLS) [C++11]

Allows each thread to have its own separate instance of a variable.<br/>
It also works for **static** variables defined inside a function. Each thread will have its own instance of the **per thread global** variable.

- **Lifetime**: The lifetime of a TLS variable begins when it is initialized and ends when the thread terminates.
- **Visibility**: TLS variables have visibility at the thread level.
- **Scope**: TLS variables have scope depending on where they are declared.

```cpp
void log(const char *name) {
    thread_local int count{};

    printf("%s: %d\n", name, count++);
}

thread_local int inc {};

void
doCount(const char *name, int count, int &ref) {
    for (int i=0; i<count; ++i) {
        ++inc;  // Increases its local copy
        log(name);
    }

    ref = inc;  // inc is local copy
}

int
main() {
    int     a{}, b{};

    std::thread ta([&a] { doCount("ta", 10, a); }); // std::thread was introduced in C++11
    std::thread tb([&b] { doCount("tb", 20, b); });

    tb.join();
    ta.join();

    printf("a=%d, b=%d, inc=%d\n", a, b, inc);  // a=10, b=20, inc=0

    return 0;
}
```

## Attributes [C++11]

Provide a unified standard syntax for implementation-defined language extensions. Before this feature, each compiler has its own way to do it:

- GNU/Clang: __attribute__((...))
- Microsoft: __declspec(...)
- Borland: __property
- Different compilers: __builtin_XXX

The new standar way is: ```[[attribute, attribute...]]```.

These are the standard attributes:

```
- [[noreturn]]              [C++11] Indicates that the function does not return.
- [[carries_dependency]]    [C++11] Indicates that dependency chain in release-consume std::memory_order propagates in and out of the function.
- [[deprecated]]            [C++14] Indicates that the use of the name or entity declared with this attribute is allowed, but discouraged for some reason.
  [[deprecated("reason")]]  [C++14]
- [[fallthrough]]           [C++17] Indicates that the fall through from the previous case label (switch statement) is intentional and should not be diagnosed by a compiler that warns on fall-through.
- [[nodiscard]]             [C++17] Encourages the compiler to issue a warning if the return value is discarded.
  [[nodiscard("reason")]]   [C++20]
- [[maybe_unused]]          [C++17] Suppresses compiler warnings on unused entities, if any.
- [[likely]]                [C++20]
- [[unlikely]]              [C++20] Indicates that the compiler should optimize for the case where a path of execution through a statement is more or less likely than any other path of execution.
- [[no_unique_address]]     [C++20] Indicates that a non-static data member need not have an address distinct from all other non-static data members of its class.
- [[assume(expression)]]    [C++23] Specifies that the expression will always evaluate to true at a given point.
```

Each compiler/library can create its own attributes inside a namespace:

- **Microsoft**: [[msvc::attribute]]
- **Guidelines Support Library**: [[gls::attribute]]
- **GNU**: [[gnu::attribute]]
- **Clang**: [[clang::attribute]]

Since C++17 we can use ```[using namespace: atribute, attribute, ...]```.

# Object Oriented

## Initializing class member variables [C++11]

```cpp
struct A {
    int value = 0;
};
```

## Initializing static class member variables [C++17]

```cpp
struct A {
    static inline int value = 0;
};

// prior to C++17
struct A {
    static int value;
};

int A::value = 0;
```

## Delegate constructor [C++11]

```cpp
struct A {
    A() : A(-1) {}
    A(int v) : value(v) {}

    int value;
};
```

## Inherit constructors [C++11]

```cpp
struct A {
    A() : A(-1) {}
    A(int v) : value(v) {}

    int value = 0;
};

struct B : public A {
    using A::A;
};

B b1;
B b2(123);
```

## Move constructors [C++11]

- A move constructor is a special type of constructor that allows the efficient transfer of resources (like memory ownership) from a temporary object to another object.
- It's invoked automatically when you initialize an object with an rvalue.
- Move constructors are typically used to avoid unnecessary copies of objects, improving performance.

```cpp
class Cls {
  public:
    Cls()                 { ptr = new uint8_t; *ptr = 0;          } // Creates and initializes a pointer
    Cls(const Cls &other) { ptr = new uint8_t; *ptr = *other.ptr; } // Creates a pointer and copies the values of other object's pointer
    Cls(Cls &&other)      { std::swap(ptr, other.ptr);            } // Steals the other object's pointer because it's temporary and will be destroyed
    ~Cls()                { if (ptr != nullptr) delete ptr;       } // Destroys the pointer

  protected:
        uint8_t *ptr = nullptr;
};
```

## Explicit conversion operators [C++11]

When you declare a conversion operator with the explicit keyword, it prevents the compiler from performing implicit conversions using that operator.

```cpp
struct Bool {
    explicit Bool(bool v) : value(v) {}

    explicit operator bool() const { return value; }
    explicit operator std::string() const { return value ? "true" : "false"; }

    bool value {};
};

Bool    b1 { true };    // Ok
Bool    b2 = { true };  // Error: constructor is explicit
Bool    b3 = true;      // Error: constructor is explicit

if (b1) {
    printf("Ok!\n");
}

// Error: operator bool is explicit. No automatic conversion to bool, that is 0 or 1, and then automatic conversion to int.
if (b1 < 123) {
    printf("Noooo!\n");
}

std::string str = b1;   // Error: operator std::string() is explicit
std::string str = static_cast<std::string>(b1); // explicit cast is alowed
```

## Explicit virtual function override [C++11]

Reduces errors when inherit from other classes.

```cpp
struct A {
    virtual void foo()          { printf("A::foo\n"); }
    virtual void bar()          { printf("A::bar\n"); }
};

struct B : public A {
    void foo(int)               { printf("B::foo\n"); }     // Does not override A::foo (maybe an error)
    void foo() const            { printf("B::foo\n"); }     // Does not override A::foo (maybe an error)
    void bar() const override   { printf("B::bar\n"); }     // Error (original bar is not const)
    void bar() override         { printf("B::bar\n"); }     // Ok
};

A *a = new B;
a->foo();   // A::foo
a->bar();   // B::bar
```

## final [C++11]

```cpp
struct A final {
};

// Error cannot inherit from A
struct B : public A {
};

//--

struct A {
    virtual void foo();
};

struct B : public A {
    virtual void foo() final;
};

struct C : public B {
    virtual void foo(); // error B::foo is final
};
```

## Operator spaceship <=> (3 way comparator) [C++20]

The return value could be one of:

- ```std::strong_ordering```:  f(a) must be equal to f(b).      Only one of (a < b), (a == b) or (a > b) must be true.
- ```std::weak_ordering```:    f(a) may be different from f(b). Only one of (a < b), (a == b) or (a > b) must be true.
- ```std::partial_ordering```: f(a) may be different from f(b). (a < b), (a == b) and (a > b) may all be false
- ```int, ...```

```cpp
#include <compare>

struct Point {
  float x, y;

  constexpr auto operator <=>(const Point &rhs) const {
        if(x < rhs.x) return -1;
        if(x > rhs.x) return  1;
        if(y < rhs.y) return -1;
        if(y > rhs.y) return  1;
        return 0;
  };
};
```

## Generate default function [C++11]

```cpp
struct A {
        A()                     = default;
        A(const A &)            = default;
        A(A &&)                 = default;
        ~A()                    = default;

    A & operator = (const A &)  = default;
    A & operator = (A &&)       = default;

    auto operator <=>(const A &rhs) const = default; // C++20
    bool operator == (const A &rhs) const = default; // C++20
    bool operator != (const A &rhs) const = default; // C++20
    bool operator <  (const A &rhs) const = default; // C++20: default is delete
    bool operator <= (const A &rhs) const = default; // C++20: default is delete
    bool operator >  (const A &rhs) const = default; // C++20: default is delete
    bool operator >= (const A &rhs) const = default; // C++20: default is delete
};
```

## Explicit delete default function [C++11]

```cpp
struct A {
        A()                     = delete;
        A(const A &)            = delete;
        A(A &&)                 = delete;
        ~A()                    = delete;

    A & operator = (const A &)  = delete;
    A & operator = (A &&)       = delete;

    // Won't need anymore this old idiom
    A & operator = (const A &); // Not implemented anywere (get a compiler error if someone tries to use it)
};
```

## Ref qualifiers [C++11]

With this feature we can indicate when we want to use a class function for l-values or r-values.

```cpp
struct Cls {
    void foo() &        { printf("lvalue\n");       }
    void foo() &&       { printf("rvalue\n");       }
    void foo() const &  { printf("const lvalue\n"); }
    void foo() const && { printf("const rvalue\n"); }
};

const Cls getCls() { return Cls(); }

int main() {
    Cls       cls;
    const Cls cCls;

    cls.foo();      // lvalue
    cCls.foo();     // rvalue

    Cls().foo();    // rvalue
    getCls().foo(); // const rvalue

    return 0;
}
```

## Explicit object member functions [C++23]

C++23 introduces clearer syntax for Ref qualifiers.

```cpp
struct Cls {
    void foo() &                    { printf("foo lvalue\n");       }   // C++11
    void foo() &&                   { printf("foo rvalue\n");       }   // C++11
    void foo() const &              { printf("foo const lvalue\n"); }   // C++11
    void foo() const &&             { printf("foo const rvalue\n"); }   // C++11

    void bar(this Cls &self)        { printf("bar lvalue\n");       }   // C++23
    void bar(this Cls &&self)       { printf("bar rvalue\n");       }   // C++23
    void bar(this const Cls &self)  { printf("bar const lvalue\n"); }   // C++23
    void bar(this const Cls &&self) { printf("bar const rvalue\n"); }   // C++23
};

const Cls getCls() { return Cls(); }

int main() {
    Cls       cls;
    const Cls cCls;

    cls.foo();      // lvalue
    cCls.foo();     // rvalue

    Cls().foo();    // rvalue
    getCls().foo(); // const rvalue

    //--

    cls.bar();      // lvalue
    cCls.bar();     // rvalue

    Cls().bar();    // rvalue
    getCls().bar(); // const rvalue

    return 0;
}
```

And since C++23 we can 'deduce this' using a template to simplify the code:

```cpp
struct Cls {
    // A lot of boilerplate
    std::string &       getName(this Cls &self)        { return mName; }                // C++23
    const std::string & getName(this const Cls &self)  { return mName; }                // C++23
    std::string &&      getName(this Cls &&self)       { return std::move(mName); }     // C++23

    // Better using 'deducing this'
    template <typename Self>
    auto && getName(this Self &&self)                   { return std::forward(mName); } // C++23

    std::string mName;
};
```

Another nice use of 'deduce this' is making recursive lambdas:

```cpp
// C++14 version
auto fibonacci14 = [](const auto &fibonacci, int n) -> long {
  return n < 2 ? n : fibonacci(fibonacci, n-1) + fibonacci(fibonacci, n-2);
};

// But it is a little bit ugly
auto a = fibonacci14(fibonacci14, 5);

//--

// C++23 version using deduce this
auto fibonacci23 = [](this auto &fibonacci, int n) -> long {
    return (n < 2) ? n : fibonacci(n-1) + fibonacci(n-2);
};

auto a = fibonacci23(5);
```

## Strongly typed enumerations [C++11]

```cpp
// Note: The type is optional
enum class Status : uint8_t {
    ON = 0,
    OFF,
};

Status s1 = ON; // Error
Status s2 = Status::ON; // Error
Status s3 = 0: // Error
```

# Multidimensional subscript operator [C++23]

```cpp
// Instead of having to use data[x][y][z]
// Now we can have multiple indexes
T &         operator[](size_t x, size_t y, size_t z)        { }
const T &   operator[](size_t x, size_t y, size_t z) const  { }

// and use it that way:
data[x, y, z] = 123;

auto value = data[x, y, z];
```

# Templates

## Extern templates [C++11]

- Allows the compiler not to instantiate the template in this translation unit. Will be instantiated in another unit.
- Reduces compile time.

```cpp
extern template class std::vector<Cls>;
```

## Right angle bracket [C++11]

Finally! We can close several templates at once without separating the '>' symbol.

```cpp
std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>> vec; // This is finally valid instead of
                                                                          // std::vector<std::vector<std::vector<std::vector<std::vector<int> > > > >
```

## Template aliases [C++11]

Before C++11 we could not typedef aliases. Now we can with the reserved word ```using``` that simplifies typedefs.

```cpp
// Using syntax is simpler than typedef syntax
typedef std::vector<int> vecInt;

using vecInt = std::vector<int>;

//-------------------------------------

template <typename A, typename B>
struct Template { ... };

// We could not do this in C++03
template <typename B>
using TemplateInt = Template<int, B>;
```

## Variadic template [C++11]

Allows you to create functions or classes that can take an arbitrary number of arguments of different types.

```cpp
template<typename... Values>                class tuple;    // takes zero or more arguments
template<typename Head, typename... Tail>   class tuple;    // takes one  or more arguments

//-------------------------------------
// Example: print
//-------------------------------------
template<typename T>
void print(T value) {
    std::cout << value << std::endl;
}

template<typename T, typename... Args>
void print(T first, Args... rest) {
    std::cout << first << std::endl;
    print(rest...); // Recursive call to print the rest of the arguments
}

//-------------------------------------
// Example: sum
//-------------------------------------
template<typename Head>
Head sum(Head value) {
    return value;
}

template<typename Head, typename ...Tail>
Head sum(Head head, Tail ...tail) {
  return head + sum(tail...);
}

auto res = sum(1, 2.61f, 3.42, true);   // int res = 8;
```

# Deprecated Features

- **String literal constants** [C++11]

```cpp
      char *str = "Hello";  // Deprecated
const char *str = "Hello";  // Ok
```

- **Unexpected handler** [C++11]<br>
```std::unexpected_handler```, ```std::set_unexpected()```, ```std::get_unexpected()``` and other related features are deprecated

- **std::auto_ptr** [C++11] (removed in C++17)<br>
Prefer ```std::unique_ptr```

- **register keyword** [C++11]

- **++ bool operator**

- **C casting**<br>
Use any of ```static_cast```, ```reinterpret_cast``` or ```const_cast```

- **Some C standar libraries**<br>

  **Empty C headers**

  - ```<ccomplex> / complex.h>``` (C++11) (deprecated in C++17) (removed in C++20)<br>
    Simply includes the header ```<complex>```
  - ```<ctgmath> / <tgmath.h>``` (C++11) (deprecated in C++17) (removed in C++20)<br>
    Simply includes the headers ```<complex>``` and ```<cmath>``` the overloads equivalent to the contents of the C header tgmath.h are already provided by those headers<br><br>

  **Meaningless C headers**

  - ```<ciso646>``` (removed in C++20)<br>
    Empty header. The macros that appear in iso646.h in C are keywords in C++
  - ```<cstdalign>``` (C++11) (deprecated in C++17) (removed in C++20)<br>
    Defines one compatibility macro constant
  - ```<cstdbool>``` (C++11) (deprecated in C++17) (removed in C++20)<br>
    Defines one compatibility macro constant
  - ```<iso646.h>```<br>
    Has no effect
  - ```<stdalign.h>``` (C++11)<br>
    Defines one compatibility macro constant
  - ```<stdbool.h>``` (C++11)<br>
    Defines one compatibility macro constant
