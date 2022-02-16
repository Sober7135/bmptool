// ./crop a.bmp b.bmp [Width]x[Height]+[x_offset]+[y_offset]

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

#define cmp(a, b) ((a->x) >= 0 && (a->x) <= (b->Width) && (a->y) >= 0 && (a->y) <= (b->Height))

int x_offset, y_offset, height_size, width_size;

static void parse(int argc, char* argv[]) {
  if (argc == 4) {
    // e.g. 200x400+100+250
    char* end;
    width_size = strtol(argv[3], &end, 10);
    if (*end != 'x') {
      fprintf(stderr, "error: not \'x\'\n");
      exit(EXIT_FAILURE);
    }
    end++;
    height_size = strtol(end, &end, 10);
    if (*end != 0) {
      end++;
      x_offset = strtol(end, &end, 10);
      y_offset = strtol(end, &end, 10);
    }
    if (x_offset < 0 || y_offset < 0 || height_size <= 0 || width_size <= 0) {
      fprintf(stderr, "error in geomentry\n");
      exit(EXIT_FAILURE);
    }
  } else {
    fprintf(stderr, "error");
    exit(EXIT_FAILURE);
  }
}

static void get_BmpInfo(FILE* fp_r, BmpInfo* image) {
  fseek(fp_r, 10, SEEK_SET);
  fread(&image->PixelOffset, 1, 1, fp_r);  // 读取偏移量
  fseek(fp_r, 18, SEEK_SET);
  fread(&image->Width, 4, 1, fp_r);  // 读取图像的长宽
  fread(&image->Height, 4, 1, fp_r);
}

static void initCOORDINATE(COORDINATE* start, COORDINATE* end, BmpInfo* image) {
  start->x = x_offset;
  start->y = image->Height - y_offset - height_size;
  end->x = start->x + width_size;
  end->y = start->y + height_size;
  if (!(cmp(start, image) && cmp(end, image))) {
    fprintf(stderr, "error in size\n");
    exit(EXIT_FAILURE);
  }
}

static void copy_crop(COORDINATE* start, BmpInfo* image, FILE* fp_r, FILE* fp_w) {
  int i = 0;
  BYTE byte;
  fseek(fp_r, 0, SEEK_SET);
  while (i++ < image->PixelOffset) {
    fread(&byte, 1, 1, fp_r);
    fwrite(&byte, 1, 1, fp_w);
  }
  fseek(fp_r, (start->x + start->y * image->Width) * 3 + image->PixelOffset, SEEK_SET);
  for (int j = 0; j < height_size; j++) {
    for (int i = 0; i < width_size * 3; i++) {
      fread(&byte, 1, 1, fp_r);
      fwrite(&byte, 1, 1, fp_w);
    }
    fseek(fp_r, 3 * (image->Width - width_size), SEEK_CUR);
  }
}

static void modify_size(FILE* fp_w) {
  long long size = ftell(fp_w);
  fseek(fp_w, 2, SEEK_SET);
  fwrite(&size, 4, 1, fp_w);
  fseek(fp_w, 0x12, SEEK_SET);
  fwrite(&width_size, 4, 1, fp_w);
  fwrite(&height_size, 4, 1, fp_w);
}

int main(int argc, char* argv[]) {
  parse(argc, argv);

  FILE* fp_r;
  FILE* fp_w;
  BmpInfo image;
  COORDINATE start, end;
  fp_r = fopen(argv[1], "rb");  // 8aec5e00
  fp_w = fopen(argv[2], "wb");

  if (!fp_r) {
    fprintf(stderr, "error in opening the target file\n");
    exit(EXIT_FAILURE);
  }
  if (!fp_w) {
    fprintf(stderr, "error in creating the new file \n");
    exit(EXIT_FAILURE);
  }

  get_BmpInfo(fp_r, &image);
  initCOORDINATE(&start, &end, &image);
  copy_crop(&start, &image, fp_r, fp_w);
  modify_size(fp_w);

  fclose(fp_r);
  fclose(fp_w);

  return 0;
}