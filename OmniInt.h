/*
OmniInt.h

This is a header file for high-precision integer calculations.

Copyright(C) 2025 SharkyMew

Version 1.2.1
*/

#ifndef OmniInt_H
#define OmniInt_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <algorithm>

/**
 * @class OmniInt
 * @brief 一个用于高精度整数计算的类。
 *
 * OmniInt 类支持任意大小的整数，并重载了常见的算术运算符、关系运算符和流运算符，
 * 使得其可以像内置整数类型一样方便地使用。
 * 内部使用一个 vector<int> 来存储数字的每一位，并用一个布尔值表示正负。
 */
class OmniInt
{
public:
    // =================================================================
    // Constructors - 构造函数
    // =================================================================

    /**
     * @brief 默认构造函数。
     * @details 创建一个值为 0 的 OmniInt 对象。
     */
    OmniInt();

    /**
     * @brief 从 long long 构造。
     * @param n 用于初始化的 long long 类型整数。
     */
    OmniInt(long long n);

    /**
     * @brief 从字符串构造。
     * @param s 代表整数的字符串，可以带有一个可选的 '+' 或 '-' 前缀。
     * @throw std::invalid_argument 如果字符串格式无效 (例如，为空、只包含符号或包含非数字字符)。
     */
    OmniInt(const std::string &s);

    /**
     * @brief 拷贝构造函数。
     * @param other 要拷贝的另一个 OmniInt 对象。
     */
    OmniInt(const OmniInt &other);

    // =================================================================
    // Assignment Operators - 赋值运算符
    // =================================================================

    /**
     * @brief long long 赋值运算符。
     * @param n 要赋给当前对象的 long long 值。
     * @return 当前对象的引用。
     */
    OmniInt &operator=(long long n);

    /**
     * @brief 字符串赋值运算符。
     * @param s 要赋给当前对象的字符串表示的整数。
     * @return 当前对象的引用。
     * @throw std::invalid_argument 如果字符串格式无效。
     */
    OmniInt &operator=(const std::string &s);

    /**
     * @brief 拷贝赋值运算符。
     * @param other 要赋给当前对象的另一个 OmniInt 对象。
     * @return 当前对象的引用。
     */
    OmniInt &operator=(const OmniInt &other);

    // =================================================================
    // Unary Arithmetic Operators - 一元算术运算符
    // =================================================================

    /**
     * @brief 负号运算符。
     * @details 返回当前 OmniInt 对象的相反数。如果当前值为 0，则返回 0。
     * @return 一个新的 OmniInt 对象，其值为当前对象的相反数。
     */
    OmniInt operator-() const;

    // =================================================================
    // Binary Arithmetic Operators - 二元算术运算符
    // =================================================================

    /**
     * @brief 加法运算符。
     * @param other 要相加的另一个 OmniInt 对象。
     * @return 一个新的 OmniInt 对象，其值为两者之和。
     */
    OmniInt operator+(const OmniInt &other) const;

    /**
     * @brief 减法运算符。
     * @param other 要相减的另一个 OmniInt 对象。
     * @return 一个新的 OmniInt 对象，其值为两者之差。
     */
    OmniInt operator-(const OmniInt &other) const;

    /**
     * @brief 乘法运算符。
     * @param other 要相乘的另一个 OmniInt 对象。
     * @return 一个新的 OmniInt 对象，其值为两者之积。
     */
    OmniInt operator*(const OmniInt &other) const;

    /**
     * @brief 除法运算符。
     * @param other 除数。
     * @return 一个新的 OmniInt 对象，其值为两者相除的商（向零取整）。
     * @throw std::runtime_error 如果除数为 0。
     */
    OmniInt operator/(const OmniInt &other) const;

    /**
     * @brief 取模运算符。
     * @param other 模数。
     * @return 一个新的 OmniInt 对象，其值为两者相除的余数。
     * @throw std::runtime_error 如果模数为 0。
     */
    OmniInt operator%(const OmniInt &other) const;

    // =================================================================
    // Compound Assignment Operators - 复合赋值运算符
    // =================================================================

    OmniInt &operator+=(const OmniInt &other);
    OmniInt &operator-=(const OmniInt &other);
    OmniInt &operator*=(const OmniInt &other);
    OmniInt &operator/=(const OmniInt &other);
    OmniInt &operator%=(const OmniInt &other);

    // =================================================================
    // Increment and Decrement Operators - 自增自减运算符
    // =================================================================

    /**
     * @brief 前缀自增运算符。
     * @return 自增后当前对象的引用。
     */
    OmniInt &operator++();

    /**
     * @brief 前缀自减运算符。
     * @return 自减后当前对象的引用。
     */
    OmniInt &operator--();

