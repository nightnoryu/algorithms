/*
 * lab1
 * justificatice (justification + justice)
 * Выравнивание текста по ширине
 */

#include "args.h"
#include "utils.h"

#define MAXLINE 1000
#define MAXWORD 100

void
insert_in_str(char *dest, char const *str, int index)
{
  char tmp[MAXLINE];
  str_ncpy(tmp, dest, index);
  tmp[index] = '\0';
  str_cat(tmp, str);
  str_cat(tmp, dest + index);
  str_cpy(dest, tmp);
}

void
insert_spaces(char *line, int max_line)
{
  if (find(line, ' ', 0) == -1) {
    return;
  }
  int pos = find_first_not_of(line, ' ', 0);
  while (str_len(line) < max_line) {
    pos = find(line, ' ', pos);
    if (pos != -1) {
      insert_in_str(line, " ", pos);
      pos = find_first_not_of(line, ' ', pos+1);
    } else {
      pos = 0;
    }
  }
}

void
prepend_first_line_indent(char *line, int amount)
{
  char *indentation = (char *) malloc(amount);
  int i = 0;
  while (i < amount - 1) {
    indentation[i++] = ' ';
  }
  indentation[i] = '\0';

  str_cpy(line, indentation);
  free(indentation);
}

int
main(int argc, char **argv)
{
  setlocale(LC_ALL, "Russian");

  struct args_type args = input_args(argc, argv);

  FILE *input = fopen(args.input_filename, "r");
  if (input == NULL) {
    perror("Error opening input file for reading");
    return EXIT_FAILURE;
  }

  FILE *output = fopen(args.output_filename, "w");
  if (output == NULL) {
    perror("Error opening output file for reading");
    fclose(input);
    return EXIT_FAILURE;
  }

  char word[MAXWORD];
  char line[MAXLINE];
  int word_length, line_length = args.first_line_indent;
  prepend_first_line_indent(line, args.first_line_indent);

  while ((word_length = read_word(word, MAXWORD, input)) > 0) {
    if ((line_length + word_length + 1) <= args.width) {
      if (line_length > 0) {
        str_cat(line, " ");
        line_length += 1;
      }
      str_cat(line, word);
      line_length += word_length;
    } else {
      if (line_length < args.width && !feof(input)) {
        insert_spaces(line, args.width);
        line_length = args.width;
      }
      fprintf(output, "%s\n", line);
      str_cpy(line, word);
      line_length = word_length;
    }
  }

  if (line_length > 0) {
    fprintf(output, "%s\n", line);
  }

  fclose(input);
  fclose(output);
  return EXIT_SUCCESS;
}