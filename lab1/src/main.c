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
  char filename[MAXLINE];
  int width;

  printf("Enter input filename: ");
  read_line(filename, MAXLINE, stdin);
  FILE *input = fopen(filename, "r");
  if (input == NULL) {
    perror("Error opening input file for reading");
    return EXIT_FAILURE;
  }

  printf("Enter output filename: ");
  read_line(filename, MAXLINE, stdin);
  FILE *output = fopen(filename, "w");
  if (output == NULL) {
    perror("Error opening output file for reading");
    fclose(input);
    return EXIT_FAILURE;
  }

  printf("Enter text width: ");
  scanf("%d", &width);

  char word[MAXWORD];
  char line[MAXLINE];
  int word_length, line_length = 0;
  str_cpy(line, "");

  while (read_word(word, MAXWORD, input)) {
    word_length = str_len(word);

    if ((line_length + word_length + 1) <= width) {
      if (line_length > 0) {
        str_cat(line, " ");
        line_length += 1;
      }
      str_cat(line, word);
      line_length += word_length;
    } else {
      if (line_length < width && !feof(input)) {
        insert_spaces(line, width);
        line_length = width;
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
