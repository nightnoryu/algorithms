/*
 * lab5
 *
 *    20. Имеется N костей игры домино. На каждой кости имеется 2    TODO: adjust number
 * числа (каждое от 0 до 6). Требуется написать программу, которая
 * будет определять максимальное число, составленное из  цифр  на
 * костях цепочки, составленной по правилам домино  из  имеющихся
 * костей.
 *    Ввод. Первая строка входного файла содержит целое число N –
 * количество костей (2 <= N <= 10). Следующие N строк содержат 2
 * целых числа X и Y (0 <= X, Y <= 6), разделенные пробелом.
 *    Вывод. В выходной файл необходимо вывести максимальное целое
 * число, цифры которого соответствуют значению костей в цепочке(13).
 *    Примеры
 * Ввод 1         Ввод 2         Ввод 3
 * 3              2              5
 * 1 6            6 6            1 5
 * 0 0            3 6            3 4
 * 2 5                           4 1
 *                               1 6
 *                               1 0
 * Вывод 1        Вывод 2        Вывод 3
 * 61             6663           611443
 *
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
#include "DominoParser.h"
#include "MaxNumberFinder.h"
#include "common_inc.h"

int main(int argc, char** argv)
{
    std::ifstream input;
    const auto inputFilename = getInputFilename(argc, argv);
    if (inputFilename.has_value())
    {
        input.open(inputFilename.value());
        if (!input.is_open())
        {
            std::cerr << "ERROR: failed to open input file for reading" << std::endl;
            std::exit(1);
        }
    }
    else
    {
        input.copyfmt(std::cin);
        input.clear(std::cin.rdstate());
        input.basic_ios<char>::rdbuf(std::cin.rdbuf());
    }

    try
    {
        const auto dominos = DominoParser::parseFromStream(input);
        const auto max = MaxNumberFinder::findMaxNumber(dominos);
        std::cout << "MAX NUMBER: " << max << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
}
