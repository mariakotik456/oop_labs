#include <iostream>
#include <memory>
#include <limits>
#include "../include/functions.h"

void displayMenu()
{
    std::cout << "\n=== Figure Management System ===" << std::endl;
    std::cout << "1. Add Triangle" << std::endl;
    std::cout << "2. Add Square" << std::endl;
    std::cout << "3. Add Rectangle" << std::endl;
    std::cout << "4. Remove Figure by Index" << std::endl;
    std::cout << "5. Print All Figures" << std::endl;
    std::cout << "6. Calculate Total Area" << std::endl;
    std::cout << "7. Clear All Figures" << std::endl;
    std::cout << "8. Demo with different types" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Choose an option: ";
}

void demoDifferentTypes()
{
    std::cout << "\n=== Demo with different types ===" << std::endl;

    // Демонстрация работы с int
    std::cout << "Integer types demo:" << std::endl;
    Array<std::shared_ptr<Figure<int>>> intFigures;
    intFigures.push_back(std::make_shared<Triangle<int>>(
        Point<int>(0, 0), Point<int>(4, 0), Point<int>(2, 3)));
    intFigures.push_back(std::make_shared<Square<int>>(Point<int>(2, 2), 4));
    printAllFiguresInfo(intFigures);
    std::cout << "Total area: " << calculateTotalArea(intFigures) << std::endl;

    // Демонстрация работы с double
    std::cout << "\nDouble types demo:" << std::endl;
    Array<std::shared_ptr<Figure<double>>> doubleFigures;
    doubleFigures.push_back(std::make_shared<Triangle<double>>(
        Point<double>(0.0, 0.0), Point<double>(4.0, 0.0), Point<double>(2.0, 3.0)));
    doubleFigures.push_back(std::make_shared<Square<double>>(Point<double>(2.5, 2.5), 4.5));
    printAllFiguresInfo(doubleFigures);
    std::cout << "Total area: " << calculateTotalArea(doubleFigures) << std::endl;
}

int main()
{
    Array<std::shared_ptr<Figure<double>>> figures;
    int choice;

    do
    {
        displayMenu();
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            try
            {
                auto triangle = createTriangle<double>();
                figures.push_back(triangle);
                std::cout << "Triangle added successfully!" << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        }

        case 2:
        {
            try
            {
                auto square = createSquare<double>();
                figures.push_back(square);
                std::cout << "Square added successfully!" << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        }

        case 3:
        {
            try
            {
                auto rectangle = createRectangle<double>();
                figures.push_back(rectangle);
                std::cout << "Rectangle added successfully!" << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        }

        case 4:
        {
            if (figures.empty())
            {
                std::cout << "Array is empty!" << std::endl;
                break;
            }

            std::cout << "Enter index to remove (0-" << figures.size() - 1 << "): ";
            size_t index;
            std::cin >> index;

            try
            {
                figures.remove(index);
                std::cout << "Figure removed successfully!" << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        }

        case 5:
        {
            if (figures.empty())
            {
                std::cout << "Array is empty!" << std::endl;
            }
            else
            {
                printAllFiguresInfo(figures);
            }
            break;
        }

        case 6:
        {
            double total = calculateTotalArea(figures);
            std::cout << "Total area of all figures: " << total << std::endl;
            break;
        }

        case 7:
        {
            figures.clear();
            std::cout << "All figures cleared!" << std::endl;
            break;
        }

        case 8:
        {
            demoDifferentTypes();
            break;
        }

        case 0:
            std::cout << "Goodbye!" << std::endl;
            break;

        default:
            std::cout << "Invalid option! Please try again." << std::endl;
            break;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (choice != 0);

    return 0;
}