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

#include "GraphParser.h"
#include "MaxWeightFinder.h"
#include "common_inc.h"

void openFile(std::ifstream& input, int argc, char** argv)
{
    std::string filePath;
    if (argc >= 2)
    {
        filePath = argv[1];
    }
    else
    {
        std::cout << "Enter graph file name: ";
        std::cin >> filePath;
    }

    input.open(filePath);
    if (!input.is_open())
    {
        std::cerr << "ERROR: failed to open input file for reading" << std::endl;
        std::exit(1);
    }
}

int main(int argc, char** argv)
{
    std::ifstream input;
    openFile(input, argc, argv);

    int from, to;
    std::cout << "Enter departure city number: ";
    std::cin >> from;
    std::cout << "Enter destination city number: ";
    std::cin >> to;
    --from, --to;

    GraphParser parser;
    MaxWeightFinder finder;

    try
    {
        auto graph = parser.parseFromStream(input);
        int maxWeight = finder.findPathWithMaxWeight(graph, from, to);

        std::cout << "MAX WEIGHT: " << maxWeight << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "\nERROR: " << e.what() << std::endl;
        exit(1);
    }
}
