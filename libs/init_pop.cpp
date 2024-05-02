#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include "drawings.h"
#include <math.h>
#include <vector>

using namespace std;

typedef struct _bixinho{
  float radius;
  float x;
  float y;
  float theta;
  float r,g,b;
  float vel;
}Bip; // Bixinho e menu

vector<Bip> Bips;
int n_Bips = 10;



Bip CreateBip(float x, float y, float *color){
    Bip A;  

    A.radius = 0.05;
    A.x = x;
    A.y = y;
    A.theta = ((rand()%20)-10)/10.0;
    A.r = color[0];
    A.g = color[1];
    A.b = color[2];
    A.vel = 0.010;

    return A; 
}

void drawBip(Bip bixinho){
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

void moveBip(Bip *bixinho, float distance){
		

	bixinho->theta+= ((rand()%11)-5)/100.0 ; // atualiza angulo

	// Para mover para onde ele está olhando (na direção theta)
	bixinho->x = bixinho->x + distance*cos(bixinho->theta);
	bixinho->y = bixinho->y + distance*sin(bixinho->theta);

	// Impede que o wilson saia da tela
	bixinho->x = bixinho->x>1 ? 0 : bixinho->x;
	bixinho->y = bixinho->y>1 ? -1 : bixinho->y;
	bixinho->x = bixinho->x<0 ? 1 : bixinho->x;
	bixinho->y = bixinho->y<-1 ? 1 : bixinho->y;

}

void init_pop(){
	float color[3];
	/*
	for(int i=0; i < n_Bips; i++)
		drawBip(Bips[i]);
	*/
	// ---- menu ----


	// cinza
	setColor(color, 0.7, 0.7, 0.7);
	 
	retangle(-0.5, 0, 1, 2, color); // pinta metade da tela de cinza
	

	
	setColor(color, 0.5, 0.5, 0.5); // cinza escuro
	retangle(-0.8, 0.9, 0.25, 0.075, color); // "<-- Back"
	RenderString(-0.91, 0.88, "<-- Back");

	RenderString(-0.6, 0.88, "População inicial");

	RenderString(-0.8, 0.65, "Insira explicação excelente aqui");
	RenderString(-0.8, 0.6, "Insira explicação excelente aqui");
	RenderString(-0.8, 0.55, "Insira explicação excelente aqui");
	RenderString(-0.8, 0.5, "Insira explicação excelente aqui");
	
// -------------------------------------------------
// 		Componete de menu do numero de individuos
// -------------------------------------------------

	// Numero de individuos a serem criados
	RenderString(-0.95, 0.4, "Nro. Individuos:");

	setColor(color, 0.5, 0.5, 0.5);

	// 10 
	RenderString(-0.51, 0.34, "10"); 
	circle( -0.48, 0.42, 0.03, color);

	// 25
	RenderString(-0.41, 0.34, "25");
	circle( -0.38, 0.42, 0.03, color);
	
	// 50
	RenderString(-0.31, 0.34, "50");
	circle( -0.28, 0.42, 0.03, color);
	
	// 100
	RenderString(-0.22, 0.34, "100");
	circle( -0.18, 0.42, 0.03, color);
	
	
	// circulo azul na posicao selecionada
	setColor(color, 0.1, 0.1, 1); // azul
	switch (n_Bips){
		case 10:
			circle( -0.48, 0.42, 0.02, color);
			break;
		case 25:
			circle( -0.38, 0.42, 0.02, color);
			break;
		case 50:
			circle( -0.28, 0.42, 0.02, color);
			break;
		case 100:
			circle( -0.18, 0.42, 0.02, color);
			break;
		default:
			;			
	
	}

// -------------------------------------------------
	
	return;
}		

// move os bixinhos na tela de menu
void processIPop(){ 
	if(Bips.empty()) return;	

	// Para mover os bixinhos
	for(int i=0; i<10; i++)
  		moveBip(&Bips[i], Bips[i].vel);

	return;
}

void IPop_buttons(int x, int y, unsigned short int *menu_state){
	if (x > 30 && x < 150 && y > 25 && y < 60) 
		*menu_state = 0; // voltar ao menu (<-- back)
	else 
		return;

	return;
}
