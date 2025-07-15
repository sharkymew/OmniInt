#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>
#include <sstream>

#include "OmniInt.h"

// 全局计数器，用于统计测试结果
int tests_passed = 0;
int tests_failed = 0;

// =========================================================================
// 测试辅助框架
// =========================================================================

/**
 * @brief 运行一个测试用例并报告结果
 * @param description 测试用例的描述
 * @param condition 测试的布尔条件，true 表示通过，false 表示失败
 */
void test_case(const std::string &description, bool condition)
{
    if (condition)
    {
        tests_passed++;
        std::cout << "[PASS] " << description << std::endl;
    }
    else
    {
        tests_failed++;
        std::cout << "[FAIL] " << description << std::endl;
    }
}

// =========================================================================
// 测试函数定义
// =========================================================================

void test_constructors_and_assignment()
{
    std::cout << "\n--- Testing Constructors and Assignment ---\n";

    // 默认构造
    OmniInt a;
    test_case("Default constructor", a.toString() == "0");

    // long long 构造
    OmniInt b(12345);
    test_case("long long constructor (positive)", b.toString() == "12345");
    OmniInt c(-54321);
    test_case("long long constructor (negative)", c.toString() == "-54321");
    OmniInt d(0);
    test_case("long long constructor (zero)", d.toString() == "0");
    OmniInt e(LLONG_MAX);
    test_case("long long constructor (LLONG_MAX)", e.toString() == std::to_string(LLONG_MAX));
    OmniInt f(LLONG_MIN);
    test_case("long long constructor (LLONG_MIN)", f.toString() == std::to_string(LLONG_MIN));

    // string 构造
    OmniInt g("98765432109876543210");
    test_case("string constructor (large positive)", g.toString() == "98765432109876543210");
    OmniInt h("-123456789123456789");
    test_case("string constructor (large negative)", h.toString() == "-123456789123456789");
    OmniInt i("+100");
    test_case("string constructor (with + sign)", i.toString() == "100");

    // 拷贝构造
    OmniInt j = g;
    test_case("Copy constructor", j.toString() == g.toString());

    // 赋值运算符
    OmniInt k;
    k = 5;
    test_case("Assignment from long long", k == 5);
    k = "-5";
    test_case("Assignment from string", k == -5);
    k = j;
    test_case("Assignment from OmniInt", k == j);

    // 移动构造和移动赋值 (隐式测试)
    auto create_temp = []()
    { return OmniInt("123"); };
    OmniInt l = create_temp();
    test_case("Move constructor (from temporary)", l == 123);
    k = create_temp();
    test_case("Move assignment (from temporary)", k == 123);
}

void test_relational_operators()
{
    std::cout << "\n--- Testing Relational Operators ---\n";
    OmniInt a(100), b(200), c(-100), d(100);

    test_case("Equality (==)", a == d);
    test_case("Inequality (!=)", a != b);
    test_case("Less than (<)", a < b);
    test_case("Less than or equal (<=) - less", a <= b);
    test_case("Less than or equal (<=) - equal", a <= d);
    test_case("Greater than (>)", b > a);
    test_case("Greater than or equal (>=) - greater", b >= a);
    test_case("Greater than or equal (>=) - equal", a >= d);
    test_case("Positive vs Negative (<)", c < a);
    test_case("Positive vs Negative (>)", a > c);
    test_case("Zero comparison", OmniInt(0) == OmniInt("-0"));
}

