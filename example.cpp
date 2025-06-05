// example.cpp
// A comprehensive example demonstrating various Modern C++ features
// All comments and code are in English

#include <iostream>
#include <vector>
#include <initializer_list>
#include <tuple>
#include <string>
#include <string_view>
#include <complex>
#include <chrono>
#include <cmath>
#include <thread>
#include <atomic>
#include <type_traits>
#include <compare>
#include <optional>

// =============================
// Preprocessor Directives
// =============================

// Conditional compilation
#define ENABLE_FEATURE 1

#if ENABLE_FEATURE
    #define MESSAGE "Feature is enabled"
#else
    #define MESSAGE "Feature is disabled"
#endif

// Macro with variadic arguments (C++20 __VA_OPT__)
#define LOG(msg, ...) \
    std::printf("[" __FILE__ ":%s:%d] " msg "\n", __func__, __LINE__ __VA_OPT__(,) __VA_ARGS__)

// Stringification and token-pasting macros
#define STRINGIFY(x) #x
#define CONCAT(a, b) a##b

// Diagnostic directive (C++23)
//#warning "Compiling example.cpp"

// =============================
// Constants
// =============================

// nullptr_t and nullptr (C++11)
void foo(char*);
void foo(int);
void foo(std::nullptr_t);

void test_nullptr_overloads() {
    //foo(NULL);      // Ambiguous if foo(nullptr_t) not defined
    foo(nullptr);   // Calls foo(std::nullptr_t)
}

// constexpr (C++11 onward)
constexpr int add_constexpr(int a, int b) {
    return a + b; // C++11 single-return constexpr
}

constexpr int factorial_constexpr(int n) {
    if (n <= 1) return 1; // C++14: conditional + loop
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// C++17: constexpr lambda
constexpr auto identity_lambda = [](int n) constexpr { return n; };

// C++20: constexpr virtual functions and constexpr destructor
struct A {
    virtual int foo() const = 0;
    constexpr virtual ~A() {}
};

struct B : public A {
    constexpr virtual int foo() const override {
        return 42;
    }
    constexpr virtual ~B() {}
};

// C++20: constexpr dynamic allocation
// This is not yet compiling on GCC 14.3/15.1, MSVC 19.43, ...
#ifdef __cpp_constexpr_dynamic_alloc

//struct Node {
//    int value;
//    Node* next;
//    constexpr Node(int v, Node* n = nullptr) : value(v), next(n) {}
//};
//
//constexpr Node* build_list(int n) {
//    if (n <= 0) return nullptr;
//    Node* head = new Node(n);
//    Node* current = head;
//    for (int i = n - 1; i > 0; --i) {
//        current->next = new Node(i);
//        current = current->next;
//    }
//    return head;
//}
//
//constexpr Node* my_list = build_list(5);
#endif

// constinit (C++20)
constexpr int ce_value = 5;
constinit int ci_value = ce_value; // Initialized at compile-time, but mutable

// consteval (C++20)
consteval int immediate_add(int a, int b) {
    return a + b;
}

// std::is_constant_evaluated (C++20)
constexpr double power(double base, int exp) {
    if (std::is_constant_evaluated()) {
        double result = 1.0;
        for (int i = 0; i < exp; ++i) {
            result *= base;
        }
        return result;
    } else {
        return std::pow(base, exp);
    }
}

// =============================
// Literals
// =============================

// Binary literals and digit separators (C++14)
int binary_literal = 0b1101'0101;
int hex_literal     = 0xFF'EE;
long long dec_sep   = 1'234'567'890LL;

// Standard literals
unsigned int ui = 123u;
long long llv   = 123ll;
float flt       = 3.14f;
double dbl      = 2.71828;

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

// Character and string literals
char16_t c16 = u'A';
char32_t c32 = U'Ω';
auto str0    = "Hello"s;          // C++14 string literal
auto str1    = "World"sv;         // C++17 string_view literal
std::u8string u8str = u8"UTF-8";  // C++20 UTF-8 string

// Raw string literal
const char* html = R"HTML(
<html>
  <body>
    <p>Hello, world!</p>
  </body>
</html>
)HTML";

