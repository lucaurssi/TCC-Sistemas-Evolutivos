#include <string>
#include <vector>
 

// muda a cor na variavel
void setColor(float* color, float R, float G, float B);

// Funções para desenhar polígonos
void retangle(float x, float y, float w, float h, float*color);
void triangle(float x, float y, float h, float b, float*color);
void circle(float x, float y, float radius, float*color);
void strangePolygon(float x, float y, float*color);
void anotherStrangePolygon(float x, float y, float*color);


// textos
void RenderString(float x, float y, std::string string);
