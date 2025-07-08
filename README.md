# OmniInt - C++ 高精度整数库

## 简介

OmniInt 是一个强大的 C++ 头文件库，专为处理任意大小的整数计算而设计，超越了标准数据类型（如 long long）的限制。无论是科学计算、密码学、数学问题还是其他需要大数运算的场景，OmniInt 都能提供稳定、高效且易用的解决方案。

这个库通过模拟手算的方式实现，将大整数存储为数字向量，并重载了常见的算术、关系以及流运算符，让 OmniInt 对象可以像普通整数一样使用。

## 主要特性

- **任意精度整数**：支持理论上无限大的整数。
- **全面的数学运算**：
  - 加法 (+, +=)
  - 减法 (-, -=)
  - 乘法 (*, *=)
  - 除法 (/, /=)
  - 取模 (%, %=)
  - 取反 (- 一元运算符)
  - 自增 (++ 前缀/后缀)
  - 自减 (-- 前缀/后缀)
- **灵活的构造与赋值**：支持从 long long 和 std::string 进行构造和赋值。
- **关系运算符**：支持所有标准的关系比较 (<, >, <=, >=, ==, !=)。
- **类型转换**：可转换为 long long (带溢出检查) 和 std::string。
- **流操作**：通过 std::cout 和 std::cin 直接进行输入输出。
- **整数平方根**：提供 sqrt() 函数计算大数的整数平方根（使用牛顿迭代法）。
- **错误处理**：对除零、无效字符串格式、负数平方根和 long long 转换溢出等情况抛出标准异常。

## 如何使用

OmniInt 是一个头文件库（header-only library），这意味着您无需编译额外的 .cpp 文件。只需将 InfInt.h 文件（请注意：您需要将文件名从 InfInt.h 重命名为 OmniInt.h 以与新名称保持一致）包含到您的 C++ 项目中即可开始使用。

### 1. 包含头文件

将 OmniInt.h 文件复制到您的项目目录中，然后在您的 C++ 源文件中包含它：

```cpp
#include "OmniInt.h"
```

### 2. 编译要求

OmniInt 库使用了一些现代 C++ 特性，建议使用 C++11 或更高版本的编译器进行编译（例如 GCC 5+ 或 Clang 3.4+）。

编译命令示例 (使用 g++):

```bash
g++ your_program.cpp -o your_program -std=c++11 # 或 -std=c++14, -std=c++17, -std=c++20
```

### 3. 基本用法示例

```cpp
#include "OmniInt.h" // 本项目头文件
#include <iostream>
#include <string>
#include <stdexcept> // 用于捕获异常

int main() {
    // 构造 OmniInt 对象
    OmniInt num1("12345678901234567890"); // 从字符串构造
    OmniInt num2(54321);                 // 从 long long 构造
    OmniInt num3 = num1 + num2;          // 加法运算

    std::cout << "num1: " << num1 << std::endl;
    std::cout << "num2: " << num2 << std::endl;
    std::cout << "num1 + num2 = " << num3 << std::endl;

    // 乘法和除法
    OmniInt product = num1 * num2;
    std::cout << "num1 * num2 = " << product << std::endl;

    // 平方根计算
    OmniInt large_num_for_sqrt("98765432109876543210");
    try {
        OmniInt result_sqrt = sqrt(large_num_for_sqrt); // sqrt函数仍然返回OmniInt
        std::cout << "sqrt(" << large_num_for_sqrt << ") = " << result_sqrt << std::endl;
    } catch (const std::domain_error& e) {
        std::cerr << "Error calculating square root: " << e.what() << std::endl;
    }

    // 异常处理示例 (除零)
    OmniInt zero(0);
    try {
        OmniInt division_by_zero = num1 / zero; // 这会抛出异常
        std::cout << "Result of division by zero: " << division_by_zero << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // 其他操作
    OmniInt counter(10);
    std::cout << "Counter initially: " << counter << std::endl;
    counter++;
    std::cout << "Counter after increment: " << counter << std::endl;
    counter -= 5;
    std::cout << "Counter after decrement: " << counter << std::endl;

    return 0;
}
```

## 错误处理

OmniInt 库在遇到无效操作或参数时会抛出标准异常：

- `std::invalid_argument`: 当从无效字符串构造或赋值 OmniInt 时。
- `std::runtime_error`: 当执行除零或模零操作时。
- `std::domain_error`: 当尝试计算负数的平方根时。
- `std::overflow_error`: 当 toLongLong() 方法转换的值超出 long long 的范围时。

强烈建议在使用这些可能引发异常的函数时，使用 try-catch 块进行错误处理。

## 许可证

本项目遵循 MIT 许可证。详见 LICENSE 文件

## 贡献

欢迎任何形式的贡献，包括错误报告、功能请求和代码优化。如果您想贡献，请：

1. Fork 本仓库。
2. 创建您的功能分支 (`git checkout -b feature/AmazingFeature`)。
3. 提交您的更改 (`git commit -m 'Add some AmazingFeature'`)。
4. 推送到分支 (`git push origin feature/AmazingFeature`)。
5. 打开一个 Pull Request。

## 鸣谢

感谢所有为开源社区做出贡献的开发者和项目。

Copyright(C) 2025 SharkyMew
