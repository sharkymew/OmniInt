/*
OmniInt.h

This is a header file for high-precision integer calculations.

Copyright(C) 2025 SharkyMew

Version 1.3.0 (改进版)
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
#include <limits>
#include <utility> // === 改进 3: 引入 <utility> 以便使用 std::move ===

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
    OmniInt() noexcept; // === 改进 4: 添加 noexcept ===

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

    /**
     * @brief === 改进 3: 移动构造函数 ===
     * @param other 用于移动的 OmniInt 对象。
     */
    OmniInt(OmniInt &&other) noexcept;

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

    /**
     * @brief === 改进 3: 移动赋值运算符 ===
     * @param other 要移动赋值的 OmniInt 对象。
     * @return 当前对象的引用。
     */
    OmniInt &operator=(OmniInt &&other) noexcept;

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
     * @details 如果 OmniInt 的值超出 long long 的范围，会抛出 std::overflow_error。
     * @return 当前 OmniInt 对象等效的 long long 值。
     * @throw std::overflow_error 如果 OmniInt 的值超出 long long 的范围。
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

    // === 改进 1: 声明一个私有的除法和取模辅助函数 ===
    /**
     * @brief 一次性计算商和余数的辅助函数。
     * @param divisor 除数。
     * @return std::pair<OmniInt, OmniInt>，第一个元素是商，第二个元素是余数。
     */
    std::pair<OmniInt, OmniInt> divide_and_remainder(const OmniInt &divisor) const;

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
OmniInt::OmniInt() noexcept : pos(true) // === 改进 4: 添加 noexcept ===
{
    val.push_back(0);
}

