
#include <iostream>
#include <math.h>

using namespace std;

#define windowWidth 600
#define windowHeight 600

// Função principal para desenhar
void draw();

// Funções para desenhar polígonos
/*
void retangle(float x, float y, float w, float h);
void triangle(float x, float y, float h, float b);
void circle(float x, float y, float radius);
void strangePolygon(float x, float y);
void anotherStrangePolygon(float x, float y);
*/

int main(int argc, char** argv){
  //----- Criar janela -----//
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(windowWidth, windowHeight);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("TCC");
  glClearColor(1.0, 1.0, 1.0, 1.0);// Limpa a tela (red, green, blue, alpha)
  
  glutDisplayFunc(draw);// Define qual função irá desenhar
  
  glutMainLoop();

  return 0;
}