#include "args.h"

size_t str_to_positive_int(const std::string& str)
{
  size_t value;
  try {
    value = std::stoi(str);
  } catch (std::exception& e) {
    value = std::string::npos;
  }

  return value < 0 ? std::string::npos : value;
}

struct args_type input_args(int argc, char **argv)
{
  struct args_type args;
  if (argc == 5) {
    args.input_filename = std::string(argv[1]);

    args.output_filename = std::string(argv[2]);

    args.width = str_to_positive_int(argv[3]);
    if (args.width == std::string::npos) {
      return args;
    }

    args.first_line_indent = str_to_positive_int(argv[4]);
    if (args.first_line_indent == std::string::npos) {
      return args;
    }
  } else {
    std::cout << "Enter input filename: ";
    getline(std::cin, args.input_filename);

    std::cout << "Enter output filename: ";
    getline(std::cin, args.output_filename);

    std::cout << "Enter text width: ";
    std::cin >> args.width;
    if (std::cin.fail()) {
      args.width = std::string::npos;
      return args;
    }

    std::cout << "Enter first line indent: ";
    std::cin >> args.first_line_indent;
    if (std::cin.fail()) {
      args.first_line_indent = std::string::npos;
      return args;
    }
  }

  return args;
}
