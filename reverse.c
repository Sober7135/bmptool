#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE* fp_r = fopen("image/example01.bmp", "r");     // 打开要反转的bmp文件
  FILE* fp_w = fopen("image/reverse_test.bmp", "w");  // 创建反转文件
  int rgb = 0, n = 0, i = 0;

  if (!fp_r) {
    fprintf(stderr, "error in opening the file!");
    exit(EXIT_FAILURE);
  }
  if (!fp_w) {
    fprintf(stderr, "error in opening the file!");
    exit(EXIT_FAILURE);
  }

  // 读取像素区偏移量
  fseek(fp_r, 10, SEEK_SET);
  fread(&n, 4, 1, fp_r);

  // 复制前面的部分
  fseek(fp_r, 0, SEEK_SET);
  while ( i < n && fread(&rgb, 1, 1, fp_r)) {
    fwrite(&rgb, 1, 1, fp_w);
    rgb = 0;
    i++;
  }

  // 反转
  while (fread(&rgb, 1, 1, fp_r)) {
    rgb ^= 0xff;
    fwrite(&rgb, 1, 1, fp_w);
    rgb = 0;
  }
  fclose(fp_r);
  fclose(fp_w);
}