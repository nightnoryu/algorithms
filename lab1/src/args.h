#ifndef ARGS_H
#define ARGS_H

#include <iostream>
#include <string>

struct args_type {
  std::string input_filename;
  std::string output_filename;
  size_t width;
  size_t first_line_indent;
};

struct args_type input_args(int argc, char **argv);

#endif /* #ifndef ARGS_H */