    /**
     * @brief 后缀自增运算符。
     * @return 自增前当前对象的副本。
     */
    OmniInt operator++(int);

    /**
     * @brief 后缀自减运算符。
     * @return 自减前当前对象的副本。
     */
    OmniInt operator--(int);

    // =================================================================
    // Relational Operators - 关系运算符
    // =================================================================

    bool operator<(const OmniInt &other) const;
    bool operator>(const OmniInt &other) const;
    bool operator<=(const OmniInt &other) const;
    bool operator>=(const OmniInt &other) const;
    bool operator==(const OmniInt &other) const;
    bool operator!=(const OmniInt &other) const;

    // =================================================================
    // Other Functions - 其他成员函数
    // =================================================================

    /**
     * @brief 转换为 long long。
     * @details 如果 OmniInt 的值超出 long long 的范围，可能会导致溢出。
     * @return 当前 OmniInt 对象等效的 long long 值。
     */
    long long toLongLong() const;

    /**
     * @brief 转换为字符串。
     * @return 当前 OmniInt 对象的字符串表示。
     */
    std::string toString() const;

    /**
     * @brief 获取数字的位数。
     * @details 返回整数的有效数字位数，不包括符号。例如，-123 的位数为 3，0 的位数为 1。
     * @return 一个 size_t 类型的值，表示数字的位数。
     */
    size_t digitCount() const;

private:
    std::vector<int> val; // 存储每一位数字，低位在前 (val[0] 是个位)
    bool pos;             // 符号位，true 为正数或零，false 为负数

    /**
     * @brief 移除内部存储中多余的前导零。
     * @details 例如，将 `[0, 1, 2, 0, 0]` 整理为 `[0, 1, 2]`。
     */
    void trim();

    /**
     * @brief 获取当前 OmniInt 对象的绝对值。
     * @return 一个新的 OmniInt 对象，其值为当前对象的绝对值。
     */
    OmniInt abs() const;

    /**
     * @brief 比较当前对象与另一个 OmniInt 对象的大小。
     * @param other 要比较的另一个 OmniInt 对象。
     * @return -1 如果 `*this < other`，0 如果 `*this == other`，1 如果 `*this > other`。
     */
    int compare(const OmniInt &) const;
};

// =========================================================================
// 实现
// =========================================================================

// 构建
OmniInt::OmniInt() : pos(true)
{
    val.push_back(0);
}

OmniInt::OmniInt(long long n)
{
    if (n >= 0)
    {
        pos = true;
    }
    else
    {
        pos = false;
        n = -n;
    }
    if (n == 0)
    {
        val.push_back(0);
    }
    while (n > 0)
    {
        val.push_back(n % 10);
        n /= 10;
    }
}

OmniInt::OmniInt(const std::string &s)
{
    if (s.empty() || (s.size() == 1 && (s[0] == '+' || s[0] == '-')))
    {
        throw std::invalid_argument("Invalid string for OmniInt");
    }

    int start = 0;
    if (s[0] == '-')
    {
        pos = false;
        start = 1;
    }
    else if (s[0] == '+')
    {
        pos = true;
        start = 1;
    }
    else
    {
        pos = true;
    }

    for (int i = s.size() - 1; i >= start; --i)
    {
        if (s[i] < '0' || s[i] > '9')
        {
            throw std::invalid_argument("Invalid character in string for OmniInt");
        }
        val.push_back(s[i] - '0');
    }
    trim();
}

OmniInt::OmniInt(const OmniInt &other) : val(other.val), pos(other.pos) {}

OmniInt &OmniInt::operator=(long long n)
{
    val.clear();
    if (n >= 0)
    {
        pos = true;
    }
    else
    {
        pos = false;
        n = -n;
    }
    if (n == 0)
    {
        val.push_back(0);
    }
    while (n > 0)
    {
        val.push_back(n % 10);
        n /= 10;
    }
    return *this;
}

OmniInt &OmniInt::operator=(const std::string &s)
{
    val.clear();
    if (s.empty() || (s.size() == 1 && (s[0] == '+' || s[0] == '-')))
    {
        throw std::invalid_argument("Invalid string for OmniInt assignment");
    }

    int start = 0;
    if (s[0] == '-')
    {
        pos = false;
        start = 1;
    }
    else if (s[0] == '+')
    {
        pos = true;
        start = 1;
    }
    else
    {
        pos = true;
    }

    for (int i = s.size() - 1; i >= start; --i)
    {
        if (s[i] < '0' || s[i] > '9')
        {
            throw std::invalid_argument("Invalid character in string for OmniInt assignment");
        }
        val.push_back(s[i] - '0');
    }
    trim();
    return *this;
}

