/*
 * lab1
 * justificatice (justification + justice)
 * Выравнивание текста по ширине
 */

#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"

#define MAXWORD 100
#define MAXLINE 1000

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
  int width;

  printf("Enter input filename: ");
  read_line(filename, MAXLINE, stdin);
  FILE *input = fopen(filename, "r");
  if (input == NULL) {
    perror("Error opening input file for reading");
    return EXIT_FAILURE;
  }

  printf("Enter text width: ");
  scanf("%d", &width);

  char word[MAXWORD];
  char line[MAXLINE];
  int word_length, line_length = 0;

  while (read_word(word, MAXWORD, input)) {
    word_length = str_len(word);

    if ((line_length + word_length + 1) <= width) {
      if (line_length > 0) {
        str_cat(line, " ");
      }
      str_cat(line, word);
      line_length += word_length + 1;
    } else {
      if (line_length < width) {
        insert_spaces(line, width);
        line_length = width;
      }
    }

    if (line_length == width || feof(input)) {
      puts(line);
      line_length = 0;
      str_cpy(line, "");
    }
  }

  fclose(input);
  return EXIT_SUCCESS;
}
