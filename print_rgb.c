// ./print_rgb a.bmp [x_coordinate] [y_coordinate]

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

// 以左下角为原点，水平方向为x轴
// 以BGR方式存储

int main(int argc, char* argv[]) {
  if (argc != 4) {
    fprintf(stderr, "no such option");
    exit(EXIT_FAILURE);
  }

  FILE* fp_r;
  RGB rgb;
  COORDINATE a;
  int offset = 0;    // 偏移量
  COORDINATE image;  // 图片的长宽

  // 获取要打印rgb的坐标
  a.x = strtol(argv[2], NULL, 10);
  a.y = strtol(argv[3], NULL, 10);

  fp_r = fopen(argv[1], "r");
  if (!fp_r) {
    fprintf(stderr, "error in opening the file");
    exit(EXIT_FAILURE);
  }

  fseek(fp_r, 10, SEEK_SET);
  fread(&offset, 1, 1, fp_r);  // 读取偏移量

  fseek(fp_r, 18, SEEK_SET);
  fread(&image.x, 4, 1, fp_r);  // 读取图像的长宽
  fread(&image.y, 4, 1, fp_r);

  // 检查有无超出坐标系
  if (a.x > image.x || a.y > image.y) {
    fprintf(stderr, "error in coordinate");
    exit(EXIT_FAILURE);
  }

  fseek(fp_r, offset + 3 * (a.y * image.x + a.x), SEEK_SET);
  fread(&rgb.B, 1, 1, fp_r);
  fread(&rgb.G, 1, 1, fp_r);
  fread(&rgb.R, 1, 1, fp_r);
  printf("R = %d\nG = %d\nB = %d", rgb.R, rgb.G, rgb.B);

  fclose(fp_r);
  return 0;
}