#ifndef ARGS_H
#define ARGS_H

#include "utils.h"

#define MAXFILENAME 256

struct args_type {
  std::string input_filename;
  std::string output_filename;
  int width;
  int first_line_indent;
};

struct args_type
input_args(int argc, char **argv);

#endif /* #ifndef ARGS_H */
