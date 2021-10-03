/*
 * lab2
 * 
 * Текст задания:
 *   23. В строке текстового файла  задано  выражение  из  целых 
 * чисел и операций '+', '-', '*', '/', '^'.  Порядок  вычислений 
 * определяется приоритетом операций и круглыми скобками. Возможен
 * одноместный минус в начале  выражения  или  после  открывающей 
 * скобки. Преобразовать выражение в постфиксную  форму (алгоритм 
 * Дейкстры) и вычислить его значение. Показать этапы  выполнения
 * (11).
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
#include "ParseLogger.h"
#include "PostfixCalculator.h"

std::string readInitialExpression(std::istream& input)
{
    std::string result;
    std::getline(input, result);
    input.seekg(0, std::ios_base::beg);
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

    ParseLogger logger(stackSize);
    InfixToPostfixParser parser(stackSize, logger);
    PostfixCalculator calculator;

    try
    {

        std::string infix = readInitialExpression(input);
        std::string rpn = parser.parseFromString(infix);

        logger.dumpLogToStream(output);
        output << "\nINFIX: " << infix << std::endl;
        output << "RPN:   " << rpn << std::endl;

        double result = calculator.calculate(rpn);
        output << "\nRESULT: " << std::setprecision(3) << result << std::endl;
    }
    catch (std::exception& e)
    {
        output << "\nERROR: " << e.what() << std::endl;
        std::exit(1);
    }
}
