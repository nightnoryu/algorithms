#include "args.h"

size_t str_to_size(const std::string& str)
{
    size_t value;
    try
    {
        value = std::stoi(str);
    }
    catch (std::exception& e)
    {
        value = std::string::npos;
    }

    return value;
}

size_t read_size(std::istream& input)
{
    size_t value;
    input >> value;
    if (input.fail())
    {
        value = std::string::npos;
    }

    return value;
}

struct args_type input_args(int argc, char** argv)
{
    struct args_type args;
    if (argc == 5)
    {
        args.input_filename = std::string(argv[1]);

        args.output_filename = std::string(argv[2]);

        args.width = str_to_size(argv[3]);
        if (args.width == std::string::npos)
        {
            return args;
        }

        args.first_line_indent = str_to_size(argv[4]);
        if (args.first_line_indent == std::string::npos)
        {
            return args;
        }
    }
    else
    {
        std::cout << "Enter input filename: ";
        getline(std::cin, args.input_filename);

        std::cout << "Enter output filename: ";
        getline(std::cin, args.output_filename);

        std::cout << "Enter text width: ";
        args.width = read_size(std::cin);

        std::cout << "Enter first line indent: ";
        args.first_line_indent = read_size(std::cin);
    }

    return args;
}
