/*
 * lab4
 *
 *    19. Имеется  сеть  автомобильных  дорог.  Для каждой дороги
 * известна максимальная масса груза, которую можно  провезти  по 
 * этой   дороге.   С   помощью  алгоритма  Дейкстры   определить 
 * максимальный   груз,   который  можно  провезти  между   двумя 
 * указанными городам (10).

 * Выполнил:
 * Хафизов Булат, ПС-21
 *
 * Среда выполнения: cmake, g++
 * Сборка проекта: в корневой директории выполнить команды:
 *   cmake -G "MSYS Makefiles" .
 *   cmake --build .
 * (вместо последней команды можно просто make)
 * Убедиться, что присутствует cmake, MinGW, MSYS и компилятор g++.
 */

#include "common_inc.h"
#include "GraphParser.h"
#include "MaxWeightFinder.h"

int main(int argc, char** argv)
{
    std::string path;
    if (argc >= 2)
    {
        path = argv[1];
    }
    else
    {
        std::cout << "Enter graph file name: ";
        std::cin >> path;
    }

    std::ifstream input(path);
    if (!input.is_open())
    {
        std::cerr << "ERROR: failed to open input file for reading" << std::endl;
        std::exit(1);
    }

    GraphParser parser;

    try
    {
        auto graph = parser.parseFromStream(input);
        for (auto const& row : graph)
        {
            for (auto const& cell : row)
            {
                std::cout << cell << ' ';
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "\nERROR: " << e.what() << std::endl;
        exit(1);
    }
}