void test_arithmetic_operators()
{
    std::cout << "\n--- Testing Arithmetic Operators ---\n";
    OmniInt a("1000"), b("123"), c("-1000"), d("-123");

    // Addition
    test_case("Addition (pos + pos)", (a + b) == OmniInt("1123"));
    test_case("Addition (neg + neg)", (c + d) == OmniInt("-1123"));
    test_case("Addition (pos + neg, result pos)", (a + d) == OmniInt("877"));
    test_case("Addition (pos + neg, result neg)", (b + c) == OmniInt("-877"));
    test_case("Addition (result zero)", (a + c) == OmniInt("0"));

    // Subtraction
    test_case("Subtraction (pos - pos, result pos)", (a - b) == OmniInt("877"));
    test_case("Subtraction (pos - pos, result neg)", (b - a) == OmniInt("-877"));
    test_case("Subtraction (pos - neg)", (a - d) == OmniInt("1123"));
    test_case("Subtraction (neg - pos)", (c - a) == OmniInt("-2000"));
    test_case("Subtraction (result zero)", (a - a) == OmniInt("0"));

    // Multiplication
    OmniInt big1("123456789"), big2("987654321");
    test_case("Multiplication (pos * pos)", (a * b) == OmniInt("123000"));
    test_case("Multiplication (pos * neg)", (a * d) == OmniInt("-123000"));
    test_case("Multiplication (neg * neg)", (c * d) == OmniInt("123000"));
    test_case("Multiplication (num * 0)", (a * 0) == OmniInt("0"));
    test_case("Multiplication (large numbers)", (big1 * big2).toString() == "121932631112635269");

    // Division
    test_case("Division (no remainder)", (a / 10) == OmniInt("100"));
    test_case("Division (with remainder, truncation)", (a / b) == OmniInt("8"));
    test_case("Division (pos / neg)", (a / d) == OmniInt("-8"));
    test_case("Division (neg / neg)", (c / d) == OmniInt("8"));
    test_case("Division (0 / num)", (OmniInt(0) / a) == OmniInt("0"));

    // Modulo
    test_case("Modulo (pos % pos)", (a % b) == OmniInt("16"));
    test_case("Modulo (pos % neg)", (OmniInt(10) % OmniInt(-3)) == OmniInt("1"));
    test_case("Modulo (neg % pos)", (OmniInt(-10) % OmniInt(3)) == OmniInt("-1"));
    test_case("Modulo (neg % neg)", (OmniInt(-10) % OmniInt(-3)) == OmniInt("-1"));
}

void test_compound_and_increment()
{
    std::cout << "\n--- Testing Compound and Increment/Decrement Operators ---\n";
    OmniInt a(100);
    a += 50;
    test_case("+= operator", a == 150);
    a -= 100;
    test_case("-= operator", a == 50);
    a *= 4;
    test_case("*= operator", a == 200);
    a /= 10;
    test_case("/= operator", a == 20);
    a %= 7;
    test_case("%= operator", a == 6);

    // Increment/Decrement
    a = 10;
    test_case("Prefix ++", ++a == 11 && a == 11);
    test_case("Postfix ++", a++ == 11 && a == 12);
    test_case("Prefix --", --a == 11 && a == 11);
    test_case("Postfix --", a-- == 11 && a == 10);
}

void test_exceptions()
{
    std::cout << "\n--- Testing Exception Safety ---\n";

    // Invalid string
    try
    {
        OmniInt a("abc");
        test_case("Exception on invalid string", false);
    }
    catch (const std::invalid_argument &)
    {
        test_case("Exception on invalid string", true);
    }

    // Division by zero
    try
    {
        OmniInt a = 100 / OmniInt(0);
        test_case("Exception on division by zero", false);
    }
    catch (const std::runtime_error &)
    {
        test_case("Exception on division by zero", true);
    }

    // Modulo by zero
    try
    {
        OmniInt a = 100 % OmniInt(0);
        test_case("Exception on modulo by zero", false);
    }
    catch (const std::runtime_error &)
    {
        test_case("Exception on modulo by zero", true);
    }

    // toLongLong overflow
    try
    {
        OmniInt too_big(LLONG_MAX);
        too_big += 1;
        too_big.toLongLong();
        test_case("Exception on toLongLong() overflow (large)", false);
    }
    catch (const std::overflow_error &)
    {
        test_case("Exception on toLongLong() overflow (large)", true);
    }

    try
    {
        OmniInt too_small(LLONG_MIN);
        too_small -= 1;
        too_small.toLongLong();
        test_case("Exception on toLongLong() overflow (small)", false);
    }
    catch (const std::overflow_error &)
    {
        test_case("Exception on toLongLong() overflow (small)", true);
    }
}

