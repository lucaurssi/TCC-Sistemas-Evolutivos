typedef struct _bixinho{
  float radius;
  float x;  // posicao
  float y;  // posicao
  float theta;
  float r,g,b;
  float vel;
}Bixinho;


// Funções para desenhar polígonos
void retangle(float x, float y, float w, float h, float*color);
void triangle(float x, float y, float h, float b, float*color);
void circle(float x, float y, float radius, float*color);
void strangePolygon(float x, float y, float*color);
void anotherStrangePolygon(float x, float y, float*color);


Bixinho CreateBixinho(float x, float y, float *color);
void drawBixinho(Bixinho bixinho);
