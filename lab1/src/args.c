#include "args.h"
#include "utils.h"

struct args_type
input_args(int argc, char **argv)
{
  struct args_type args;
  if (argc == 4) {
    str_cpy(args.input_filename, argv[1]);
    str_cpy(args.output_filename, argv[2]);
    args.width = 70; // TODO
  } else {
    printf("Enter input filename: ");
    read_line(args.input_filename, MAXFILENAME, stdin);
    printf("Enter output filename: ");
    read_line(args.output_filename, MAXFILENAME, stdin);
    printf("Enter text width: ");
    scanf("%d", &args.width);
  }

  return args;
}
