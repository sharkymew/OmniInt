/*
OmniInt.h

This is a header file for high-precision integer calculations.

This project is just for learning.

Copyright(c) 2025 SharkyMew

Version 1.6.0
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
#include <utility>

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
    friend OmniInt gcd(OmniInt a, OmniInt b);
    // =================================================================
    // Constructors - 构造函数
    // =================================================================
    OmniInt() noexcept;
    OmniInt(long long n);
    OmniInt(const std::string &s);
    OmniInt(const OmniInt &other);
    OmniInt(OmniInt &&other) noexcept;

    // =================================================================
    // Assignment Operators - 赋值运算符
    // =================================================================
    OmniInt &operator=(long long n);
    OmniInt &operator=(const std::string &s);
    OmniInt &operator=(const OmniInt &other);
    OmniInt &operator=(OmniInt &&other) noexcept;

    // =================================================================
    // Unary Arithmetic Operators - 一元算术运算符
    // =================================================================
    OmniInt operator-() const;

    // =================================================================
    // Binary Arithmetic Operators - 二元算术运算符
    // =================================================================
    OmniInt operator+(const OmniInt &other) const;
    OmniInt operator-(const OmniInt &other) const;
    OmniInt operator*(const OmniInt &other) const;
    OmniInt operator/(const OmniInt &other) const;
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
    OmniInt &operator++();
    OmniInt &operator--();
    OmniInt operator++(int);
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
    long long toLongLong() const;
    std::string toString() const;
    size_t digitCount() const;
    OmniInt abs() const;

    // === 辅助函数 ===
    bool is_zero() const;
    bool is_even() const;

private:
    std::vector<int> val; // 存储每一位数字，低位在前 (val[0] 是个位)
    bool pos;             // 符号位，true 为正数或零，false 为负数

    // 私有辅助函数
    std::pair<OmniInt, OmniInt> divide_and_remainder(const OmniInt &divisor) const;
    void trim();
    int compare(const OmniInt &) const;
    void halve_in_place();
};

// =========================================================================
// 实现
// =========================================================================

// --- 构造函数 ---
OmniInt::OmniInt() noexcept : pos(true)
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
    unsigned long long mag = (n > 0) ? n : -static_cast<unsigned long long>(n);
    while (mag > 0)
    {
        val.push_back(mag % 10);
        mag /= 10;
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
    if (is_zero())
    {
        pos = true;
    }
}

OmniInt::OmniInt(const OmniInt &other) : val(other.val), pos(other.pos) {}

OmniInt::OmniInt(OmniInt &&other) noexcept : val(std::move(other.val)), pos(other.pos)
{
    // 将源对象置于有效的空状态
    other.val.clear();
    other.val.push_back(0);
    other.pos = true;
}

// --- 赋值运算符 ---
OmniInt &OmniInt::operator=(long long n)
{
    // 直接调用构造函数和移动赋值，代码复用且安全
    *this = OmniInt(n);
    return *this;
}

OmniInt &OmniInt::operator=(const std::string &s)
{
    // 构造-移动惯用法
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

// --- 一元运算符 ---
OmniInt OmniInt::operator-() const
{
    if (is_zero())
    {
        return *this;
    }
    OmniInt result = *this;
    result.pos = !pos;
    return result;
}

// --- 二元运算符 (调用复合赋值实现) ---
OmniInt OmniInt::operator+(const OmniInt &other) const
{
    OmniInt result = *this;
    result += other;
    return result;
}

OmniInt OmniInt::operator-(const OmniInt &other) const
{
    OmniInt result = *this;
    result -= other;
    return result;
}

OmniInt OmniInt::operator*(const OmniInt &other) const
{
    OmniInt result = *this;
    result *= other;
    return result;
}

OmniInt OmniInt::operator/(const OmniInt &other) const
{
    return divide_and_remainder(other).first;
}

OmniInt OmniInt::operator%(const OmniInt &other) const
{
    return divide_and_remainder(other).second;
}

// --- 复合赋值运算符 (就地修改) ---
OmniInt &OmniInt::operator+=(const OmniInt &other)
{
    if (pos == other.pos)
    {
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
        *this -= (-other);
    }
    return *this;
}

OmniInt &OmniInt::operator-=(const OmniInt &other)
{
    if (pos != other.pos)
    {
        *this += (-other);
        return *this;
    }

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
    if (is_zero())
    {
        pos = true;
    }
    return *this;
}

OmniInt &OmniInt::operator*=(const OmniInt &other)
{
    // 处理任意一方为零的平凡情况
    if (this->is_zero() || other.is_zero())
    {
        *this = 0;
        return *this;
    }

    // 1. 准备阶段
    // 结果的符号由两个操作数的符号决定
    bool result_pos = (this->pos == other.pos);

    // 结果的位数最多是两个操作数位数之和，分配一个足够大的向量
    std::vector<int> result_val(this->val.size() + other.val.size(), 0);

    // 2. 纯乘法累加阶段
    //   - 遍历 this 的每一位 (val[i])
    //   - 遍历 other 的每一位 (other.val[j])
    //   - 将乘积 val[i] * other.val[j] 累加到 result_val 的第 i+j 位
    for (size_t i = 0; i < this->val.size(); ++i)
    {
        for (size_t j = 0; j < other.val.size(); ++j)
        {
            result_val[i + j] += this->val[i] * other.val[j];
        }
    }

    // 3. 进位处理阶段
    //   - 从低位到高位遍历 result_val
    //   - 将每一位的数字和来自前一位的进位相加
    //   - 更新当前位为 total % 10，并计算新的进位 total / 10
    int carry = 0;
    for (size_t i = 0; i < result_val.size(); ++i)
    {
        int total = result_val[i] + carry;
        result_val[i] = total % 10;
        carry = total / 10;
    }

    // 如果最高位还有进位，将其添加到向量末尾
    while (carry > 0)
    {
        result_val.push_back(carry % 10);
        carry /= 10;
    }

    // 4. 收尾阶段
    // 将计算好的结果更新到 this 对象
    this->val = result_val;
    this->pos = result_pos;

    // 调用 trim() 移除可能存在的前导零 (在 vector 中是尾部的零)
    // 这一步是必要的，因为我们预分配的 result_val 可能比实际结果长
    this->trim();

    return *this;
}

    OmniInt &OmniInt::operator/=(const OmniInt &other)
    {
        *this = *this / other;
        return *this;
    }

    OmniInt &OmniInt::operator%=(const OmniInt &other)
    {
        *this = *this % other;
        return *this;
    }

    // --- 自增自减 ---
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

    // --- 关系运算符 ---
    bool OmniInt::operator<(const OmniInt &other) const { return compare(other) == -1; }
    bool OmniInt::operator>(const OmniInt &other) const { return compare(other) == 1; }
    bool OmniInt::operator<=(const OmniInt &other) const { return compare(other) <= 0; }
    bool OmniInt::operator>=(const OmniInt &other) const { return compare(other) >= 0; }
    bool OmniInt::operator==(const OmniInt &other) const { return compare(other) == 0; }
    bool OmniInt::operator!=(const OmniInt &other) const { return compare(other) != 0; }

    // --- 其他成员函数 ---
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
        if (is_zero())
            return "0";
        std::stringstream ss;
        if (!pos)
            ss << '-';
        for (int i = val.size() - 1; i >= 0; --i)
        {
            ss << val[i];
        }
        return ss.str();
    }

    size_t OmniInt::digitCount() const
    {
        if (is_zero())
            return 1;
        return val.size();
    }

    OmniInt OmniInt::abs() const
    {
        OmniInt result = *this;
        result.pos = true;
        return result;
    }

    bool OmniInt::is_zero() const
    {
        return val.size() == 1 && val[0] == 0;
    }

    bool OmniInt::is_even() const
    {
        if (is_zero())
            return true;
        return val[0] % 2 == 0;
    }

    // --- 私有辅助函数实现 ---
    std::pair<OmniInt, OmniInt> OmniInt::divide_and_remainder(const OmniInt &divisor) const
    {
        if (divisor.is_zero())
        {
            throw std::runtime_error("Division by zero");
        }
        if (abs() < divisor.abs())
        {
            return {OmniInt(0), *this};
        }

        OmniInt abs_this = abs();
        OmniInt abs_divisor = divisor.abs();

        std::vector<OmniInt> multiples(10);
        for (int i = 1; i <= 9; ++i)
        {
            multiples[i] = abs_divisor * i;
        }

        std::vector<int> quotient_digits;
        OmniInt current_remainder = 0;

        for (int i = abs_this.val.size() - 1; i >= 0; --i)
        {
            current_remainder = current_remainder * 10 + abs_this.val[i];

            int low = 0, high = 9, digit = 0;
            while (low <= high)
            {
                int mid = (low + high) / 2;
                if (multiples[mid] <= current_remainder)
                {
                    digit = mid;
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }

            current_remainder -= multiples[digit];
            quotient_digits.push_back(digit);
        }

        OmniInt quotient;
        std::reverse(quotient_digits.begin(), quotient_digits.end());
        quotient.val = quotient_digits;
        quotient.trim();
        quotient.pos = (this->pos == divisor.pos);
        if (quotient.is_zero())
        {
            quotient.pos = true;
        }

        OmniInt remainder = current_remainder;
        remainder.pos = this->pos;
        if (remainder.is_zero())
        {
            remainder.pos = true;
        }

        return {quotient, remainder};
    }

    void OmniInt::trim()
    {
        while (val.size() > 1 && val.back() == 0)
        {
            val.pop_back();
        }
    }

    int OmniInt::compare(const OmniInt &other) const
    {
        if (pos != other.pos)
        {
            return pos ? 1 : -1;
        }
        if (is_zero() && other.is_zero())
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

    void OmniInt::halve_in_place()
    {
        if (is_zero())
            return;
        int carry = 0;
        for (int i = val.size() - 1; i >= 0; --i)
        {
            int current_val = val[i] + carry * 10;
            val[i] = current_val / 2;
            carry = current_val % 2;
        }
        trim();
    }

    // =========================================================================
    // Non-Member Functions - 非成员函数
    // =========================================================================

    // --- 外部运算符 (支持 long long 在左侧) ---
    inline OmniInt operator+(long long lhs, const OmniInt &rhs) { return OmniInt(lhs) + rhs; }
    inline OmniInt operator-(long long lhs, const OmniInt &rhs) { return OmniInt(lhs) - rhs; }
    inline OmniInt operator*(long long lhs, const OmniInt &rhs) { return OmniInt(lhs) * rhs; }
    inline OmniInt operator/(long long lhs, const OmniInt &rhs) { return OmniInt(lhs) / rhs; }
    inline OmniInt operator%(long long lhs, const OmniInt &rhs) { return OmniInt(lhs) % rhs; }

    // --- 流运算符 ---
    std::ostream &operator<<(std::ostream &os, const OmniInt &n)
    {
        os << n.toString();
        return os;
    }

    std::istream &operator>>(std::istream &is, OmniInt &n)
    {
        std::string s;
        if (is >> s)
        {
            try
            {
                n = s;
            }
            catch (const std::invalid_argument &)
            {
                // 如果构造失败，设置流的错误状态
                is.setstate(std::ios_base::failbit);
            }
        }
        return is;
    }

    // --- 数学函数 ---
    OmniInt sqrt(const OmniInt &n)
    {
        if (n < 0)
        {
            throw std::domain_error("Cannot compute square root of a negative number.");
        }
        if (n.is_zero())
        {
            return 0;
        }

        // 步骤 1: 构造一个绝对可靠的“过高”初始值 (overestimate)
        // 这是保证后续循环逻辑正确性的关键。
        // 一个 d 位数 n, 其 sqrt(n) 的位数是 ceil(d/2)。
        // 我们构造一个比结果多一位的数 10^ceil(d/2)，它必然大于真实的 sqrt(n)。
        size_t digits = n.digitCount();
        size_t root_exponent = (digits + 1) / 2;
        std::string guess_str(root_exponent + 1, '0');
        guess_str[0] = '1';
        OmniInt x(guess_str);

        // 步骤 2: 牛顿迭代。由于初始值 x 保证偏高，迭代序列将稳定单调递减。
        OmniInt last_x;
        do
        {
            last_x = x;
            x = (x + n / x) / 2;
        } while (x < last_x);

        // 步骤 3: 循环结束时，last_x 是最接近真实根的候选值
        x = last_x;

        // 步骤 4: 最终修正，防止因整数截断导致的 off-by-one 错误
        // 如果我们得到的 x 的平方大于 n，说明 x 偏大了1，需要减一。
        if (x * x > n)
        {
            x -= 1;
        }
        return x;
    }

    OmniInt gcd(OmniInt a, OmniInt b)
    {
        a = a.abs();
        b = b.abs();

        while (!b.is_zero())
        {
            OmniInt r = a % b;
            a = std::move(b);
            b = std::move(r);
        }

        return a;
    }

#endif // OmniInt_H
