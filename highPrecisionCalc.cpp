#include "OmniInt.h"
#include <iostream>
#include <string>
#include <stdexcept>

int main()
{
    // 构造 OmniInt 对象
    OmniInt num1("12345678901234567890"); // 从字符串构造
    OmniInt num2(54321);                  // 从 long long 构造
    OmniInt num3 = num1 + num2;           // 加法运算

    std::cout << "num1: " << num1 << std::endl;
    std::cout << "num2: " << num2 << std::endl;
    std::cout << "num1 + num2 = " << num3 << std::endl;

    // 乘法和除法
    OmniInt product = num1 * num2;
    std::cout << "num1 * num2 = " << product << std::endl;

    // 平方根计算
    OmniInt large_num_for_sqrt("98765432109876543210");
    try
    {
        OmniInt result_sqrt = sqrt(large_num_for_sqrt); // sqrt函数仍然返回OmniInt
        std::cout << "sqrt(" << large_num_for_sqrt << ") = " << result_sqrt << std::endl;
    }
    catch (const std::domain_error &e)
    {
        std::cerr << "Error calculating square root: " << e.what() << std::endl;
    }

    // 异常处理示例 (除零)
    OmniInt zero(0);
    try
    {
        OmniInt division_by_zero = num1 / zero; // 这会抛出异常
        std::cout << "Result of division by zero: " << division_by_zero << std::endl;
    }
    catch (const std::runtime_error &e)
    {
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