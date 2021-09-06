/*
 * justificatice (justification + justice)
 * Выравнивание параграфа текста по ширине
 */

#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"

#define MAXLINE 1000

typedef unsigned int uint;

uint
find_longest_line(FILE *file)
{
  long post = ftell(file);
  rewind(file);

  char c;
  uint current_length, longest_length;
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
insert_spaces(char *line, uint amount)
{
  char blanks[amount+1];
  for (uint i = 0; i < amount; ++i) {
    blanks[i] = ' ';
  }
  blanks[amount] = '\0';

  int last_blank_index = reverse_find(line, ' ');
  if (last_blank_index != -1) {
    insert_in_str(line, blanks, last_blank_index);
  }
}

int
main(void)
{
  char filename[MAXLINE];
  printf("Enter filename: ");
  read_line(filename, MAXLINE, stdin);

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file for reading");
    return EXIT_FAILURE;
  }

  char line[MAXLINE];
  uint longest_length = find_longest_line(file);
  uint line_length;

  while (read_line(line, MAXLINE, file)) {
    line_length = str_len(line);
    if (line_length < longest_length) {
      insert_spaces(line, longest_length - line_length);
    }
    puts(line);
  }

  return EXIT_SUCCESS;
}
