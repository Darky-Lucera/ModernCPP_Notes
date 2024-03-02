# Modern C++ 

- [Constants](#constants)
  - [nullptr_t and nullptr [C++11]](#nullptr_t-and-nullptr-c11)
  - [constexpr [C++11]](#constexpr-c11)
  - [constinit [C++20]](#constinit-c20)
  - [consteval [C++20]](#consteval-c20)
  - [std::is_constant_evaluated [C++20]](#stdis_constant_evaluated-c20)
- [Literals](#literals)
  - [Binary Literals [C++14]](#binary-literals-c14)
  - [Digit separators [C++14]](#digit-separators-c14)
  - [Standard literals](#standard-literals)
    - [Integer literals](#integer-literals)
    - [Floating point literals](#floating-point-literals)
    - [Character literals](#character-literals)
    - [String literals](#string-literals)
    - [Raw string literal](#raw-string-literal)
    - [Complex numbers literals](#complex-numbers-literals)
    - [Chrono literals](#chrono-literals)
  - [User-defined literals [C++11]](#user-defined-literals-c11)
- [Initialization](#Initialization)
  - [Initializer lists [C++11]](#Initializer-lists-C11)
  - [Uniform initialization [C++11]](#Uniform-initialization-C11)
  - [Designated Initializers [C++20]](#Designated-Initializers-c20)
- [Type inference](#type-inference)
  - [auto [C++11]](#auto-c11)
  - [decltype(...) [C++11]](#decltype-c11)
  - [decltype(auto) [C++14]](#decltypeauto-c14)
  - [Tail type [C++11]](#tail-type-c11)
- [Control flow enhancements](#control-flow-enhancements)
  - [Range-based for loop [C++11]](#range-based-for-loop-c11)
  - [Range-based for loop with initializer [C++20]](#range-based-for-loop-with-initializer-c20)
  - [if with initializer [C++17]](#if-with-initializer-c17)
  - [if constexpr [C++17]](#if-constexpr-c17)
  - [if consteval [C++23]](#if-consteval-c23)
  - [switch with initializer [C++17]](#switch-with-initializer-c17)
- [Object Oriented](#object-oriented)
  - [Initializing class member variables [C++11]](#initializing-class-member-variables-c11)
  - [Initializing static class member variables [C++17]](#initializing-static-class-member-variables-c17)
  - [Delegate constructor [C++11]](#delegate-constructor-c11)
  - [Inherit constructors [C++11]](#inherit-constructors-c11)
  - [Explicit virtual function override [C++11]](#explicit-virtual-function-override-c11)
  - [final [C++11]](#final-c11)
  - [Operator spaceship <=> (3 way comparator) [C++20]](#operator-spaceship--3-way-comparator-c20)
  - [Generate default function [C++11]](#generate-default-function-c11)
  - [Explicit delete default function [C++11]](#explicit-delete-default-function-c11)
  - [Strongly typed enumerations [C++11]](#strongly-typed-enumerations-c11)
- [Deprecated Features](#deprecated-features)

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

// C++17 allows constexpr lambda functions (see lambda functions)
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
std::vector<float>         vec    = {1.0f, 2.0f, 3.0f};   // Automatic conversion.

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

  __Empty C headers__

  - ```<ccomplex> / complex.h>``` (C++11) (deprecated in C++17) (removed in C++20)<br>
    Simply includes the header ```<complex>```
  - ```<ctgmath> / <tgmath.h>``` (C++11) (deprecated in C++17) (removed in C++20)<br>
    Simply includes the headers ```<complex>``` and ```<cmath>``` the overloads equivalent to the contents of the C header tgmath.h are already provided by those headers<br><br>

  __Meaningless C headers__

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
