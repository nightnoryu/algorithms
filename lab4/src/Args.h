#pragma once

#include "common_inc.h"

struct Args
{
    std::string inputFilename;
    int from;
    int to;
};

Args parseArgs(int argc, char** argv);