OmniInt &OmniInt::operator=(const OmniInt &other)
{
    if (this != &other)
    {
        val = other.val;
        pos = other.pos;
    }
    return *this;
}

OmniInt OmniInt::operator-() const
{
    if (val.size() == 1 && val[0] == 0)
        return *this;
    OmniInt result = *this;
    result.pos = !pos;
    return result;
}

OmniInt OmniInt::operator+(const OmniInt &other) const
{
    if (pos == other.pos)
    {
        OmniInt result;
        result.pos = pos;
        int carry = 0;
        size_t i = 0, j = 0;
        while (i < val.size() || j < other.val.size() || carry)
        {
            int sum = carry;
            if (i < val.size())
                sum += val[i++];
            if (j < other.val.size())
                sum += other.val[j++];
            result.val.push_back(sum % 10);
            carry = sum / 10;
        }
        return result;
    }
    return *this - (-other);
}

OmniInt OmniInt::operator-(const OmniInt &other) const
{
    if (pos != other.pos)
    {
        return *this + (-other);
    }

    if (abs() < other.abs())
    {
        OmniInt result = other.abs() - abs();
        result.pos = !pos;
        return result;
    }

    OmniInt result;
    result.pos = true;
    int borrow = 0;
    for (size_t i = 0; i < val.size(); ++i)
    {
        int diff = val[i] - borrow;
        if (i < other.val.size())
            diff -= other.val[i];
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        result.val.push_back(diff);
    }
    result.trim();
    if (!pos)
        result.pos = false;
    if (result.val.size() == 1 && result.val[0] == 0)
        result.pos = true;
    return result;
}

OmniInt OmniInt::operator*(const OmniInt &other) const
{
    if ((val.size() == 1 && val[0] == 0) || (other.val.size() == 1 && other.val[0] == 0))
    {
        return OmniInt(0);
    }

    OmniInt result;
    result.val.resize(val.size() + other.val.size(), 0);
    for (size_t i = 0; i < val.size(); ++i)
    {
        int carry = 0;
        for (size_t j = 0; j < other.val.size() || carry; ++j)
        {
            int current = result.val[i + j] + carry;
            if (j < other.val.size())
                current += val[i] * other.val[j];
            result.val[i + j] = current % 10;
            carry = current / 10;
        }
    }
    result.trim();
    result.pos = (pos == other.pos);
    return result;
}

OmniInt OmniInt::operator/(const OmniInt &other) const
{
    if (other.val.size() == 1 && other.val[0] == 0)
    {
        throw std::runtime_error("Division by zero");
    }
    if (*this == 0 || abs() < other.abs())
    {
        return OmniInt(0);
    }

    // 获取绝对值
    OmniInt abs_this = abs();
    OmniInt abs_other = other.abs();

    // 特殊情况：除数为1或-1
    if (abs_other == 1)
    {
        OmniInt result = *this;
        result.pos = (pos == other.pos);
        if (result == 0)
            result.pos = true;
        return result;
    }

    // 预先计算除数的倍数（1-9倍）
    std::vector<OmniInt> multiples(10);
    for (int i = 1; i <= 9; ++i)
    {
        multiples[i] = abs_other * i;
    }

    // 准备长除法
    std::vector<int> quotient_digits;
    OmniInt current = 0;

    // 从最高位向最低位处理（小端序：最高位在val的末尾）
    for (int i = val.size() - 1; i >= 0; --i)
    {
        current = current * 10 + val[i]; // 左移一位并添加新数字

        // 计算当前位的商
        int digit = 0;
        if (current >= abs_other)
        {
            // 高效商位计算：从9到1查找合适的倍数
            for (int d = 9; d >= 1; --d)
            {
                if (multiples[d] <= current)
                {
                    digit = d;
                    current -= multiples[d];
                    break;
                }
            }
        }
        quotient_digits.push_back(digit);
    }

    // 反转商位序列（小端序转换）
    std::reverse(quotient_digits.begin(), quotient_digits.end());

    // 构造结果
    OmniInt quotient;
    quotient.val = quotient_digits;
    quotient.trim(); // 移除前导零

    // 处理符号
    quotient.pos = (pos == other.pos);
    if (quotient == 0)
        quotient.pos = true;
    return quotient;
}

OmniInt OmniInt::operator%(const OmniInt &other) const
{
    if (other.val.size() == 1 && other.val[0] == 0)
    {
        throw std::runtime_error("Modulo by zero");
    }
    OmniInt remainder = *this - (*this / other) * other;
    return remainder;
}

