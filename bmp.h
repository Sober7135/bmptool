#ifndef BMP_H__
#define BMP_H__

typedef unsigned char BYTE;
typedef struct RGB {
  BYTE R;
  BYTE G;
  BYTE B;
} RGB;
typedef struct coordinate {
  int x;
  int y;
} COORDINATE;

typedef struct BmpInfo {
  int PixelOffset;
  int Width;
  int Height;
  int Size;
} BmpInfo;

#endif
