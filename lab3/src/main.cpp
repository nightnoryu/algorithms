/*
 * lab3
 * 
 *   20. Имеется  некоторое  алгебраическое выражение.  Операнды
 * заданы идентификаторами,  операции выполняются по приоритетам,
 * допускается использование круглых скобок. Возможны одноместные
 * операции '+' и '-', а также операция возведения в степень '^'.
 * Требуется построить и выдать в наглядном виде бинарное дерево,
 * представляющее данное выражение (12).
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

#include "InfixToPostfixParser.h"
#include "common_inc.h"

std::string readInitialExpression(std::istream& input)
{
    std::string result;
    std::getline(input, result);
    return result;
}

void getInput(std::ifstream& input, int argc, char** argv)
{
    if (argc > 1)
    {
        input.open(argv[1]);
        if (!input.is_open())
        {
            std::cerr << "ERROR: failed to open input file" << std::endl;
            std::exit(1);
        }
    }
    else
    {
        input.copyfmt(std::cin);
        input.clear(std::cin.rdstate());
        input.basic_ios<char>::rdbuf(std::cin.rdbuf());
    }
}

void getOutput(std::ofstream& output, int argc, char** argv)
{
    if (argc > 2)
    {
        output.open(argv[2]);
        if (!output.is_open())
        {
            std::cerr << "ERROR: failed to open output file" << std::endl;
            std::exit(1);
        }
    }
    else
    {
        output.copyfmt(std::cout);
        output.clear(std::cout.rdstate());
        output.basic_ios<char>::rdbuf(std::cout.rdbuf());
    }
}

int main(int argc, char** argv)
{
    const size_t stackSize = 256;

    std::ifstream input;
    getInput(input, argc, argv);

    std::ofstream output;
    getOutput(output, argc, argv);

    InfixToPostfixParser parser(stackSize);
    // ExpressionTreeBuilder treeBuilder(stackSize);

    try
    {

        std::string infix = readInitialExpression(input);
        std::string postfix = parser.parseFromString(infix);

        output << "EXPRESSION: " << infix << std::endl;
        output << "BINARY EXPRESSION TREE:" << std::endl;
        // treeBuilder.buildTreeToStream(output, postfix);
    }
    catch (std::exception& e)
    {
        output << "\nERROR: " << e.what() << std::endl;
        std::exit(1);
    }
}
