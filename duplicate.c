#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE* fp_r = fopen("image/example01.bmp", "r");
  FILE* fp_w = fopen("image/duplicate_test.bmp", "w+");
  int rgb;
  if (!fp_r) {
    exit(EXIT_FAILURE);
  }
  if (!fp_w) {
    exit(EXIT_FAILURE);
  }
  
  while (fread(&rgb, 1, 1, fp_r)) {
    fwrite(&rgb, 1, 1, fp_w);
    rgb = 0;
  }
  fclose(fp_r);
  fclose(fp_w);
}