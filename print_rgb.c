#include <stdio.h>
#include <stdlib.h>

// 以左下角为原点，水平方向为x轴
// 以BGR方式存储

typedef struct RGB {
  int R;
  int G;
  int B;
} RGB;

typedef struct coordinate {
  int x;
  int y;
} COORDINATE;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "no such option");
    exit(EXIT_FAILURE);
  }

  FILE* fp_r = fopen("image/duplicate_test.bmp", "r");
  RGB rgb;
  COORDINATE a;
  int n = 0;
  COORDINATE image;  // 长宽
  rgb.R = 0;
  rgb.G = 0;
  rgb.B = 0;

  a.x = strtol(argv[1], NULL, 10);
  a.y = strtol(argv[2], NULL, 10);

  if (!fp_r) {
    fprintf(stderr, "error in opening the file");
    exit(EXIT_FAILURE);
  }

  if(a.x > image.x || a.y > image.y){
    fprintf(stderr, "error in coordinate");
    exit(EXIT_FAILURE);
  }

  fseek(fp_r, 10, SEEK_SET);
  fread(&n, 1, 1, fp_r);
  fseek(fp_r, 18, SEEK_SET);
  fread(&image.x, 4, 1, fp_r);
  fread(&image.y, 4, 1, fp_r);
  // printf("x = %d, y = %d", image.x, image.y);
  fseek(fp_r, n + 3 * (a.y * image.x + a.x), SEEK_SET);
  fread(&rgb.B, 1, 1, fp_r);
  fread(&rgb.G, 1, 1, fp_r);
  fread(&rgb.R, 1, 1, fp_r);
  printf("R = %d\nG = %d\nB = %d", rgb.R, rgb.G, rgb.B);

  fclose(fp_r);
  return 0;
}