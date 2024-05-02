#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <math.h>
#include <string>

#define FONT GLUT_BITMAP_TIMES_ROMAN_24

using namespace std;


void setColor(float* color, float R, float G, float B){
	color[0] = R;
	color[1] = G;
	color[2] = B;
	return; 
}

void retangle(float x, float y, float w, float h, float*color){
  // Vai desenhar um polígono de 4 vértices

  glColor3f(color[0], color[1], color[2]);// Define que será desenhar um objeto azul
  glBegin(GL_POLYGON);// Fala para o OpenGL que os próximos pontos serão para desenhar um polígono

  // Adicionada cada vértice do retângulo
  glVertex2d( x-w/2, y-h/2);
  glVertex2d( x-w/2, y+h/2);
  glVertex2d( x+w/2, y+h/2);
  glVertex2d( x+w/2, y-h/2);

  glEnd();// Fala para o OpenGL que terminou de enviar os vértices do polígono
}


void triangle(float x, float y, float h, float b, float*color){
  // O mais polígono mais trivial: 3 vertíces

  glColor3f(color[0], color[1], color[2]);// Define que será desenhar um objeto roxo
  glBegin(GL_POLYGON);

  // Adicionada cada vértice do triângulo
  glVertex2d( x-b/2, y-h/2);
  glVertex2d( x+b/2, y-h/2);
  glVertex2d( x, y+h/2);

  glEnd();// Fala para o OpenGL que terminou de enviar os vértices do polígono
}


void circle(float x, float y, float radius, float*color){
  // Um circulo é desenhado como um polígono de muitos pontos

  glColor3f(color[0], color[1], color[2]);// Define que será desenhar um objeto verde
  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i+=5) {
    // Adicionada cada vértice 2D do circulo
    glVertex2d( radius*cos(i/180.0*M_PI) + x, radius*sin(i/180.0*M_PI) + y);
  }
  glEnd();
}


void strangePolygon(float x, float y, float*color){

  glColor3f(color[0], color[1], color[2]);// Define que será desenhar um objeto preto

  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i+=10) {
    glVertex2d( 0.2*cos(i/180.0*M_PI) + x + cos(i)*0.15,  0.2*sin(i/180.0*M_PI) + y + sin(i)*0.15);
  }
  glEnd();

}

void anotherStrangePolygon(float x, float y, float*color){
  glColor3f(color[0], color[1], color[2]);// Define que será desenhar um objeto amarelo

  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i+=10) {
    glVertex2d( 0.3*cos(i/180.0*M_PI) + x,  0.3*sin(i/180.0*M_PI) + y);
    i+=10;
    glVertex2d( 0.1*cos(i/180.0*M_PI) + x,  0.1*sin(i/180.0*M_PI) + y);
  }
  glEnd();
}


void RenderString(float x, float y, string string){  
	
	glColor3f(0, 0, 0); // black
	glRasterPos2f(x, y); 
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[0]); // write one character
	
	for(int i=1; i<(int)string.length(); i++){
		x = (x*900)+ 2*glutBitmapWidth(FONT, string[i-1]); // move x by the width of the character
		x = x/900;
		glRasterPos2f(x, y);
		glutBitmapCharacter(FONT, string[i]);
	}
}







