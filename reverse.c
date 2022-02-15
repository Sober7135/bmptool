#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;

int main(int argc, char* argv[]) {
  if (argc == 1) {
    fprintf(stderr, "missing file operand\n");
    exit(EXIT_FAILURE);
  } else if (argc == 2) {
    fprintf(stderr, "missing destination file operand after '%s'\n", argv[1]);
    exit(EXIT_FAILURE);
  } else if (argc > 3) {
    exit(EXIT_FAILURE);
  }

  FILE* fp_r;
  FILE* fp_w;
  BYTE rgb;
  int offset = 0, i = 0;
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

  // 读取像素区偏移量
  fseek(fp_r, 10, SEEK_SET);
  fread(&offset, 4, 1, fp_r);

  // 复制前面的部分
  fseek(fp_r, 0, SEEK_SET);
  while (i < offset && fread(&rgb, 1, 1, fp_r)) {
    fwrite(&rgb, 1, 1, fp_w);
    rgb = 0;
    i++;
  }

  // 反转
  while (fread(&rgb, 1, 1, fp_r)) {
    rgb ^= 0xff;
    fwrite(&rgb, 1, 1, fp_w);
  }
  fclose(fp_r);
  fclose(fp_w);
}