#include "Args.h"

Args parseArgs(int argc, char** argv)
{
    std::string filePath;
    int from, to;

    if (argc >= 2)
    {
        filePath = argv[1];
    }
    else
    {
        std::cout << "Enter graph file name: ";
        std::cin >> filePath;
    }

    if (argc >= 3)
    {
        from = std::stoi(argv[2]);
    }
    else
    {
        std::cout << "Enter departure city number: ";
        std::cin >> from;
    }

    if (argc >= 4)
    {
        to = std::stoi(argv[3]);
    }
    else
    {
        std::cout << "Enter departure city number: ";
        std::cin >> to;
    }

    return { filePath, --from, --to };
}
