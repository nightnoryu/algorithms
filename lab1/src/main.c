/*
 * justificatice (justification + justice)
 * Выравнивание параграфа текста по ширине
 */

#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"

#define MAXLINE 1000

int
find_longest_line(FILE *file)
{
  long post = ftell(file);
  rewind(file);

  char c;
  int current_length, longest_length;
  current_length = longest_length = 0;

  while ((c = fgetc(file)) != EOF) {
    ++current_length;
    if (c == '\n') {
      --current_length;
      if (current_length > longest_length) {
        longest_length = current_length;
      }
      current_length = 0;
    }
  }

  fseek(file, post, SEEK_SET);
  return longest_length;
}

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
  int pos;
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

int
main(void)
{
  setlocale(LC_ALL, "Russian");

  char filename[MAXLINE];
  printf("Enter filename: ");
  read_line(filename, MAXLINE, stdin);

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file for reading");
    return EXIT_FAILURE;
  }

  char line[MAXLINE];
  int longest_length = find_longest_line(file);
  int line_length;

  while (read_line(line, MAXLINE, file)) {
    line_length = str_len(line);
    if (line_length < longest_length) {
      insert_spaces(line, longest_length);
    }
    puts(line);
  }

  fclose(file);
  return EXIT_SUCCESS;
}
