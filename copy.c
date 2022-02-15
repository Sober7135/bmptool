#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE;

int main(int argc, char* argv[]) {
  if (argc == 1) {
    fprintf(stderr, "missing file operand\n");
    exit(EXIT_FAILURE);
  } else if (argc == 2) {
    fprintf(stderr, "missing destination file operand after '%s'", argv[1]);
    exit(EXIT_FAILURE);
  } else if (argc > 3) {
    exit(EXIT_FAILURE);
  }

  FILE* fp_r;
  FILE* fp_w;
  BYTE rgb;
  fp_r = fopen(argv[1], "rb");
  fp_w = fopen(argv[2], "wb");
  if (!fp_r) {
    fprintf(stderr, "error in opening the target file\n");
    exit(EXIT_FAILURE);
  }
  if (!fp_w) {
    fprintf(stderr, "error in creating the new file \n");
    exit(EXIT_FAILURE);
  }

  while (fread(&rgb, 1, 1, fp_r)) {
    fwrite(&rgb, 1, 1, fp_w);
  }
  fclose(fp_r);
  fclose(fp_w);
  return 0;
}