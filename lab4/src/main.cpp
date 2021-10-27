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

#include "Args.h"
#include "GraphParser.h"
#include "MaxWeightFinder.h"
#include "common_inc.h"

int main(int argc, char** argv)
{
    auto args = parseArgs(argc, argv);
    std::ifstream input;

    input.open(args.inputFilename);
    if (!input.is_open())
    {
        std::cerr << "ERROR: failed to open input file for reading" << std::endl;
        std::exit(1);
    }

    GraphParser parser;
    MaxWeightFinder finder;

    try
    {
        auto graph = parser.parseFromStream(input);
        auto maxWeight = finder.findPathWithMaxWeight(graph, args.from, args.to);

        std::cout << "MAX WEIGHT: " << maxWeight << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "\nERROR: " << e.what() << std::endl;
        exit(1);
    }
}
