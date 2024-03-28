#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <math.h>

typedef struct _bixinho{
  float radius;
  float x;
  float y;
  float theta;
  float r,g,b;
  float vel;// Agora o struct tambem tem a velocidade do bixinho
}Bixinho;


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

Bixinho CreateBixinho(float x, float y, float *color){
    Bixinho A;  

    A.radius = 0.05;
    A.x = x;
    A.y = y;
    A.theta = ((rand()%20)-10)/10.0;
    A.r = color[0];
    A.g = color[1];
    A.b = color[2];
    A.vel = 0.015;

    return A; 
}

void drawBixinho(Bixinho bixinho){
  // Função para desenhar o bixinho
  float radius = bixinho.radius;
  float x = bixinho.x;
  float y = bixinho.y;
  float theta = bixinho.theta;

  //----- Desenha corpo do bixinho -----//
  glColor3f(bixinho.r, bixinho.g, bixinho.b);// Bixinho verde
  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i+=5) {
    glVertex2d( radius*cos(i/180.0*M_PI) + x, radius*sin(i/180.0*M_PI) + y);
  }
  glEnd();

  //----- Desenha olho direito do bixinho -----//
  float eyeRadius = radius/8;
  float eyeDist = M_PI/6;

  glColor3f(0, 0, 0);
  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i+=5) {
    float shiftX = radius/2*cos(theta-eyeDist);
    float shiftY = radius/2*sin(theta-eyeDist);
    glVertex2d( eyeRadius*cos(i/180.0*M_PI) + x + shiftX, eyeRadius*sin(i/180.0*M_PI) + y + shiftY);
  }
  glEnd();

  //----- Desenha olho esquerdo do bixinho -----//
  glColor3f(0, 0, 0);
  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i+=5) {
    float shiftX = radius/2*cos(theta+eyeDist);
    float shiftY = radius/2*sin(theta+eyeDist);

    glVertex2d( eyeRadius*cos(i/180.0*M_PI) + x + shiftX, eyeRadius*sin(i/180.0*M_PI) + y + shiftY);
  }
  glEnd();
}
