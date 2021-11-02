#include "Args.h"

std::optional<std::string> getInputFilename(int argc, char** argv)
{
    if (argc >= 2)
    {
        return std::string(argv[1]);
    }

    return std::nullopt;
}
