/*
 * lab1
 * justificatice (justification + justice)
 * Выравнивание текста по ширине
 */

#include "args.h"
#include "utils.h"

void insert_spaces(std::string& line, size_t max_line)
{
  if (find(line, ' ', 0) == std::string::npos) {
    return;
  }

  size_t pos = find_first_not_of(line, ' ', 0);

  while (str_len(line) < max_line) {
    pos = find(line, ' ', pos);

    if (pos != std::string::npos) {
      insert_in_str(line, " ", pos);
      pos = find_first_not_of(line, ' ', pos+1);
    } else {
      pos = 0;
    }
  }
}

void prepend_first_line_indent(std::string& line, size_t amount)
{
  std::string indentation(amount - 1, ' ');
  line = indentation + line;
}

bool consists_of_spaces(const std::string& str)
{
  const char *c_str = str.c_str();
  for (int i = 0; c_str[i] != '\0'; ++i) {
    if (c_str[i] != ' ') {
      return false;
    }
  }
  return true;
}

int main(int argc, char **argv)
{
  std::setlocale(LC_ALL, "Russian");

  struct args_type args = input_args(argc, argv);
  if (args.width == std::string::npos || args.first_line_indent == std::string::npos) {
    std::cerr << "Invalid input\n";
    std::exit(1);
  }

  std::ifstream input(args.input_filename);
  if (!input.is_open()) {
    std::cerr << "Error opening file for reading\n";
    std::exit(1);
  }

  std::ofstream output(args.output_filename);
  if (!output.is_open()) {
    std::cerr << "Error opening file for writing\n";
    std::exit(1);
  }

  std::string word;
  std::string line;
  size_t word_length, line_length = args.first_line_indent;
  prepend_first_line_indent(line, args.first_line_indent);

  while (input >> word) {
    word_length = word.length();
    if ((line_length + word_length + 1) <= args.width) {
      if (line_length > 0) {
        line += ' ';
        line_length += 1;
      }
      line += word;
      line_length += word_length;
    } else {
      if (line_length < args.width && !input.eof()) {
        insert_spaces(line, args.width);
        line_length = args.width;
      }
      if (!consists_of_spaces(line)) {
        output << line << "\n";
      }
      line = word;
      line_length = word_length;
    }
  }

  if (line_length > 0) {
    output << line << "\n";
  }

  input.close();
  output.close();
}