OmniInt::OmniInt(long long n)
{
    if (n == 0)
    {
        pos = true;
        val.push_back(0);
        return;
    }
    pos = (n > 0);
    unsigned long long magnitude = (n > 0) ? n : -static_cast<unsigned long long>(n);
    while (magnitude > 0)
    {
        val.push_back(magnitude % 10);
        magnitude /= 10;
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
    if (val.size() == 1 && val[0] == 0)
    {
        pos = true;
    }
}

OmniInt::OmniInt(const OmniInt &other) : val(other.val), pos(other.pos) {}

// === 改进 3: 实现移动构造函数 ===
OmniInt::OmniInt(OmniInt &&other) noexcept : val(std::move(other.val)), pos(other.pos)
{
    // 移动后，原对象应处于有效的、可析构的状态
    other.val.clear();
    other.val.push_back(0);
    other.pos = true;
}

OmniInt &OmniInt::operator=(long long n)
{
    val.clear();
    if (n == 0)
    {
        pos = true;
        val.push_back(0);
        return *this;
    }
    pos = (n > 0);
    unsigned long long magnitude = (n > 0) ? n : -static_cast<unsigned long long>(n);
    while (magnitude > 0)
    {
        val.push_back(magnitude % 10);
        magnitude /= 10;
    }
    return *this;
}

OmniInt &OmniInt::operator=(const std::string &s)
{
    // C++11 "copy-and-swap" idiom for strong exception guarantee
    OmniInt temp(s);
    *this = std::move(temp);
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

// === 改进 3: 实现移动赋值运算符 ===
OmniInt &OmniInt::operator=(OmniInt &&other) noexcept
{
    if (this != &other)
    {
        val = std::move(other.val);
        pos = other.pos;

        other.val.clear();
        other.val.push_back(0);
        other.pos = true;
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
    // === 改进 2: 使用就地加法实现，代码复用 ===
    OmniInt result = *this;
    result += other;
    return result;
}

OmniInt OmniInt::operator-(const OmniInt &other) const
{
    // === 改进 2: 使用就地减法实现，代码复用 ===
    OmniInt result = *this;
    result -= other;
    return result;
}

OmniInt OmniInt::operator*(const OmniInt &other) const
{
    // === 改进 2: 使用就地乘法实现，代码复用 ===
    OmniInt result = *this;
    result *= other;
    return result;
}

// === 改进 1: `operator/` 使用辅助函数实现 ===
OmniInt OmniInt::operator/(const OmniInt &other) const
{
    return divide_and_remainder(other).first;
}

// === 改进 1: `operator%` 使用辅助函数实现 ===
OmniInt OmniInt::operator%(const OmniInt &other) const
{
    return divide_and_remainder(other).second;
}

// === 改进 2: 实现高效的就地复合赋值运算符 ===
OmniInt &OmniInt::operator+=(const OmniInt &other)
{
    if (pos == other.pos)
    {
        // 同号相加
        val.resize(std::max(val.size(), other.val.size()), 0);
        int carry = 0;
        for (size_t i = 0; i < val.size(); ++i)
        {
            int sum = val[i] + carry + (i < other.val.size() ? other.val[i] : 0);
            val[i] = sum % 10;
            carry = sum / 10;
        }
        if (carry)
        {
            val.push_back(carry);
        }
    }
    else
    {
        // 异号相加，等价于减法
        *this -= (-other);
    }
    return *this;
}

OmniInt &OmniInt::operator-=(const OmniInt &other)
{
    if (pos != other.pos)
    {
        // 异号相减，等价于加法
        *this += (-other);
        return *this;
    }

    // 同号相减
    if (abs() < other.abs())
    {
        *this = -(other - *this);
        return *this;
    }

    int borrow = 0;
    for (size_t i = 0; i < val.size(); ++i)
    {
        int diff = val[i] - borrow - (i < other.val.size() ? other.val[i] : 0);
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        val[i] = diff;
    }
    trim();
    if (val.size() == 1 && val[0] == 0)
    {
        pos = true;
    }
    return *this;
}

OmniInt &OmniInt::operator*=(const OmniInt &other)
{
    if ((val.size() == 1 && val[0] == 0) || (other.val.size() == 1 && other.val[0] == 0))
    {
        *this = 0;
        return *this;
    }

    std::vector<int> result_val(val.size() + other.val.size(), 0);
    for (size_t i = 0; i < val.size(); ++i)
    {
        int carry = 0;
        for (size_t j = 0; j < other.val.size() || carry; ++j)
        {
            int current = result_val[i + j] + carry;
            if (j < other.val.size())
                current += val[i] * other.val[j];
            result_val[i + j] = current % 10;
            carry = current / 10;
        }
    }

    pos = (pos == other.pos);
    val = result_val;
    trim();

    return *this;
}

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
    if (pos)
    {
        static const OmniInt llong_max(std::numeric_limits<long long>::max());
        if (*this > llong_max)
        {
            throw std::overflow_error("OmniInt value too large for long long");
        }
    }
    else
    {
        static const OmniInt llong_min(std::numeric_limits<long long>::min());
        if (*this < llong_min)
        {
            throw std::overflow_error("OmniInt value too small for long long");
        }
    }
    long long result = 0;
    for (int i = val.size() - 1; i >= 0; --i)
    {
        result = result * 10 + val[i];
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

// === 改进 1: 实现高效的除法与取模辅助函数 ===
std::pair<OmniInt, OmniInt> OmniInt::divide_and_remainder(const OmniInt &divisor) const
{
    if (divisor.val.size() == 1 && divisor.val[0] == 0)
    {
        throw std::runtime_error("Division by zero");
    }
    if (abs() < divisor.abs())
    {
        // 被除数绝对值小于除数绝对值，商为0，余数为被除数本身
        return {OmniInt(0), *this};
    }

    OmniInt abs_this = abs();
    OmniInt abs_divisor = divisor.abs();

    OmniInt quotient;
    OmniInt current_remainder;
    quotient.val.assign(val.size(), 0);

    for (int i = val.size() - 1; i >= 0; --i)
    {
        current_remainder = current_remainder * 10 + val[i];

        // 商的这一位最大可能为9
        int digit = 0;
        while (current_remainder >= abs_divisor)
        {
            current_remainder -= abs_divisor;
            digit++;
        }
        quotient.val[i] = digit;
    }

    quotient.trim();
    quotient.pos = (pos == divisor.pos);
    if (quotient.val.size() == 1 && quotient.val[0] == 0)
    {
        quotient.pos = true; // 规范化0
    }

    // 计算最终余数
    // Remainder = Dividend - Quotient * Divisor
    // 符号与被除数相同
    OmniInt remainder = *this - quotient * divisor;

    return {quotient, remainder};
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
    if (pos != other.pos)
    {
        return pos ? 1 : -1;
    }

    if (val.size() == 1 && val[0] == 0 && other.val.size() == 1 && other.val[0] == 0)
    {
        return 0;
    }

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
// Non-Member Arithmetic Operators (for long long on LHS) - 非成员算术运算符
// =========================================================================

/**
 * @brief 非成员加法运算符，处理 long long 在左边的情况。
 */
inline OmniInt operator+(long long lhs, const OmniInt &rhs)
{
    return OmniInt(lhs) + rhs;
}

/**
 * @brief 非成员减法运算符，处理 long long 在左边的情况。
 */
inline OmniInt operator-(long long lhs, const OmniInt &rhs)
{
    return OmniInt(lhs) - rhs;
}

/**
 * @brief 非成员乘法运算符，处理 long long 在左边的情况。
 */
inline OmniInt operator*(long long lhs, const OmniInt &rhs)
{
    return OmniInt(lhs) * rhs;
}

/**
 * @brief 非成员除法运算符，处理 long long 在左边的情况。
 */
inline OmniInt operator/(long long lhs, const OmniInt &rhs)
{
    return OmniInt(lhs) / rhs;
}

/**
 * @brief 非成员取模运算符，处理 long long 在左边的情况。
 */
inline OmniInt operator%(long long lhs, const OmniInt &rhs)
{
    return OmniInt(lhs) % rhs;
}

// =========================================================================
// Non-Member Functions - 非成员函数
// =========================================================================

std::ostream &operator<<(std::ostream &os, const OmniInt &n)
{
    os << n.toString();
    return os;
}

std::istream &operator>>(std::istream &is, OmniInt &n)
{
    std::string s;
    if (is >> s)
    { // 检查流状态
        try
        {
            n = s;
        }
        catch (const std::invalid_argument &)
        {
            // 如果字符串无效，设置流状态为 failbit
            is.setstate(std::ios_base::failbit);
        }
    }
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

    // === 最终性能与正确性修正: 高效地计算一个可靠的过高初始值 ===
    // 1. 获取 n 的位数 d。
    size_t digits = n.digitCount();

    // 2. 一个有 d 位数的 n，其平方根的位数是 (d+1)/2。
    //    因此，10^((d+1)/2) 在数学上必然是一个比 sqrt(n) 大的数。
    //    这个初始值的计算非常快，只涉及整数算术和字符串操作，避免了任何高精度运算。
    size_t guess_exponent = (digits + 1) / 2;
    std::string initial_guess_str(guess_exponent + 1, '0');
    initial_guess_str[0] = '1';

    OmniInt x = initial_guess_str;

    // 3. 由于初始值 x 现在保证是过高估计，迭代序列将稳定地单调递减。
    //    下面的 do-while 循环是正确且高效的。
    OmniInt last_x;
    do
    {
        last_x = x;
        x = (x + n / x) / 2;
    } while (x < last_x);

    // 4. 循环结束后，last_x 是我们需要的整数平方根（向下取整）。
    x = last_x;

    // 5. 最后的安全检查，处理可能的 off-by-one 错误。
    if (x * x > n)
    {
        x -= 1;
    }

    return x;
}
#endif // OmniInt_H