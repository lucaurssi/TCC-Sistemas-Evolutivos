
#ifndef BIXINHO
#define BIXINHO

typedef struct _bixinho{
  float radius;
  float x;
  float y;
  float theta;
  unsigned char r,g,b;
  float vel;
  int shape;
}Bixinho; // Bixinho e menu

#endif



Bixinho CreateBixinho(float x, float y, unsigned char *color);

void drawBixinho(Bixinho bixinho, int gene);

void moveBixinho(Bixinho *bixinho, float distance);
