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
 * Среда выполнения: make, g++
 * Сборка проекта: в корневой директории выполнить команду make.
 * Убедиться, что присутствует компилятор g++.
 */

#include "InfixToPostfixParser.h"
#include "ParseLogger.h"

int main(int argc, char **argv)
{
  ParseLogger logger(256);
  InfixToPostfixParser parser(logger);

  try {

    std::string expression = parser.parseFromStream(std::cin);
    logger.dumpLogToStream(std::cout);
    std::cout << std::endl;
    std::cout << "RESULT:" << std::endl << expression << std::endl;

  } catch (std::exception& e) {
    std::cout << "error: " << e.what() << std::endl;
    std::exit(1);
  }
}
