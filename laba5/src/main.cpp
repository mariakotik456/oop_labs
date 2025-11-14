#include "block_tracking_memory_resource.h"
#include "dynamic_array.h"
#include <iostream>
#include <string>

struct Person
{
    std::string name;
    int age;
    double salary;

    Person(const std::string &n, int a, double s) : name(n), age(a), salary(s) {}

    friend std::ostream &operator<<(std::ostream &os, const Person &p)
    {
        os << "Person{name='" << p.name << "', age=" << p.age << ", salary=" << p.salary << "}";
        return os;
    }
};

void demonstrate_simple_type()
{
    std::cout << "1. Демонстрация с простым типом (int):\n";

    BlockTrackingMemoryResource memory_resource;

    DynamicArray<int> int_array{std::pmr::polymorphic_allocator<int>(&memory_resource)};

    std::cout << "Добавляем элементы: ";
    for (int i = 0; i < 5; ++i)
    {
        int_array.push_back(i * 10);
        std::cout << i * 10 << " ";
    }
    std::cout << "\n";

    std::cout << "Содержимое через итератор: ";
    for (auto it = int_array.begin(); it != int_array.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "Удаляем два элемента...\n";
    int_array.pop_back();
    int_array.pop_back();

    std::cout << "Содержимое после удаления: ";
    for (const auto &elem : int_array)
    {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    std::cout << "Статистика memory_resource: allocated="
              << memory_resource.get_allocated_blocks_count()
              << ", free=" << memory_resource.get_free_blocks_count() << "\n\n";
}

void demonstrate_complex_type()
{
    std::cout << "2. Демонстрация со сложным типом (struct):\n";

    BlockTrackingMemoryResource memory_resource;

    DynamicArray<Person> people{std::pmr::polymorphic_allocator<Person>(&memory_resource)};

    people.push_back(Person("Alice", 30, 50000.0));
    people.push_back(Person("Bob", 25, 45000.0));
    people.push_back(Person("Charlie", 35, 60000.0));

    std::cout << "Содержимое массива людей:\n";
    for (auto it = people.begin(); it != people.end(); ++it)
    {
        std::cout << "  " << *it << "\n";
    }

    std::cout << "Доступ по индексу: " << people[1] << "\n";

    std::cout << "Статистика memory_resource: allocated="
              << memory_resource.get_allocated_blocks_count()
              << ", free=" << memory_resource.get_free_blocks_count() << "\n\n";
}

void demonstrate_memory_reuse()
{
    std::cout << "3. Демонстрация повторного использования памяти:\n";

    BlockTrackingMemoryResource memory_resource;

    DynamicArray<std::string> strings{std::pmr::polymorphic_allocator<std::string>(&memory_resource)};

    std::cout << "Создаем и удаляем строки для демонстрации переиспользования блоков...\n";

    strings.push_back("First string");
    strings.push_back("Second string");
    strings.push_back("Third string");

    std::cout << "Удаляем элементы...\n";
    strings.pop_back();
    strings.pop_back();

    std::cout << "Добавляем новые элементы (должны переиспользовать память)...\n";
    strings.push_back("Reused block 1");
    strings.push_back("Reused block 2");

    std::cout << "Финальная статистика memory_resource: allocated="
              << memory_resource.get_allocated_blocks_count()
              << ", free=" << memory_resource.get_free_blocks_count() << "\n";
}

int main()
{
    std::cout << "=== Демонстрация DynamicArray с BlockTrackingMemoryResource ===\n\n";

    demonstrate_simple_type();
    demonstrate_complex_type();
    demonstrate_memory_reuse();

    std::cout << "\n=== Демонстрация завершена ===\n";

    return 0;
}