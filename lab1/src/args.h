#ifndef ARGS_H
#define ARGS_H

#define MAXFILENAME 256

struct args_type {
  char input_filename[MAXFILENAME];
  char output_filename[MAXFILENAME];
  int width;
  int first_line_indent;
};

struct args_type
input_args(int argc, char **argv);

#endif /* #ifndef ARGS_H */