OmniInt &OmniInt::operator+=(const OmniInt &other) { return *this = *this + other; }
OmniInt &OmniInt::operator-=(const OmniInt &other) { return *this = *this - other; }
OmniInt &OmniInt::operator*=(const OmniInt &other) { return *this = *this * other; }
OmniInt &OmniInt::operator/=(const OmniInt &other) { return *this = *this / other; }
OmniInt &OmniInt::operator%=(const OmniInt &other) { return *this = *this % other; }

OmniInt &OmniInt::operator++() { return *this += 1; }
OmniInt &OmniInt::operator--() { return *this -= 1; }
OmniInt OmniInt::operator++(int)
{
    OmniInt temp = *this;
    ++*this;
    return temp;
}
OmniInt OmniInt::operator--(int)
{
    OmniInt temp = *this;
    --*this;
    return temp;
}

bool OmniInt::operator<(const OmniInt &other) const { return compare(other) == -1; }
bool OmniInt::operator>(const OmniInt &other) const { return compare(other) == 1; }
bool OmniInt::operator<=(const OmniInt &other) const { return compare(other) <= 0; }
bool OmniInt::operator>=(const OmniInt &other) const { return compare(other) >= 0; }
bool OmniInt::operator==(const OmniInt &other) const { return compare(other) == 0; }
bool OmniInt::operator!=(const OmniInt &other) const { return compare(other) != 0; }

long long OmniInt::toLongLong() const
{
    long long result = 0;
    long long power_of_10 = 1;
    for (size_t i = 0; i < val.size(); ++i)
    {
        if (i > 18 && val.size() > 19)
        { // 粗略的溢出检查
            throw std::overflow_error("OmniInt value too large for long long");
        }
        result += val[i] * power_of_10;
        power_of_10 *= 10;
    }
    return pos ? result : -result;
}

std::string OmniInt::toString() const
{
    if (val.empty() || (val.size() == 1 && val[0] == 0))
    {
        return "0";
    }
    std::stringstream ss;
    if (!pos)
    {
        ss << '-';
    }
    for (int i = val.size() - 1; i >= 0; --i)
    {
        ss << val[i];
    }
    return ss.str();
}

size_t OmniInt::digitCount() const
{
    if (val.size() == 1 && val[0] == 0)
        return 1;
    return val.size();
}

void OmniInt::trim()
{
    while (val.size() > 1 && val.back() == 0)
    {
        val.pop_back();
    }
}

OmniInt OmniInt::abs() const
{
    OmniInt result = *this;
    result.pos = true;
    return result;
}

int OmniInt::compare(const OmniInt &other) const
{
    if (pos && !other.pos)
        return 1;
    if (!pos && other.pos)
        return -1;

    int sign_multiplier = pos ? 1 : -1;

    if (val.size() < other.val.size())
        return -1 * sign_multiplier;
    if (val.size() > other.val.size())
        return 1 * sign_multiplier;

    for (int i = val.size() - 1; i >= 0; --i)
    {
        if (val[i] < other.val[i])
            return -1 * sign_multiplier;
        if (val[i] > other.val[i])
            return 1 * sign_multiplier;
    }

    return 0;
}

// =========================================================================
// Non-Member Functions - 非成员函数
// =========================================================================

/**
 * @brief 输出流运算符。
 * @param os 输出流对象。
 * @param n 要输出的 OmniInt 对象。
 * @return 输出流对象的引用。
 */
std::ostream &operator<<(std::ostream &os, const OmniInt &n)
{
    os << n.toString();
    return os;
}

/**
 * @brief 输入流运算符。
 * @param is 输入流对象。
 * @param n 用于存储输入值的 OmniInt 对象。
 * @return 输入流对象的引用。
 */
std::istream &operator>>(std::istream &is, OmniInt &n)
{
    std::string s;
    is >> s;
    n = s;
    return is;
}

/**
 * @brief 计算 OmniInt 的整数平方根。
 * @details 使用牛顿迭代法计算并返回向下取整的整数平方根。
 * @param n 一个非负的 OmniInt 对象。
 * @return OmniInt 类型的整数平方根。
 * @throw std::domain_error 如果输入为负数。
 */
OmniInt sqrt(const OmniInt &n)
{
    if (n < 0)
    {
        throw std::domain_error("Cannot compute square root of a negative number.");
    }
    if (n == 0)
    {
        return 0;
    }

    // 使用新的digitCount方法获取数字位数
    size_t digits = n.digitCount();

    // 更好的初始猜测值：10^(digits/2)
    OmniInt x = 1;
    for (size_t i = 0; i < (digits + 1) / 2; i++)
    {
        x *= 10;
    }

    while (true)
    {
        OmniInt next_x = (x + n / x) / 2;
        if (next_x >= x)
        {
            break;
        }
        x = next_x;
    }
    return x;
}

#endif // OmniInt_H
