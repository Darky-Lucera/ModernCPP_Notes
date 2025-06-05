# Modern C++

- [Preprocessor Directives](#preprocessor-directives)
- [Constants](#constants)
  - [nullptr_t and nullptr [C++11]](#nullptr_t-and-nullptr-c11)
  - [constexpr [C++11]](#constexpr-c11)
  - [constinit [C++20]](#constinit-c20)
  - [consteval [C++20]](#consteval-c20)
  - [Comparison of `constexpr` vs. `consteval` vs. `constinit`](#Comparison-of-constexpr-vs-consteval-vs-constinit)
  - [std::is_constant_evaluated [C++20]](#stdis_constant_evaluated-c20)
- [Literals](#literals)
  - [Binary Literals [C++14]](#binary-literals-c14)
  - [Digit Separators [C++14]](#digit-separators-c14)
  - [Standard Literals](#standard-literals)
    - [Integer Literals](#integer-literals)
    - [Floating-Point Literals](#floating-point-literals)
    - [Character Literals](#character-literals)
    - [String Literals](#string-literals)
    - [Raw String Literals](#raw-string-literals)
    - [Complex Number Literals](#complex-number-literals)
    - [Chrono Literals](#chrono-literals-c14-c20)
  - [User-Defined Literals [C++11]](#user-defined-literals-c11)
- [Initialization](#initialization)
  - [Initializer Lists [C++11]](#initializer-lists-c11)
  - [Uniform Initialization [C++11]](#uniform-initialization-c11)
  - [Aggregate Initialization Improvements [C++17]](#aggregate-initialization-improvements-c17)
  - [Designated Initializers [C++20]](#designated-initializers-c20)
- [Type Inference](#type-inference)
  - [auto Keyword [C++11]](#auto-keyword-c11)
  - [decltype(...) [C++11]](#decltype-c11)
  - [decltype(auto) [C++14]](#decltypeauto-c14)
  - [Trailing Return Type [C++11]](#trailing-return-type-c11)
  - [Structured Bindings [C++17]](#structured-bindings-c17)
- [Control-Flow Enhancements](#control-flow-enhancements)
  - [Range-Based for Loop [C++11]](#range-based-for-loop-c11)
  - [Range-Based for Loop with Initializer [C++20]](#range-based-for-loop-with-initializer-c20)
  - [if with Initializer [C++17]](#if-with-initializer-c17)
  - [if constexpr [C++17]](#if-constexpr-c17)
  - [if consteval [C++23]](#if-consteval-c23)
  - [switch with Initializer [C++17]](#switch-with-initializer-c17)
- [Lambdas](#lambdas)
  - [Lambda Expressions [C++11]](#lambda-expressions-c11)
  - [Default Parameters [C++14]](#default-parameters-c14)
  - [Template Parameters [C++14]](#template-parameters-c14)
  - [Generalized Capture [C++14]](#generalized-capture-c14)
  - [Returning a Lambda from a Function [C++14]](#returning-a-lambda-from-a-function-c14)
  - [Capture of this [C++17]](#capture-of-this-c17)
  - [Constexpr Lambda Expressions [C++17]](#constexpr-lambda-expressions-c17)
  - [Templated Lambdas [C++20]](#templated-lambdas-c20)
- [Other Interesting Parts](#other-interesting-parts)
  - [Rvalue References [C++11]](#rvalue-references-c11)
  - [Static Assertions [C++11]](#static-assertions-c11)
  - [sizeof on Class Members [C++11]](#sizeof-on-class-members-c11)
  - [Object Alignment Control and Query [C++11]](#object-alignment-control-and-query-c11)
  - [Thread-Local Storage (TLS) [C++11]](#thread-local-storage-tls-c11)
  - [Attributes [C++11]](#attributes-c11)
- [Object-Oriented](#object-oriented)
  - [In-Class Member Initializers [C++11]](#in-class-member-initializers-c11)
  - [Inline Static Member Initialization [C++17]](#inline-static-member-initialization-c17)
  - [Delegating Constructors [C++11]](#delegating-constructors-c11)
  - [Inherited Constructors [C++11]](#inherited-constructors-c11)
  - [Move Constructors [C++11]](#move-constructors-c11)
  - [Explicit Conversion Operators [C++11]](#explicit-conversion-operators-c11)
  - [Explicit virtual Function Override [C++11]](#explicit-virtual-function-override-c11)
  - [final [C++11]](#final-c11)
  - [Operator <=> (Three-Way Comparator) [C++20]](#operator-spaceship-three-way-comparator-c20)
  - [Defaulted Special Member Functions [C++11]](#defaulted-special-member-functions-c11)
  - [Deleted Special Member Functions [C++11]](#deleted-special-member-functions-c11)
  - [Ref-Qualifiers [C++11]](#ref-qualifiers-c11)
  - [Explicit Object Member Functions [C++23]](#explicit-object-member-functions-c23)
  - [Strongly Typed Enumerations [C++11]](#strongly-typed-enumerations-c11)
  - [Multidimensional Subscript Operator [C++23]](#multidimensional-subscript-operator-c23)
- [Templates](#templates)
  - [Extern Templates [C++11]](#extern-templates-c11)
  - [Right-Angle Brackets [C++11]](#right-angle-brackets-c11)
  - [Template Argument Deduction for Class Templates [C++17]](#template-argument-deduction-for-class-templates-c17)
  - [Template Aliases [C++11]](#template-aliases-c11)
  - [Variadic Templates [C++11]](#variadic-templates-c11)
  - [Fold Expressions [C++17]](#fold-expressions-c17)
- [Deprecated Features](#deprecated-features)

## Preprocessor Directives

Since the additions in this section are very few, most directives are grouped here.

[**Conditional Compilation**](https://en.cppreference.com/w/cpp/preprocessor/conditional):

```cpp
#if     expression
#ifdef  id         // equivalent to: #if defined(id)
#ifndef id         // equivalent to: #if !defined(id)
#elif   expression
#else
#endif

// New in C++23
#elifdef    id     // equivalent to: #elif defined(id)
#elifndef   id     // equivalent to: #elif !defined(id)
```

[**Macros**](https://en.cppreference.com/w/cpp/preprocessor/replace):

```cpp
#define id              [expressions]
#define id(params)      [expressions]
#define id(params, ...) [expressions] // [C++11] __VA_OPT__() and __VA_ARGS__ can manage the ellipsis
#define id(...)         [expressions] // [C++11] __VA_OPT__() and __VA_ARGS__ can manage the ellipsis
#undef  id

// __VA_ARGS__ is not always available before C++11.
// __VA_OPT__ is available since C++20.

// Example using __VA_ARGS__ and __VA_OPT__ (C++20)
#define LOG(msg, ...) printf("[" __FILE__ ":%s:%d] " msg, __func__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
```

**Operators**

- Operator Stringification `#`: Converts a token to a string.
- Operator Token-Pasting  `##`: Concatenates two tokens.

```cpp
#define kStringify(x)    #x
#define kConcat(x, y)    x##y

int num1 = 5;
int num2 = 10;
int result = kConcat(num, 1) + kConcat(num, 2);

printf("%s = %d\n", kStringify(result), result); // result = 15
```

[**Include Directives**](https://en.cppreference.com/w/cpp/preprocessor/include):

```cpp
#include <header>             // global header
#include "header"             // local header
#if __has_include(<header>)   // global header check [C++17]
  ...
#elif __has_include("header") // local header check [C++17]
  ...
#endif

#if defined(__has_include)
  #if __has_include(<optional>)
    #include <optional>
  #endif
#endif
```

[**Diagnostic Directives**](https://en.cppreference.com/w/cpp/preprocessor/error):

```cpp
#warning    "message"   //                      [C++23]
#error      "message"   //                      [C++98]
```

[**Implementation-Defined Behavior Control**](https://en.cppreference.com/w/cpp/preprocessor/impl):

```cpp
#pragma name                // Usually 'name' is compiler-specific
_Pragma(string)             // Allows using pragma inside macros [C++11]

#pragma once

#pragma pack(push)          // Save current alignment
#pragma pack(push, value)   // Save current alignment and set to 'value'
#pragma pack(pop)           // Restore last alignment
#pragma pack(value)         // Set alignment to 'value'
#pragma pack()              // Restore default alignment
```

[**Predefined Macros**](https://en.cppreference.com/w/cpp/preprocessor/replace#Predefined_macros):

Not all compilers define the same macros, so their availability may vary.

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
__FUNCTION__                        Current function name. Non-standard
__FUNCDNAME__                       Current function name. Non-standard
__PRETTY_FUNCTION__                 Current function name. Non-standard [GCC]
__FUNCSIG__                         Current function name. Non-standard [MSVC]
__STDCPP_DEFAULT_NEW_ALIGNMENT__    [C++17]
__STDCPP_BFLOAT16_T__               [C++23]
__STDCPP_FLOAT16_T__                [C++23]
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

## Constants

### nullptr_t and nullptr [C++11]

- The type of `nullptr` is `std::nullptr_t`.
- It replaces the macro `NULL` with a more meaningful, type-safe keyword.
- `nullptr` is not `0`, `0x0`, `((void*)0)`, etc.

**Benefits**:

- Improves code readability and type safety.

**Example**;

```cpp
void foo(char *);
void foo(int);
void foo(std::nullptr_t); // Since C++11 we can detect nullptr

foo(NULL);      // Ambiguous: could call either overload
foo(nullptr);   // Calls foo(std::nullptr_t) if defined, if not calls foo(char *)
```

### constexpr [C++11]

- `constexpr` **variables** are evaluated at compile time and cannot be modified.

  - **Built-in types**: `constexpr` implies `const` (`bool`, `int`, `float`, `uint64_t`, ...).
  - **Pointers**: `constexpr` implies that the pointer itself is constant `int * const` but NOT `const int *`.

- `constexpr` **functions** can be executed at compile time if all arguments are constant expressions.

#### Evolution by Standard

- **C++11**: Limited to a single `return` expression and cannot contain loops or branches.
- **C++14**: Allows conditionals (`if`, `switch`), loops, and multiple statements. Class types in `constexpr` functions can have mutable members.
- **C++17**: Introduces `constexpr` lambdas.
- **C++20**: Allows `constexpr` destructors and virtual functions, and the use of exceptions in `constexpr` contexts.
- **C++20**: Allows `constexpr` dynamic allocations.


```cpp
// C++11 constexpr function (single return only)
constexpr int add(int a, int b) {
    return a + b;
}

// C++14 constexpr function (multiple statements, loops)
constexpr int factorial(int n) {
    if (n <= 1) return 1;
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// C++17 constexpr lambda
auto identity = [](int n) constexpr { return n; };

// C++20 constexpr virtual function
struct A {
    virtual int foo() const = 0;
    constexpr virtual ~A() { ... }
};

struct B : public A {
    constexpr virtual int foo() const override {
        return 42;
    }
    constexpr virtual ~B() { ... }
};

// C++20 constexpr Dynamic allocations.
struct Node {
    int value;
    Node* next;
    constexpr Node(int v, Node* n = nullptr) : value(v), next(n) {}
};

constexpr Node* build_list(int n) {
    if (n <= 0) return nullptr;
    Node* head = new Node(n);
    Node* current = head;
    for (int i = n - 1; i > 0; --i) {
        current->next = new Node(i);
        current = current->next;
    }
    return head;
}

constexpr Node* my_list = build_list(5); // Constructed at compile time
```

**Benefits**:

- Enables compile-time computation and checking.
- Facilitates optimizations and metaprogramming.

**Special cases**:

```cpp
// In this case, const is irrelevant. It only adds some semantic value.
constexpr char       kStrA[] = "Hola";
constexpr const char kStrB[] = "Hola";

// Remember the address of a variable inside a function is unknown at compile time
int value = 0;

int
main() {
    constexpr int *             constexprPtr            = &value;   // We can NOT modify the pointer, only the value. It is equal to 'constexpr int * const'
    constexpr const int *       constexprConstPtr       = &value;   // We can NOT modify either the pointer or the value. It is equal to 'constexpr const int * const'
    constexpr int * const       constexprPtrConst       = &value;   // We can NOT modify the pointer, only the value. The second const is redundant!
    constexpr const int * const constexprConstPtrConst  = &value;   // We can NOT modify either the pointer or the value. The second const is redundant!

    int *                       ptr                     = &value;   // We can modify the pointer and the value
    const int *                 constPtr                = &value;   // We can modify the pointer but NOT the value
    int * const                 ptrConst                = &value;   // We can NOT modify the pointer, only the value
    const int * const           constPtrConst           = &value;   // We can NOT modify either the pointer or the value

    constexpr int &             constexprRef            = value;
    constexpr const int &       constexprConstRef       = value;
    // This is not valid in C++
    //constexpr int & const       constexprRefConst       = value;
    //constexpr const int & const constexprConstRefConst  = value;

    int &                       ref                     = value;
    const int &                 constRef                = value;
    // This is not valid in C++
    //int & const                 refConst                = value;
    //const int & const           constRefConst           = value;

    //---------------------------------
    // constexpr pointers
    //---------------------------------
    *constexprPtr           = 1;
    //*constexprConstPtr      = 2;      // [WRONG] The value is const
    *constexprPtrConst      = 3;
    //*constexprConstPtrConst = 4;      // [WRONG] The value is const

    //++constexprPtr;                   // [WRONG] The pointer is const
    //++constexprConstPtr;              // [WRONG] The pointer is const
    //++constexprPtrConst;              // [WRONG] The pointer is const
    //++constexprConstPtrConst;         // [WRONG] The pointer is const

    //---------------------------------
    // normal pointers
    //---------------------------------
    *ptr                    = 5;
    //*constPtr               = 6;      // [WRONG] The value is const
    *ptrConst               = 7;
    //*constPtrConst          = 8;      // [WRONG] The value is const

    ++ptr;
    ++constPtr;
    //++ptrConst;                       // [WRONG] The pointer is const
    //++constPtrConst;                  // [WRONG] The pointer is const

    //---------------------------------
    // constexpr references
    //---------------------------------
    constexprRef            = 9;
    //constexprConstRef       = 10;     // [WRONG] The value is const

    ++constexprRef;                     // Valid but don't do this at home.
    //++constexprConstRef;              // [WRONG] The reference is const

    //---------------------------------
    // normal references
    //---------------------------------
    ref                     = 13;
    //constRef                = 14;     // [WRONG] The value is const

    ++ref;
    //++constRef;                       // [WRONG] The reference is const

    return 0;
}
```

### constinit [C++20]

- Ensures that a variable with static storage duration is initialized at compile time (i.e., constant initialization).
- The variable remains mutable at runtime.
- It can be used in global objects or objects declared with static or extern.

**Benefits**:

- Avoids the static-initialization-order fiasco.
- Enables stronger compile-time guarantees.
- Improves code safety by avoiding undefined behavior.
- Facilitates static analysis and optimizations.

**Example**:

```cpp
constexpr int ce = 3;
constinit int ci = ce;         // OK: x is a constexpr
//constinit int error = ci;    // Error: ci is not usable in constant expressions

void foo() {
    ce++;  // Error: ce is constexpr
    ci++;  // OK: ci is constinit (and mutable)
}
```

### consteval [C++20]

- Defines an **immediate function**: it must be evaluated at compile time.
- Cannot be called at runtime.

**Benefits**:

- Improves performance by pre-computing values.
- Enables compile-time checks and optimizations.
- Enforces compile-time computation for functions that must produce constant expressions.

**Example**;

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

### Comparison of `constexpr` vs. `consteval` vs. `constinit`

| Keyword             | Applies To              | Evaluation Time           |
| --------------------| ----------------------- | ------------------------- |
| `constexpr` [C++11] | Functions and variables | Compile‐time *or* runtime |
| `consteval` [C++20] | Functions               | Always compile‐time       |
| `constinit` [C++20] | Variables               | N/A (variable‐level)      |

### std::is_constant_evaluated [C++20]

Detects whether the current evaluation context is a constant expression.

**Example**;

```cpp
constexpr double
power(double b, int x) {
    if (std::is_constant_evaluated()) {
        // Compile-time path
        double result = 1;
        for (int i = 0; i < x; ++i) {
            result *= b;
        }
        return result;
    }
    else {
        // Runtime path
        return std::pow(b, double(x));
    }
}
```

## Literals

### Binary Literals [C++14]

Prefix `0b` or `0B` followed by one or more binary digits (`0` or `1`).

**Example**;

```cpp
int             a = 0b0001;
unsigned int    b = 0B0010;
```

### Digit Separators [C++14]

The single-quote character (`'`) may be used arbitrarily as a digit separator in numeric literals to improve readability.

Useful to make numbers more 'human readable'.

**Example**;

```cpp
int     bin = 0b0000'0011'1110'1000;
int     oct = 0'17'50;
int     dec = 1'23'456'7890;
int     hex = 0x03'E8;
float   flt = 0.1234'5678f;
double  dbl = 0.12'34'56'78;
```

### Standard Literals

#### Integer Literals

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

#### Floating-Point Literals

```
f / F           float                           2f, 2.0f
l / L           long double                     2.0l / 2.0L
e / E           Exponent                        2e2 / 2E2 == 2 * 10^2 == 200
0x / 0X         Hexadecimal float
p / P           Binary exponent for hex float   0x2.1p0 = (2 + 1/16) * 2^0 = 2.0625
```

**Hexadecimal float regex**:

```
[+-]? 0 [xX] ( [0-9a-fA-F]* . [0-9a-fA-F]+ | [0-9a-fA-F]+ .? ) [pP] [+-]? [0-9]+ [flL]?
```

Examples:

```cpp
0x2p1f    = 2 * 2^1 = 4.0f
-0x2.1p0  = (2 + 1/16) * 2^0 = -2.0625
0x1.0p10L = 1024.0L
0x0.8p-1  = 0.25
```

#### Character Literals

```
L               wchar_t                         L'a'
u8              char8_t  (UTF-8)                u8'a'           Range [0x0, 0x7F]       [C++17]
u               char16_t (UTF-16)               u'a'            Range [0x0, 0xFFFF]     [C++11]
U               char32_t (UTF-32)               U'a'            Range [0x0, 0xFFFFFFFF] [C++11]
```

**Note**: Some compilers may not fully support all Unicode character literal prefixes.

#### String Literals

**Example**;

```cpp
using namespace std::literals::string_literals;       [C++14]
using namespace std::literals::string_view_literals;  [C++17]

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

#### Raw String Literals

```
R"delimiter( raw characters )delimiter"
```

- The delimiter can be any sequence of characters (except `"(` or `)"`).
- Useful for embedding strings that contain backslashes, quotes, or multiple lines.

**Example**;

```cpp
const char *html = R"HTML(
<html>
    <body>
    <p>Hello, world!</p>
    </body>
</html>
)HTML";
```

#### Complex Number Literals [C++14]

Defined in the inline namespace `std::literals::complex_literals`. Creates a `std::complex<T>` representing a pure imaginary value.

Suffixes:

- `if` → `std::complex<float>`
- `i`  → `std::complex<double>`
- `il` → `std::complex<long double>`

**Example**;

```cpp
using namespace std::literals::complex_literals;

auto a = 5if;  // std::complex<float>(0, 5)
auto b = 3.0i; // std::complex<double>(0, 3.0)
```

#### Chrono Literals [C++14, C++20]

Defined in the inline namespace `std::literals::chrono_literals`. [C++14]

Suffixes:

```
h    // std::chrono::hours
min  // std::chrono::minutes
s    // std::chrono::seconds
ms   // std::chrono::milliseconds
us   // std::chrono::microseconds
ns   // std::chrono::nanoseconds

y    // std::chrono::year          (since C++20)
d    // std::chrono::day           (since C++20)
```

**Example**;

```cpp
using namespace std::literals::chrono_literals;

auto timeout = 5min + 30s;     // 5 minutes + 30 seconds
auto year    = 2023y;          // std::chrono::year{2023}
auto days    = 15d;            // std::chrono::day{15}
```

### User-Defined Literals [C++11]

Allows users to define custom suffixes and conversion rules. All user-defined literal operators must begin with an underscore `_`. Standard library literal suffixes never start with an underscore.

Allowed parameter lists for literal operator functions:

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
( const char * ,     size_t )
( const wchar_t * ,  size_t )
( const char8_t * ,  size_t )      // C++20
( const char16_t * , size_t )
( const char32_t * , size_t )
```

**Example**;

```cpp
constexpr float
operator "" _deg (long double deg) {
    return float(deg * 3.141592 / 180.0);
}

constexpr float
operator "" _deg (unsigned long long int deg) {
    return float(deg * 3.141592 / 180.0);
}

// Usage:
sprite.Rotate(180_deg); // Rotate receives radians as parameter
```

## Initialization

### Initializer Lists [C++11]

- `std::initializer_list<T>` is a lightweight container representing a sequence of objects of type `T`.
- It is primarily used to initialize containers and aggregate types in a concise way.
- An `initializer_list` is immutable (its elements cannot be modified).

**Benefits**:

- Improves code readability and conciseness.
- Can be more efficient than manually inserting elements.
- Enables uniform initialization syntax.
- Copying an initializer_list doesn't copy the actual elements, only references them.

**Example**;

```cpp
#include <initializer_list>
#include <vector>
#include <iostream>

std::initializer_list<int> values = {1, 2, 3, 4, 5};
std::vector<float>         vec    = {1, 2.0, 3.0f};   // Automatic conversion

void printValues(std::initializer_list<int> values) {
    for (auto it = values.begin(); it != values.end(); ++it) {
        std::cout << *it << " ";
    }
}
```

### Uniform Initialization [C++11]

- Provides a consistent syntax for initializing objects using braces `{}`.
- Works for built-in types, aggregates, and user-defined types.
- Prevents narrowing conversions (the type inside braces must be representable by the target).

**Example**;

```cpp
int     x     { 42 };
double  y     { 3.14 };
int     z     { 3.14 }; // Error: narrowing conversion
int     w     { };      // Zero-initialized
int     *p    { };      // Initialized to nullptr
int     arr[] { 1, 2, 3, 4 };

struct Person {
    std::string name;
    int age;
};

Person p1 { "Carlos", 10 };

std::vector<float> v {1, 2, 3};
```

### Aggregate Initialization Improvements [C++17]

- C++17 relaxes some aggregate rules, allowing default members and inheritance in aggregates.

**Example**: Class that remains an aggregate despite having base classes (under certain conditions)

```cpp
struct Base {
    int a;
};

struct Derived : Base {
    int b;
};

Derived d{ {1}, 2 };  // Inicializa Base::a = 1, Derived::b = 2
```

### Designated Initializers [C++20]

- This is a C99 standard feature that was not included in C++.
- Prior to C++20, aggregate initialization relied on the order of members in the class or struct definition. However, this could lead to errors if the order changed or if some members were added or removed.

**Example**;

```cpp
struct Point {
    int x;
    int y;
    int z;
};

Point p1 { .x = 10, .y = 20, .z = 30 };
Point p2 { .x = 10,          .z = 30 };   // .y is zero-initialized
Point p3 { .z = 30, .x = 10 };            // Error: Order is important
```

**Note**: The fact that order matters makes it less useful.

## Type Inference

Type inference reduces boilerplate by letting the compiler deduce variable or function return types from context.

### auto Keyword [C++11]

- Replaces explicit type declarations, especially useful with long or complex types.
- Improves code readability and reduces verbosity.

**Example**;

```cpp
auto it = std::find(begin(vec), end(vec), 4);

// Instead of:
std::vector<int>::iterator it = std::find(begin(vec), end(vec), 4);

// C++14: Deduction for return type (not arguments):
template<typename A, typename B>
auto add(A a, B b) {
    return a + b;
}

// C++20: auto in function parameters (deduction for arguments):
auto
multiply(auto a, auto b) {
    return a * b;
}
```

### decltype(...) [C++11]

- Yields the type of an expression without evaluating it.
- Especially useful to deduce types in template code or to declare variables based on expressions.

**Example**;

```cpp
auto          a = 2.3f;
auto          b = 1;
decltype(a + b) c;  // c has the same type as (a + b), which is float

if (std::is_same<decltype(c), int>::value)
    std::cout << "c is int\n";

if (std::is_same<decltype(c), float>::value)
    std::cout << "c is float\n";
```

### decltype(auto) [C++14]

- Deduces types while preserving references and const/volatile qualifiers.
- Useful when you want exactly the type returned by an expression.

**Example**;

```cpp
int             y  = 0;
const int &     y2 = y;

const auto y3 = y2;     // y3 is const int
decltype(auto) y4 = y2; // y4 is const int&
```

### Trailing Return Type [C++11]

- Specifies a function's return type after the parameter list using `->`.
- Enables return type deduction based on parameters (useful for templates).

**Example**;

```cpp
template<typename A, typename B>
auto add(A a, B b) -> decltype(a + b) {
    return a + b;
}
```

### Structured Bindings [C++17]

- Allows unpacking tuple-like or aggregate objects directly into named variables.

**Example**:

```cpp
#include <tuple>
std::tuple<int, double, std::string> getData() {
    return {42, 3.14, "hello"};
}

auto [i, d, s] = getData(); // i == 42, d == 3.14, s == "hello"

//--

struct Punto { int x, y; };

Punto p{10, 20};

auto [px, py] = p;  // px == 10, py == 20
```

## Control-Flow Enhancements

### Range-Based for Loop [C++11]

```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
for(auto &value : vec) {
    value += 3;
}
```

### Range-Based for Loop with Initializer [C++20]

- Introduces an initializer before the range; helpful to manage loop index or temporary variables.

```cpp
std::vector<std::string> vec = {"apple", "banana", "cherry"};
for(size_t index = 0; const auto &value : vec) {
    printf("%zu: %s\n", index++, value.c_str());
}
```

### if with Initializer [C++17]

- Declares a variable inside the `if` statement, reducing its scope.

```cpp
if(auto it = std::find(begin(vec), end(vec), 4); it != end(vec)) {
    *it = -4;
}
```

### if constexpr [C++17]

- Evaluates the condition at compile time if all conditions and branches are constexpr.
- Unused branches are not compiled.
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

### if consteval [C++23]

- Evaluates to true only when the context is a constant expression.
- Notice that braces are mandatory: `if consteval { } else { }```

```cpp
// Used by ipow
consteval uint64_t ipow_ct(uint64_t base, uint8_t exp) {
    if (base == 0)
        return 0;

    uint64_t result = 1;
    while (exp) {
        if (exp & 1) result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
}

constexpr uint64_t ipow(uint64_t base, uint8_t exp) {
    if consteval {
        // Compile-time path
        return ipow_ct(base, exp);
    }

    // use runtime evaluation
    return std::pow(base, exp);
}
```

**Note**: In C++20, you can use [std::is_constant_evaluated()](https://en.cppreference.com/w/cpp/types/is_constant_evaluated) instead of `if consteval` to differentiate compile-time versus runtime.

### switch with Initializer [C++17]

- Declares a variable inside the `switch` statement, limiting its scope.

```cpp
enum class Status { Init, Run };
switch(auto status = GetStatus(); status) {
    case Status::Init:
        ...
        break;

    case Status::Run:
        ...
        break;
}
```

## Lambdas

### Lambda Expressions [C++11]

- Provides a concise way to create anonymous function objects.

**Structure**:

```cpp
[captureList](parameters) mutable -> returnType { body }
```

**Example**:

```cpp
auto lambda = [foo](int a, int b) -> decltype(a + b) {
    return foo + a + b;
};

// The lambda code generated by the compiler would be something like this:
class __RandomName {
  public:
    __RandomName(int _foo) : foo{_foo} { }

    inline int operator()(int a, int b) const {
        return foo + a + b;
    }

  private:
    int foo;
};
```

- **capture-list** (optional):
  - `[&]`: capture all visible variables by reference.
  - `[=]`: capture all visible variables by value.
  - `[&foo, bar]`: capture `foo` by reference and `bar` by value.
- **(parameters)** (optional): Lamba parameters.
- **mutable** (optional): By default, the generated `operator()` is `const`. To modify captured variables, add `mutable` after parameters.
- **return-type** (optional, deduced if not specified).
- **body**: the function body.

**Example**:

```cpp
auto lambda = [foo = 0](int a, int b) mutable {
    ++foo;  // Modifies the captured local copy of foo
    return foo + a + b;
};
```

**Note**: Lambda types are unique and can only be stored in an `auto` or a templated type (e.g., `std::function<>`).

### Default Parameters [C++14]

- Lambdas can have default parameter values, like any other function.

```cpp
auto lambda = [](int a, int b=1) -> int {
    return a + b;
};
```

### Template Parameters [C++14]

- Lambdas can be generic, accepting any types for parameters.

```cpp
auto lambda = [](auto a, auto b=1) {
    return a + b;
};
```

### Generalized Capture [C++14]

- Introduces *init-captures*, allowing initialization of captured values.

```cpp
auto lambda = [sum = 0](auto value) mutable {
    sum += value;
    return sum;
};
```

**Note**: I find it especially useful to capture `std::shared_from_this()` / `std::enable_shared_from_this<>`.

### Returning a Lambda from a Function [C++14]

Since the lambda type must be auto, in C++11 we cannot return a lambda from a function. This is fixed in C++14 as functions are allowed to return auto following the deduction guidelines.

```cpp
auto make_adder(int x) {
    return [x](int y) { return x + y; };
}

auto adder = make_adder(5);
int result = adder(3);  // result == 8
```

### Capture of this [C++17]

- Before C++17, capturing `this` meant capturing the pointer only. C++17 allows capturing a copy of `*this`.

```cpp
class Cls {
    public:
        Cls(int v) : value(v) {}
        auto getLambda() const {
            return [*this]() { return value * value; }; // captures a copy of *this
        }
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

### Constexpr Lambda Expressions [C++17]

- Lambdas can be `constexpr` if their bodies are constexpr-evaluable.

```cpp
constexpr auto add = [](auto a, auto b) {
    return a + b;
};

static_assert(add(2, 1) == 3);
```

### Templated Lambdas [C++20]

- Allows specifying template parameters explicitly for lambdas.

```cpp
//-------------------------------------
// Example: Variadic sum using lambda
//-------------------------------------
template<typename... Args>
int add(Args &&...args) {
    auto lambda = [...args = std::forward<Args>(args)]() {
        return (args + ...); // fold expression (C++17)
    };

    return lambda();
}

//-------------------------------------
// Example: Compile-time optimized power
//-------------------------------------
template <typename T>
auto Pow = [](T base, T exponent) {
    if constexpr (std::is_integral_v<T>) {
        return ipow(base, exponent);    // Optimized for integer types
    }
    else if constexpr (std::is_same_v<T, float>) {
        return std::powf(base, exponent);
    }
    else {
        // fallback to std::pow
        return std::pow(base, exponent); // Default (maybe imaginary numbers?)
    }
};
```

## Other Interesting Parts

### Rvalue References [C++11]

- An **rvalue reference** (`&&`) can bind to temporary objects (rvalues).
- Enables move semantics: transferring resources from temporaries to named objects efficiently.

```cpp
int a = 3;
int b = 4;
int &&rvalue = a + b; // binds to rvalue (3 + 4 == 7)
```

### Static Assertions [C++11]

- `static_assert` checks a compile-time boolean expression; if false, produces a compilation error.
- Pre-C++11 options (`assert`, `#error`) were either too late or too early in compilation.

```cpp
static_assert(sizeof(void *) == sizeof(uint32_t), "We store pointers in uint32_t fields")

template<typename Integral>
Integral foo(Integral x) {
    static_assert(std::is_integral<Integral>::value, "foo() parameter must be an integral type");

    return x;
}
```

### sizeof on Class Members [C++11]

- Allows `sizeof` to work on non-static data members without needing an object instance.

```cpp
struct A {
    int   data;
    double more;
};

auto offset = offsetof(A, data);          // standard C macro
auto size_of_member = sizeof(A::more);    // allowed in C++11 and later
```

### Object Alignment Control and Query [C++11]

C++11 allows variable alignment to be queried `alignof` and queried `alignas`.

- `alignof(T)`: Takes the type and returns the alignment requirement (in bytes) of type ``T.
  - For references, it returns the referenced type's alignment.
  - For arrays, it returns the element type's alignment.

- `alignas()`: Specifies the memory alignment for a variable or type.
`alignas(T)` is shorthand for `alignas(alignof(T))`.

```cpp
struct alignas(16) Vec4 {
    float x, y, z, w;
};

static_assert(alignof(Vec4) == 16);

alignas(float) unsigned char matrix4x4[sizeof(float) * 16]
```

### Thread-Local Storage (TLS) [C++11]

Allows each thread to have its own separate instance of a variable.<br/>
It also works for **static** variables defined inside a function. Each thread will have its own instance of the **per thread global** variable.

- **Lifetime**: The lifetime of a TLS variable begins when it is initialized and ends when the thread terminates.
- **Visibility**: TLS variables have visibility at the thread level.
- **Scope**: TLS variables have scope depending on where they are declared.

```cpp
void log(const char *name) {
    thread_local int counter{};

    printf("%s: %d\n", name, counter++);
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

### Attributes [C++11]

Provide a unified standard syntax for implementation-defined language extensions. Before this feature, each compiler has its own way to do it:

- GNU/Clang: __attribute__((...))
- Microsoft: __declspec(...)
- Borland: __property
- Different compilers: __builtin_XXX

The new standard way is: `[[attribute, attribute...]]`.

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

Since C++17, we can use `[using namespace: atribute, attribute, ...]`.

## Object-Oriented

### In-Class Member Initializers [C++11]

- Allows providing default member initializers inside the class definition.

```cpp
struct A {
    int value = 0;
};
```

### Inline Static Member Initialization [C++17]

- `static inline` variables can be initialized inside the class definition, eliminating the need for an out-of-class definition.

```cpp
struct A {
    static inline int value = 0;
};

// Pre-C++17
// Header
struct A {
    static int value;
};

// Code
int A::value = 0;
```

### Delegating Constructors [C++11]

- A constructor can delegate to another constructor in the same class using the member initializer list.

```cpp
struct A {
    A() : A(-1) {}       // delegates to A(int)
    A(int v) : value(v) {}

    int value;
};
```

### Inherited Constructors [C++11]

- A derived class can inherit constructors from its base class using `using Base::Base;`.

```cpp
struct A {
    A() : A(-1) {}
    A(int v) : value(v) {}

    int value = 0;
};

struct B : public A {
    using A::A;  // inherit A's constructors
};

B b1;      // calls A()
B b2(123); // calls A(int)
```

### Move Constructors [C++11]

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

### Explicit Conversion Operators [C++11]

- Declaring a conversion operator as `explicit` prevents implicit conversions.

```cpp
struct Bool {
    explicit Bool(bool v) : value(v) {}

    explicit operator bool() const { return value; }
    explicit operator std::string() const {
        return value ? "true" : "false";
    }

    bool value {};
};

Bool    b0(true);       // Ok
Bool    b1 { true };    // Ok
Bool    b2 = { true };  // Error: constructor is explicit
Bool    b3 = true;      // Error: constructor is explicit

bool flag1 = static_cast<bool>(b1); // Ook
bool flag2 = b1;                    // Error: operator bool is explicit

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

### Explicit Virtual Function Override [C++11]

- `override` keyword ensures that a virtual function truly overrides a base-class function; otherwise the compiler issues an error.

```cpp
struct A {
    virtual void foo()          { printf("A::foo\n"); }
    virtual void bar()          { printf("A::bar\n"); }
};

struct B : public A {
    void foo(int)               { printf("B::foo(int)\n"); }     // Does not override A::foo (maybe an error)
    void foo() const            { printf("B::foo() const\n"); }  // Does not override A::foo (maybe an error)
    void bar() const override   { printf("B::bar() const\n"); }  // Error: signature mismatch (original bar is not const)
    void bar() override         { printf("B::bar()\n"); }        // Ok
};

A *a = new B;
a->foo();   // A::foo
a->bar();   // B::bar
```

### final [C++11]

- A class declared as `final` cannot be inherited from.
- A virtual function marked `final` cannot be overridden in further derived classes.

```cpp
struct A final {
    void foo() {}
};

// struct B : public A {}; // Error: cannot inherit from final class

struct Base {
    virtual void foo() {}
};

struct B : public Base {
    void foo() final {} // Cannot be overridden further
};

struct C : public B {
    void foo() override {} // Error: B::foo is final
};
```

### Operator `<=>` (Three-Way Comparator) [C++20]

The return value could be one of:

- `std::strong_ordering`:  f(a) must be equal to f(b). Only one of (a < b), (a == b) or (a > b) must be true.
- `std::weak_ordering`:    f(a) may be different from f(b). Only one of (a < b), (a == b) or (a > b) must be true.
- `std::partial_ordering`: f(a) may be different from f(b). (a < b), (a == b) and (a > b) may all be false.
- `int` or other type.

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

    // Alternative:
    constexpr auto operator<=>(const Point &rhs) const {
        if (x < rhs.x) return std::weak_ordering::less;
        if (x > rhs.x) return std::weak_ordering::greater;
        if (y < rhs.y) return std::weak_ordering::less;
        if (y > rhs.y) return std::weak_ordering::greater;
        return std::weak_ordering::equivalent;
    }
};
```

- Alternatively, you can write:

```cpp
struct Point {
    float x, y;
    auto operator<=>(const Point&) const = default; // compiler-generated
};
```

**Note**: The default version ususallly generates better and faster code.

### Defaulted Special Member Functions [C++11]

- `= default` tells the compiler to generate the default implementation of constructors, destructors, or assignment operators.

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

### Deleted Special Member Functions [C++11]

- `= delete` prevents the compiler from generating or using the default version of a function.

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

### Ref-Qualifiers [C++11]

- Allows overloading member functions based on whether the object is an lvalue or rvalue.
- Syntax: `void foo() &` (lvalue only) or `void foo() &&` (rvalue only).

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
    cCls.foo();     // const lvalue

    Cls().foo();    // rvalue
    getCls().foo(); // const rvalue

    return 0;
}
```

### Explicit Object Member Functions [C++23]

- Introduces a clearer syntax for ref-qualifiers by explicitly naming the `this` parameter.

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
    cCls.foo();     // const lvalue

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

Since C++23 we can 'deduce this' using a template to simplify the code:

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
auto fibonacci_14 = [](const auto &self, int n) -> int {
  return n < 2 ? n : self(self, n-1) + self(self, n-2);
};

// But it is a little bit ugly
auto a = fibonacci_14(fibonacci_14, 5);

// Alternative C++14
int foo() {
    // This only works as local lambda.
    // We cannot use auto here.
    static std::function<int(int)> fibonacci_14_alt = [&](int n) -> int {
        return (n < 2) ? n : fibonacci_14_alt(n - 1) + fibonacci_14_alt(n - 2);
    };

    return fibonacci_14(fibonacci_14, 5);
}

//--

// C++23 version using deduce this
auto fibonacci_23 = [](this auto &self, int n) -> long {
    return (n < 2) ? n : self(n-1) + self(n-2);
};

auto a = fibonacci_23(5);
```

### Strongly Typed Enumerations [C++11]

- `enum class` (or `enum struct`) defines an enumeration with a scoped name and optionally a fixed underlying type.
- No implicit conversions to integer, improving type safety.

```cpp
// Note: The type is optional
enum class Status : uint8_t {
    ON = 0,
    OFF,
};

Status s1 = Status::ON; // Ok
Status s2 = ON;         // Error: must use Status::ON
Status s3 = 0;          // Error: no implicit conversion

int x = static_cast<int>(s1); // Ok
int y = s1;             // Error: no implicit conversion
```

### Multidimensional Subscript Operator [C++23]

- Allows a single `operator[]` to accept multiple indices.
- Syntax: `T& operator[](size_t x, size_t y, size_t z);`

```cpp
// Instead of having to use data[x][y][z]
// Now we can have multiple indexes
T &         operator[](size_t x, size_t y, size_t z)        { }
const T &   operator[](size_t x, size_t y, size_t z) const  { }

// and we can use it that way:
data[x, y, z] = 123;

auto value = data[x, y, z];
```

## Templates

### Extern Templates [C++11]

- Tells the compiler not to instantiate a template in this translation unit; instantiation must occur elsewhere.
- Reduces compile times when templates are used across multiple translation units.

```cpp
// In header file:
extern template class std::vector<MyClass>;

// In one .cpp file:
template class std::vector<MyClass>; // Actual instantiation
```

### Right-Angle Brackets [C++11]

Finally! Allows nested template instantiations without spaces between consecutive `>` characters.

```cpp
// Before C++11:
std::vector<std::vector<std::vector<std::vector<std::vector<int> > > > > vec;

// Since C++11:
std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>> vec;
```

### Template Argument Deduction for Class Templates [C++17]

- Deduce template arguments from constructor arguments when instantiating objects.

**Example**:

```cpp
std::vector vec = {1, 2, 3, 4}; // CTAD: deduces std::vector<int>
```

### Template Aliases [C++11]

- `using` syntax provides alias templates, replacing verbose `typedef` declarations.

```cpp
// Before C++11:
typedef std::vector<int> vecInt;

// Since C++11:
using vecInt = std::vector<int>;

//-------------------------------------

template <typename T, typename U>
struct Pair { ... };

// Before C++11, cannot partially apply template parameters:
typedef Pair<int, double> PairIntDouble;

// With alias templates:
template <typename U>
using IntPair = Pair<int, U>;
```

### Variadic Templates [C++11]

- Enables functions or classes to accept an arbitrary number of template parameters or function arguments.

```cpp
template<typename... Values>                class tuple;    // takes zero or more arguments
template<typename Head, typename... Tail>   class tuple;    // takes one  or more arguments

//-------------------------------------
// Example: Variadic function 'print'
//-------------------------------------
template<typename T>
void print(const T& value) {
    std::cout << value << "\n";
}

template<typename T, typename... Args>
void print(const T& first, const Args&... rest) {
    std::cout << first << "\n";
    print(rest...); // Recursive call to print the rest of the arguments
}

//-------------------------------------
// Example: Variadic function 'sum'
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

### Fold Expressions [C++17]

- Simplifies variadic template code by collapsing parameter packs with a binary operator.

**Example**:

```cpp
template<typename... Args>
auto sumAll(Args... args) {
    return (args + ...); // equivalent to a + b + c + ...
}

template<typename T, typename... Rest>
void print_all(const T& first, const Rest&... rest) {
    std::cout << first;
    ((std::cout << ", " << rest), ...);
    std::cout << "\n";
}
```

## Deprecated Features

- **String literal constants** [C++11]

```cpp
          char *str = "Hello";  // Deprecated: mutable pointer to string literal
  const char *str = "Hello";  // Recommended: pointer to const char
```

- **Unexpected handler** [C++11]

`std::unexpected_handler`, `std::set_unexpected()`, `std::get_unexpected()` and other related features are deprecated

- **std::auto_ptr** [C++11] (removed in C++17)

  ```cpp
  // Deprecated in C++11
  std::auto_ptr<int> p(new int(5));
  // Prefer std::unique_ptr or std::shared_ptr
  std::unique_ptr<int> p2 = std::make_unique<int>(5);
  ```

- **register keyword** [C++11]

  ```cpp
  // register int x = 0;  // Deprecated. Compiler decides storage automatically.
  ```

- **++ bool operator** [C++11]

  ```cpp
  // bool b = true;
  // ++b; // Deprecated: increments boolean (conceptually toggles).
  ```

- **C-style casts** [C++11]

Use any of `static_cast<>()`, `reinterpret_cast<>()` or `const_cast<>()`

  ```cpp
  // int x = (int)3.14; // Old style: C-style cast
  int y = static_cast<int>(3.14); // Prefer C++-style cast
  ```

- **Some C standard headers** (deprecated or removed)

  **Empty C headers**

  - `<ccomplex>` / `<complex.h>` [C++11: deprecated in C++17; removed in C++20]<br/>
    Include the header `<complex>`
  - `<ctgmath>` / `<tgmath.h>` [C++11: deprecated in C++17; removed in C++20]<br/>
    Include the headers `<complex>` and `<cmath>` the overloads equivalent to the contents of the C header tgmath.h are already provided by those headers

  **Meaningless C headers**

  - `<ciso646>` [Removed in C++20]<br/>
    Empty header. The macros that appear in iso646.h in C are keywords in C++
  - `<cstdalign>` [C++11: deprecated in C++17; removed in C++20]<br/>
    Defines one compatibility macro constant
  - `<cstdbool>` [C++11: deprecated in C++17; removed in C++20]<br/>
    Defines one compatibility macro constant
  - `<iso646.h>`<br/>
    Has no effect
  - `<stdalign.h>` [C++11]<br/>
    Defines one compatibility macro constant
  - `<stdbool.h>` [C++11]<br/>
    Defines one compatibility macro constant

---