void test_utility_and_streams()
{
    std::cout << "\n--- Testing Utility Functions and Streams ---\n";

    OmniInt a("-12345");
    test_case("toString()", a.toString() == "-12345");
    test_case("digitCount()", a.digitCount() == 5);
    test_case("digitCount() on zero", OmniInt(0).digitCount() == 1);

    // Stream I/O
    OmniInt b;
    std::stringstream ss;
    ss << a;
    ss >> b;
    test_case("Stream I/O (<< and >>)", a == b);
}

void test_sqrt()
{
    std::cout << "\n--- Testing sqrt() Function ---\n";

    test_case("sqrt(0)", sqrt(OmniInt(0)) == 0);
    test_case("sqrt(1)", sqrt(OmniInt(1)) == 1);
    test_case("sqrt(100)", sqrt(OmniInt(100)) == 10);
    test_case("sqrt(99)", sqrt(OmniInt(99)) == 9); // Test truncation
    test_case("sqrt(perfect square)", sqrt(OmniInt("12345678987654321")) == OmniInt("111111111"));

    // The big test case from our debugging session
    OmniInt n("98765432109876543210");
    OmniInt expected_sqrt("9938079900");
    test_case("sqrt(large number)", sqrt(n) == expected_sqrt);

    // Exception for negative input
    try
    {
        sqrt(OmniInt(-1));
        test_case("Exception on sqrt(-1)", false);
    }
    catch (const std::domain_error &)
    {
        test_case("Exception on sqrt(-1)", true);
    }
}

// =========================================================================
// 新增: GCD 测试函数
// =========================================================================
void test_gcd()
{
    std::cout << "\n--- Testing gcd() Function ---\n";

    // 基本情况
    test_case("gcd(n, 0)", gcd(OmniInt(123), OmniInt(0)) == 123);
    test_case("gcd(0, n)", gcd(OmniInt(0), OmniInt(123)) == 123);
    test_case("gcd(0, 0)", gcd(OmniInt(0), OmniInt(0)) == 0);

    // 常规情况
    test_case("gcd(60, 48)", gcd(OmniInt(60), OmniInt(48)) == 12);
    test_case("gcd(48, 60)", gcd(OmniInt(48), OmniInt(60)) == 12);

    // 互质数
    test_case("gcd(coprime numbers)", gcd(OmniInt(17), OmniInt(13)) == 1);

    // 倍数关系
    test_case("gcd(one is multiple of other)", gcd(OmniInt(100), OmniInt(20)) == 20);

    // 符号处理 (结果应始终为非负)
    test_case("gcd(-60, 48)", gcd(OmniInt(-60), OmniInt(48)) == 12);
    test_case("gcd(60, -48)", gcd(OmniInt(60), OmniInt(-48)) == 12);
    test_case("gcd(-60, -48)", gcd(OmniInt(-60), OmniInt(-48)) == 12);

    // 大数测试
    OmniInt g("1000000007"); // 一个较大的质数作为公因子
    OmniInt x("17");         // 使用一个质数作为乘数
    OmniInt y("19");         // 使用另一个不同的质数作为乘数 (17和19互质)

    OmniInt a = g * x;
    OmniInt b = g * y;
    test_case("gcd(large numbers)", gcd(a, b) == g);
}

// =========================================================================
// 主函数
// =========================================================================

int main()
{
    std::cout << "========================================" << std::endl;
    std::cout << "     Starting OmniInt Test Suite        " << std::endl;
    std::cout << "========================================" << std::endl;

    test_constructors_and_assignment();
    test_relational_operators();
    test_arithmetic_operators();
    test_compound_and_increment();
    test_utility_and_streams();
    test_sqrt();
    test_gcd(); // <-- 新增对 gcd 测试的调用
    test_exceptions();

    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "Test Summary:" << std::endl;
    std::cout << "  Total tests run: " << tests_passed + tests_failed << std::endl;
    std::cout << "  Passed: " << tests_passed << std::endl;
    std::cout << "  Failed: " << tests_failed << std::endl;
    std::cout << "========================================" << std::endl;

    // 如果有测试失败，返回非零退出码
    return (tests_failed > 0) ? 1 : 0;
}