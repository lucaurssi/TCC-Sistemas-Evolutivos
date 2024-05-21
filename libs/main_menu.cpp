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
}Bm; // Bixinho e menu

vector<Bm> Bms;
bool menuChange = true;



Bm CreateBm(float x, float y, float *color){
    Bm A;  

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

void drawBm(Bm bixinho){
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

void moveBm(Bm *bixinho, float distance){
		

	bixinho->theta+= ((rand()%11)-5)/100.0 ; // atualiza angulo

	// Para mover para onde ele está olhando (na direção theta)
	bixinho->x = bixinho->x + distance*cos(bixinho->theta);
	bixinho->y = bixinho->y + distance*sin(bixinho->theta);

	// Impede que o wilson saia da tela
	bixinho->x = bixinho->x>1 ? 0.03 : bixinho->x;
	bixinho->y = bixinho->y>1 ? -1 : bixinho->y;
	bixinho->x = bixinho->x<0.02 ? 1 : bixinho->x;
	bixinho->y = bixinho->y<-1 ? 1 : bixinho->y;

}

void main_menu(){
	float color[3];

	setColor(color, 1, 1, 1);
	retangle(0.5, 0, 1, 2, color); // limpa bixinhos

	if(Bms.empty()) // cria bixinhos para serem desenhados
		for(int i=0; i<10; i++){
			setColor(color, (rand()%255)/255.0, (rand()%255)/255.0, (rand()%255)/255.0);
		
			Bm A = CreateBm(rand()%10/10.0, ((rand()%20)-10)/10.0, color);
			Bms.push_back(A);
		}

	
	for(int i=0; i<10; i++)
		drawBm(Bms[i]);
	
	// ---- menu ----

	setColor(color, 0.7, 0.7, 0.7);
	
	if(!menuChange){// se nao apertar nada no menu, não precisa re-escrever o menu
		retangle(-0.014, 0, 0.026, 2, color); // limpa 
		

	}else{
	// cinza
		menuChange = false;

		setColor(color, 0.7, 0.7, 0.7);
		retangle(-0.5, 0, 1, 2, color); // pinta metade da tela de cinza
		

		// cinza, um pouco mais escuro
		setColor(color, 0.5, 0.5, 0.5);

		retangle(-0.6, 0.8, 0.4, 0.1, color);
		RenderString(-0.79, 0.78, "População inicial");

		retangle(-0.6, 0.6, 0.4, 0.1, color);
		RenderString(-0.79, 0.58, "Selecao");

		retangle(-0.6, 0.4, 0.4, 0.1, color);
		RenderString(-0.79, 0.38, "Crossover");
	}
	return;
}		

// move os bixinhos na tela de menu
void processMenu(){ 
	if(Bms.empty()) return;	

	// Para mover os bixinhos
	for(int i=0; i<10; i++)
  		moveBm(&Bms[i], Bms[i].vel);
	return;

}

void menu_buttons(int x, int y, unsigned short int *menu_state){
	if (x > 270 || x < 90) return; // esquerda e direta dos botoes

	if (y < 112 && y > 65 ){
		*menu_state = 1; // Iniciar Populacao
		menuChange = true;
	}else if (y < 200 && y > 150 ){
		*menu_state = 2; // Selecao
		menuChange = true;
	}else if (y < 290 && y > 245 ){
		*menu_state = 3; // Crossover
		menuChange = true;
	}

	return;
}



