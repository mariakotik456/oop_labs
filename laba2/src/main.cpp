#include <iostream>
#include "../include/quinary_integer.h"

void demonstrateOperations()
{
    std::cout << "=== Демонстрация работы с QuinaryInteger ===\n"
              << std::endl;

    QuinaryInteger num1("132");
    QuinaryInteger num2("234");
    QuinaryInteger num3({2, 3, 1});

    std::cout << "Число 1: " << num1.toString() << "₅" << std::endl;
    std::cout << "Число 2: " << num2.toString() << "₅" << std::endl;
    std::cout << "Число 3: " << num3.toString() << "₅" << std::endl;

    std::cout << "\n=== Сравнение пятеричных чисел ===" << std::endl;
    std::cout << num1.toString() << "₅ == " << num3.toString() << "₅ : "
              << (num1.equals(num3) ? "true" : "false") << std::endl;
    std::cout << num1.toString() << "₅ < " << num2.toString() << "₅ : "
              << (num1.lessThan(num2) ? "true" : "false") << std::endl;
    std::cout << num2.toString() << "₅ > " << num1.toString() << "₅ : "
              << (num2.greaterThan(num1) ? "true" : "false") << std::endl;

    std::cout << "\n=== Арифметические операции в пятеричной системе ===" << std::endl;
    QuinaryInteger sum = num1.add(num2);
    std::cout << num1.toString() << "₅ + " << num2.toString() << "₅ = "
              << sum.toString() << "₅" << std::endl;

    QuinaryInteger diff = num2.subtract(num1);
    std::cout << num2.toString() << "₅ - " << num1.toString() << "₅ = "
              << diff.toString() << "₅" << std::endl;

    std::cout << "\n=== Копирование ===" << std::endl;
    QuinaryInteger copy = num1.copy();
    std::cout << "Копия числа 1: " << copy.toString() << "₅" << std::endl;
    std::cout << "Оригинал == Копия: " << (num1.equals(copy) ? "true" : "false") << std::endl;

    std::cout << "\n=== Операции с присваиванием ===" << std::endl;
    QuinaryInteger num4 = num1.copy();
    QuinaryInteger result = num4.addAssign(num2);
    std::cout << "После addAssign: " << result.toString() << "₅" << std::endl;
}

int main()
{
    try
    {
        demonstrateOperations();

        std::cout << "\n=== Интерактивный режим ===" << std::endl;
        std::string input1, input2;

        std::cout << "Введите первое пятеричное число (цифры 0-4): ";
        std::cin >> input1;

        std::cout << "Введите второе пятеричное число (цифры 0-4): ";
        std::cin >> input2;

        QuinaryInteger userNum1(input1);
        QuinaryInteger userNum2(input2);

        std::cout << "\nРезультаты:" << std::endl;
        std::cout << "Сумма: " << userNum1.add(userNum2).toString() << "₅" << std::endl;

        try
        {
            std::cout << "Разность: " << userNum2.subtract(userNum1).toString() << "₅" << std::endl;
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Разность: невозможно вычислить (результат отрицательный)" << std::endl;
        }

        std::cout << "Сравнение: " << userNum1.toString() << "₅ < " << userNum2.toString()
                  << "₅ = " << (userNum1.lessThan(userNum2) ? "true" : "false") << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}