// Complex number literals (C++14)
using namespace std::literals::complex_literals;
auto comp1 = 5.0i;    // std::complex<double> with imaginary part 5
auto comp2 = 2.5if;   // std::complex<float> with imaginary part 2.5

// Chrono literals (C++14 and C++20)
using namespace std::literals::chrono_literals;
auto duration_seconds = 5min + 30s;  // 5 minutes + 30 seconds
auto year2025  = 2025y; // C++20 std::chrono::year
auto day15     = 15d;   // C++20 std::chrono::day

// User-defined literal (C++11)
constexpr float operator""_deg(long double deg) {
    return static_cast<float>(deg * 3.14159265358979323846L / 180.0L);
}

// =============================
// Initialization
// =============================

// Initializer lists (C++11)
void print_values(std::initializer_list<int> values) {
    for (auto it = values.begin(); it != values.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

// Uniform initialization (C++11)
struct Person {
    std::string name;
    int age;
};

void test_uniform_initialization() {
    int x{42};
    // int y{3.14}; // Error: narrowing conversion
    int w{}; // Zero-initialized
    int* p{}; // Initialized to nullptr
    int arr[] {1, 2, 3, 4};

    Person p1{"Alice", 30};
    print_values({1, 2, 3, 4, 5});
}

// Aggregate initialization improvements (C++17)
struct Base {
    int a;
};
struct Derived : Base {
    int b;
};
void test_aggregate_initialization() {
    Derived d{{10}, 20}; // Initialize Base::a = 10, Derived::b = 20
    std::cout << "Derived a=" << d.a << " b=" << d.b << "\n";
}

// Designated initializers (C++20)
struct Point {
    int x;
    int y;
    int z;
};

void test_designated_initializers() {
    Point p1 { .x = 1, .y = 2, .z = 3 };
    Point p2 { .x = 5,         .z = 6 }; // y is zero-initialized
    std::cout << "Point p1: (" << p1.x << ", " << p1.y << ", " << p1.z << ")\n";
    std::cout << "Point p2: (" << p2.x << ", " << p2.y << ", " << p2.z << ")\n";
}

// =============================
// Type Inference
// =============================

void test_type_inference() {
    std::vector<int> vec = {1, 2, 3, 4};
    auto it = std::find(vec.begin(), vec.end(), 3); // auto deduction (C++11)
    if (it != vec.end()) {
        std::cout << "Found 3 at position: " << std::distance(vec.begin(), it) << "\n";
    }

    // decltype (C++11)
    auto a = 2.5f;
    auto b = 1;
    decltype(a + b) c; // c is float
    static_assert(std::is_same_v<decltype(c), float>);

    // decltype(auto) (C++14)
    const int ci = 100;
    const int& cri = ci;
    decltype(auto) ref = cri; // ref is const int&
    // auto val = cri; // val is const int (copy)

    // Trailing return type (C++11)
    auto add_trailing = [](auto x, auto y) -> decltype(x + y) {
        return x + y;
    };
    std::cout << "Trailing add: " << add_trailing(2, 3) << "\n";

    // Structured bindings (C++17)
    auto getTuple = []() -> std::tuple<int, double, std::string> {
        return {42, 3.14, "tuple"};
    };
    auto [i, d, s] = getTuple();
    std::cout << "Structured bindings: " << i << ", " << d << ", " << s << "\n";

    struct Punto { int x, y; };
    Punto p{10, 20};
    auto [px, py] = p; // px = 10, py = 20
    std::cout << "Punto: (" << px << ", " << py << ")\n";
}

// =============================
// Control-Flow Enhancements
// =============================

consteval auto ipow_ct(auto base, auto exp) {
    if (base == 0) return 0LL;
    long long result = 1;
    while (exp) {
        if (exp & 1) result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
};

void test_control_flow() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Range-based for loop (C++11)
    for (auto& value : vec) {
        value += 1;
    }

    // Range-based for loop with initializer (C++20)
    for (size_t idx = 0; const auto& val : vec) {
        std::cout << idx++ << ": " << val << "\n";
    }

    // if with initializer (C++17)
    if (auto it = std::find(vec.begin(), vec.end(), 3); it != vec.end()) {
        std::cout << "Found 3 in modified vec\n";
    }

    // if constexpr (C++17)
    auto getValue = [](auto t) {
        if constexpr (std::is_pointer_v<decltype(t)>) {
            return *t;
        } else {
            return t;
        }
    };
    int x = 10;
    int* px = &x;
    std::cout << "getValue(x): " << getValue(x) << "\n";
    std::cout << "getValue(px): " << getValue(px) << "\n";

    // if consteval (C++23)
    constexpr auto ipow = [&](auto base, auto exp) {
        if consteval {
            return static_cast<double>(ipow_ct(base, exp));
        }
        return std::pow(static_cast<double>(base), static_cast<double>(exp));
    };

    constexpr long long ipow_result = ipow(2, 10); // compile-time
    std::cout << "ipow(2,10) compile-time: " << ipow_result << "\n";

    // switch with initializer (C++17)
    enum class Status { Init, Running };
    auto getStatus = []() { return Status::Running; };
    switch (auto status = getStatus(); status) {
        case Status::Init:
            std::cout << "Status: Init\n";
            break;
        case Status::Running:
            std::cout << "Status: Running\n";
            break;
    }
}

// =============================
// Lambdas
// =============================

void test_lambdas() {
    int foo = 5;

    // Lambda expression (C++11)
    auto lambda1 = [foo](int a, int b) -> int {
        return foo + a + b;
    };
    std::cout << "lambda1(2,3): " << lambda1(2, 3) << "\n";

    // Default parameters in lambda (C++14)
    auto lambda2 = [](int a, int b = 10) { return a + b; };
    std::cout << "lambda2(5): " << lambda2(5) << "\n";

    // Template parameters in lambda (C++14)
    auto lambda3 = [](auto a, auto b = 1) { return a + b; };
    std::cout << "lambda3(3.5, 2.5): " << lambda3(3.5, 2.5) << "\n";

    // Generalized capture (C++14)
    auto lambda4 = [sum = 0](auto value) mutable {
        sum += value;
        return sum;
    };
    std::cout << "lambda4(5): " << lambda4(5) << "\n";
    std::cout << "lambda4(3): " << lambda4(3) << "\n";

    // Returning a lambda from a function (C++14)
    auto make_adder = [](int x) {
        return [x](int y) { return x + y; };
    };
    auto adder = make_adder(7);
    std::cout << "adder(3): " << adder(3) << "\n";

    // Capture of *this (C++17)
    struct Cls {
        int value;
        Cls(int v) : value(v) {}
        auto getLambda() const {
            return [*this]() { return value * value; }; // captures copy of *this
        }
    };
    Cls cobj(6);
    auto lambda5 = cobj.getLambda();
    std::cout << "lambda5(): " << lambda5() << "\n";

    // Constexpr lambda (C++17)
    constexpr auto add_constexpr_lambda = [](auto a, auto b) { return a + b; };
    static_assert(add_constexpr_lambda(2, 3) == 5);

    // Templated lambda (C++20)
    auto Pow = [](auto base, auto exponent) {
        if constexpr (std::is_integral_v<decltype(base)>) {
            long long result = 1;
            auto b = base;
            auto e = exponent;
            while (e) {
                if (e & 1) result *= b;
                e >>= 1;
                b *= b;
            }
            return result;
        } else if constexpr (std::is_same_v<decltype(base), float>) {
            return std::powf(base, exponent);
        } else {
            return std::pow(static_cast<double>(base), static_cast<double>(exponent));
        }
    };
    std::cout << "Pow(2, 8): " << Pow(2, 8) << "\n";
    std::cout << "Pow(2.0f, 3): " << Pow(2.0f, 3) << "\n";
}

// =============================
// Other Interesting Parts
// =============================

// Attributes (C++11 onward)
[[nodiscard]] int must_use() { return 42; }

void test_other_parts() {
    // Rvalue references (C++11)
    int a = 3, b = 4;
    int&& rv = a + b; // binds to rvalue (7)
    std::cout << "rvalue reference: " << rv << "\n";

    // Static assertions (C++11)
    static_assert(sizeof(void*) == sizeof(std::uintptr_t), "Pointer size mismatch");

    // sizeof on class member (C++11)
    struct A { double data; };
    std::cout << "Size of A::data: " << sizeof(A::data) << "\n";

    // alignof and alignas (C++11)
    struct alignas(16) Vec4 {
        float x, y, z, w;
    };
    static_assert(alignof(Vec4) == 16);
    alignas(float) unsigned char matrix[sizeof(float) * 16];

    // Thread-local storage (C++11)
    thread_local int tls_counter = 0;
    tls_counter += 1;
    std::cout << "Thread-local counter: " << tls_counter << "\n";

    int result = must_use();
    (void)result; // avoid unused warning
}

// =============================
// Object-Oriented
// =============================

// In-class member initializer (C++11)
struct InClassInit {
    int value = 100;
};

// Inline static member initialization (C++17)
struct InlineStaticInit {
    static inline int static_val = 200;
};

// Delegating constructors (C++11)
struct Delegating {
    int value;
    Delegating() : Delegating(-1) {} // delegates to Delegating(int)
    Delegating(int v) : value(v) {}
};

// Inherited constructors (C++11)
struct BaseCtor {
    int value;
    BaseCtor() : value(0) {}
    BaseCtor(int v) : value(v) {}
};

struct InheritedCtor : public BaseCtor {
    using BaseCtor::BaseCtor; // inherit constructors
};

// Move constructor (C++11)
class ClsMove {
public:
    int* ptr;
    ClsMove() { ptr = new int(0); }
    ClsMove(const ClsMove& other) { ptr = new int(*other.ptr); }
    ClsMove(ClsMove&& other) noexcept { ptr = other.ptr; other.ptr = nullptr; }
    ~ClsMove() { delete ptr; }
};

// Explicit conversion operators (C++11)
struct BoolWrapper {
    bool value;
    explicit BoolWrapper(bool v) : value(v) {}
    explicit operator bool() const { return value; }
    explicit operator std::string() const { return value ? "true" : "false"; }
};

// Explicit virtual function override (C++11)
struct BaseVirtual {
    virtual void foo() { std::cout << "BaseVirtual::foo\n"; }
    virtual void bar() { std::cout << "BaseVirtual::bar\n"; }
};

struct DerivedVirtual : public BaseVirtual {
    void foo(int) { std::cout << "DerivedVirtual::foo(int)\n"; }
    void foo() const { std::cout << "DerivedVirtual::foo() const\n"; } // does not override
    void bar() override { std::cout << "DerivedVirtual::bar\n"; }     // overrides
};

// final (C++11)
struct FinalClass final {
    void display() { std::cout << "This is a final class\n"; }
};

struct BaseFinal {
    virtual void foo() {}
};

struct DerivedFinal : public BaseFinal {
    void foo() final { std::cout << "DerivedFinal::foo (final)\n"; }
};

// Operator <=> (three-way comparator) (C++20)
struct Point3 {
    float x, y;
    constexpr auto operator<=>(const Point3& other) const = default;
};

// Defaulted special member functions (C++11)
struct DefaultMembers {
    DefaultMembers() = default;
    DefaultMembers(const DefaultMembers&) = default;
    DefaultMembers(DefaultMembers&&) = default;
    ~DefaultMembers() = default;
    DefaultMembers& operator=(const DefaultMembers&) = default;
    DefaultMembers& operator=(DefaultMembers&&) = default;
};

// Deleted special member functions (C++11)
struct DeletedMembers {
    DeletedMembers() = delete;
    DeletedMembers(const DeletedMembers&) = delete;
    DeletedMembers(DeletedMembers&&) = delete;
    ~DeletedMembers() = delete;
    DeletedMembers& operator=(const DeletedMembers&) = delete;
};

// Ref-qualifiers (C++11)
struct RefQualifier {
    void foo() &  { std::cout << "Lvalue foo\n"; }
    void foo() && { std::cout << "Rvalue foo\n"; }
    void foo() const & { std::cout << "Const lvalue foo\n"; }
    void foo() const &&{ std::cout << "Const rvalue foo\n"; }
};

// Explicit object member functions (C++23)
struct ExplicitMember {
    std::string name;
    void getName(this ExplicitMember& self) { std::cout << "Lvalue name: " << self.name << "\n"; }
    void getName(this ExplicitMember&& self) { std::cout << "Rvalue name: " << std::move(self.name) << "\n"; }
};

// Strongly typed enumeration (C++11)
enum class StatusCode : uint8_t { OK = 0, Error = 1 };

// Multidimensional subscript operator (C++23)
template<typename T>
struct MultiArray {
    T data[2][2][2];
    T& operator[](size_t i, size_t j, size_t k) {
        return data[i][j][k];
    }
    const T& operator[](size_t i, size_t j, size_t k) const {
        return data[i][j][k];
    }
};

void test_object_oriented() {
    InClassInit ic;
    std::cout << "InClassInit value: " << ic.value << "\n";

    std::cout << "InlineStaticInit static_val: " << InlineStaticInit::static_val << "\n";

    Delegating d1;
    Delegating d2(123);
    std::cout << "Delegating d1.value: " << d1.value << ", d2.value: " << d2.value << "\n";

    InheritedCtor ih1;
    InheritedCtor ih2(456);
    std::cout << "InheritedCtor ih1.value: " << ih1.value << ", ih2.value: " << ih2.value << "\n";

    ClsMove cm1;
    ClsMove cm2 = std::move(cm1);
    std::cout << "ClsMove cm2.ptr: " << (cm2.ptr ? *cm2.ptr : -1) << "\n";

    BoolWrapper bw(true);
    bool bw_bool = static_cast<bool>(bw);
    std::cout << "BoolWrapper as bool: " << std::boolalpha << bw_bool << "\n";

    DerivedVirtual dv;
    BaseVirtual* bv = &dv;
    bv->foo(); // calls BaseVirtual::foo
    bv->bar(); // calls DerivedVirtual::bar

    FinalClass fc;
    fc.display();

    DerivedFinal df;
    df.foo();

    Point3 p1{1.0f, 2.0f}, p2{1.0f, 2.0f};
    if (p1 == p2) {
        std::cout << "Points are equal\n";
    }

    DefaultMembers dm;

    // DeletedMembers dm2; // Error: constructor deleted

    RefQualifier rq;
    rq.foo();          // lvalue
    RefQualifier().foo(); // rvalue

    ExplicitMember em{"Charlie"};
    em.getName();      // lvalue overload
    ExplicitMember{"Dave"}.getName(); // rvalue overload

    StatusCode sc = StatusCode::OK;
    // int code = sc; // Error: no implicit conversion
    int code = static_cast<int>(sc);
    std::cout << "StatusCode as int: " << code << "\n";

    MultiArray<int> ma{};
    ma[0, 0, 0] = 7;
    std::cout << "MultiArray[0,0,0]: " << ma[0, 0, 0] << "\n";
}

// =============================
// Templates
// =============================

// Extern template (C++11)
// In header: extern template class std::vector<int>;
// In one translation unit:
template class std::vector<int>;

// Right-angle brackets (C++11)
std::vector<std::vector<std::vector<int>>> nestedVec;

// Template argument deduction for class templates (C++17)
std::vector vec_ctad = {1, 2, 3, 4}; // deduced as std::vector<int>

// Template aliases (C++11)
template <typename T>
using VecAlias = std::vector<T>;

// Variadic templates (C++11)
template<typename T>
T sum_variadic(T value) {
    return value;
}

template<typename T, typename... Ts>
T sum_variadic(T head, Ts... tail) {
    return head + sum_variadic(tail...);
}

// Fold expressions (C++17)
template<typename... Ts>
auto sum_fold(Ts... args) {
    return (args + ...);
}

void test_templates() {
    std::cout << "sum_variadic(1,2.5,3): " << sum_variadic(1, 2.5, 3) << "\n";
    std::cout << "sum_fold(1, 2, 3, 4): " << sum_fold(1, 2, 3, 4) << "\n";

    VecAlias<int> myVec = {10, 20, 30};
    for (auto v : myVec) {
        std::cout << "VecAlias element: " << v << "\n";
    }
}

// =============================
// Deprecated Features
// =============================

void test_deprecated_features() {
    // std::auto_ptr (C++11 deprecated, removed in C++17)
    // std::auto_ptr<int> p1(new int(5)); // Compilation error if C++17 or higher
    // Prefer std::unique_ptr
    std::unique_ptr<int> p2 = std::make_unique<int>(5);

    // register keyword (deprecated C++11)
    // register int x = 0; // deprecated

    // ++ on bool (deprecated C++11)
    bool b = true;
    // ++b; // logically toggles; deprecated

    // C-style cast (deprecated C++11)
    int x = (int)3.14; // use static_cast instead
    int y = static_cast<int>(3.14);
    (void)x; (void)y;
}

// =============================
// Main
// =============================

int main() {
    std::cout << MESSAGE << "\n";
    LOG("Starting example execution");

    // Constants testing
    test_nullptr_overloads();
    std::cout << "constexpr add: " << add_constexpr(2, 3) << "\n";
    std::cout << "constexpr factorial: " << factorial_constexpr(5) << "\n";
    std::cout << "identity_lambda(7): " << identity_lambda(7) << "\n";
    B b_obj;
    std::cout << "B::foo(): " << b_obj.foo() << "\n";
    //std::cout << "constexpr build_list head value: " << my_list->value << "\n";
    ci_value += 1; // allowed
    std::cout << "constinit ci_value: " << ci_value << "\n";
    constexpr int imadd = immediate_add(3, 4);
    std::cout << "consteval immediate_add: " << imadd << "\n";
    std::cout << "power(2.0, 10): " << power(2.0, 10) << "\n";

    // Literals testing
    std::cout << "binary_literal: " << binary_literal << "\n";
    std::cout << "hex_literal: " << hex_literal << "\n";
    std::cout << "dec_sep: " << dec_sep << "\n";
    std::cout << "str0: " << str0 << ", str1: " << str1 << "\n";
    std::cout << "html snippet:\n" << html << "\n";
    std::cout << "comp1: " << comp1 << ", comp2: " << comp2 << "\n";
    std::cout << "duration_seconds (in seconds): " << std::chrono::duration_cast<std::chrono::seconds>(duration_seconds).count() << "\n";
    std::cout << "year2025: " << static_cast<int>(year2025) << ", day15: " << static_cast<unsigned>(day15) << "\n";
    std::cout << "90_deg in radians: " << 90.0_deg << "\n";

    // Initialization testing
    test_uniform_initialization();
    test_aggregate_initialization();
    test_designated_initializers();

    // Type inference testing
    test_type_inference();

    // Control-flow testing
    test_control_flow();

    // Lambdas testing
    test_lambdas();

    // Other interesting parts
    test_other_parts();

    // Object-oriented testing
    test_object_oriented();

    // Templates testing
    test_templates();

    // Deprecated features testing
    test_deprecated_features();

    LOG("Example execution completed");
    return 0;
}
