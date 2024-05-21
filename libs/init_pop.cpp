#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include "drawings.h"
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

typedef struct _bixinho{
  float radius;
  float x;
  float y;
  float theta;
  float r,g,b;
  float vel;
  int shape;
}Bip; // Bixinho e menu

vector<Bip> Bips;
int n_Bips = 10;
int N_ip = 0;

int tipoGene = 1;
int G_ip = 1;


bool IPChange = true;
bool IPdraw = false;
bool IPnextPhase = false;
bool geneMenu = false;

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
	A.shape = rand()%3;

    return A; 
}

void drawBip(Bip bixinho, int gene){
	// Função para desenhar o bixinho	
	float color[3]; 
	setColor(color, bixinho.r, bixinho.g, bixinho.b);
	
	if (gene == 2) // forma apenas
		setColor(color, 0.3, 0.3, 0.3); // cinza claro
	

	float radius = bixinho.radius;
	float x = bixinho.x;
	float y = bixinho.y;
	float theta = bixinho.theta;
	int shape = bixinho.shape;

	//----- Desenha corpo do bixinho -----//

	if (gene == 1) // apenas cor
		circle(x, y, radius, color);
	else {
		switch (shape){
			case 0:		
				circle(x, y, radius, color);
				break;
			case 1:
				triangle(x, y, radius*2, radius*2, color);				
				break;
			case 2: 
				retangle(x, y, radius*2, radius*2, color);
				break;
		
		}
	}

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
	bixinho->x = bixinho->x>1 ? 0.04 : bixinho->x;
	bixinho->y = bixinho->y>1 ? -1 : bixinho->y;
	bixinho->x = bixinho->x<0.03 ? 1 : bixinho->x;
	bixinho->y = bixinho->y<-1 ? 1 : bixinho->y;

}

void init_pop(){
	float color[3];
	
	setColor(color, 1, 1, 1);
	retangle(0.5, 0, 1, 2, color); // limpa bixinhos
	
	
	if (IPdraw){ 
		N_ip = n_Bips;
		G_ip = tipoGene;		
		IPdraw = false;	
		
	}

	if (!Bips.empty())
		for(int i=0; i < N_ip; i++)
			drawBip(Bips[i], G_ip);
	
	// ---- menu ----
	

	// cinza
	setColor(color, 0.7, 0.7, 0.7);
	
	if(!IPChange){// se nao apertar nada no menu, não precisa re-escrever o menu
		retangle(-0.012, 0, 0.027, 2, color);
		

	}else{
		IPChange = false;
		
		retangle(-0.5, 0, 1, 2, color); // pinta metade da tela de cinza
		

		
		setColor(color, 0.5, 0.5, 0.5); // cinza escuro
		retangle(-0.8, 0.9, 0.25, 0.075, color); 
		RenderString(-0.91, 0.88, "<-- Back");

		RenderString(-0.6, 0.88, "População inicial");

		RenderString(-0.95, 0.65, "O primeiro passo para simular um sistema");
		RenderString(-0.95, 0.60, "evolutivo eh iniciar uma população, o que");
		RenderString(-0.95, 0.55, "significa escolher o numero de individuos");
		RenderString(-0.95, 0.50, "a serem simulados:");
		
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
				cout << "n_Bips outside of pre-determined values.\n";			
		
		}

	// -------------------------------------------------
	//            Gene / cromossomo do individuo
	// -------------------------------------------------
		
		RenderString(-0.95, 0.25, "O segundo passo eh decidir o que sera");
		RenderString(-0.95, 0.20, "simulado. No caso desse exemplo temos");
		RenderString(-0.95, 0.15, "cor e formas de bixinhos.");

		setColor(color, 0.2, 0.2, 0.2);
		retangle(-0.4, 0.015, 0.36, 0.085, color); 
		setColor(color, 0.5, 0.5, 0.5); // cinza escuro
		retangle(-0.4, 0.015, 0.35, 0.075, color); 

		RenderString(-0.95, 0, "Tipo de genes:");

		switch (tipoGene){
			case 0:
				RenderString(-0.55, 0, "Cor e Forma");	
				break;
			case 1:
				RenderString(-0.55, 0, "Cor");	
				break;
			case 2:
				RenderString(-0.55, 0, "Forma");	
				break;
			default: 
				cout << "unkown tipoGene" << tipoGene << "\n";				
		}

		if (geneMenu){
			
			setColor(color, 0.5, 0.5, 0.5); // cinza escuro
			retangle(-0.12, -0.065, 0.15, 0.075, color);
			setColor(color, 0.5, 0.5, 0.5); // cinza escuro
			retangle(-0.12, 0.015, 0.15, 0.075, color);
			setColor(color, 0.5, 0.5, 0.5); // cinza escuro
			retangle(-0.12, 0.095, 0.15, 0.075, color);
			RenderString(-0.19, 0.075, "Cor");
			RenderString(-0.19, 0, "Forma");
			RenderString(-0.19, -0.08, "C e F");
			

		
		}

		RenderString(-0.95, -0.30, "Escolha os genes e o numero de ");
		RenderString(-0.95, -0.35, "individuos acima e clique em 'Run'.");

	// --------------------------------------------------

		// --------- Run Button -----------------
		setColor(color, 0.2, 0.2, 0.2);
		retangle(-0.25, -0.9, 0.2, 0.09, color); 
		setColor(color, 0.5, 0.5, 0.5); // cinza escuro
		retangle(-0.25, -0.9, 0.19, 0.08, color); 
		
		RenderString(-0.3, -0.92, "Run");
		// --------------------------------------

		if (N_ip){ // se atualizar clicando no run, abilita o botao NEXT
			setColor(color, 0.2, 0.2, 0.2);
			retangle(-0.55, -0.9, 0.2, 0.09, color); 
			setColor(color, 0.5, 0.5, 0.5); // cinza escuro
			retangle(-0.55, -0.9, 0.19, 0.08, color); 
			
			RenderString(-0.62, -0.92, "Next");
			RenderString(-0.95, -0.75, "Clique em Next para passar");
			RenderString(-0.95, -0.80, "para proxima faze.");
		}
	}
	return;
}		

// move os bixinhos na tela de menu
void processIPop(){ 
	if(Bips.empty()) return;	

	// Para mover os bixinhos
	for(int i=0; i<N_ip; i++)
  		moveBip(&Bips[i], Bips[i].vel);

	return;
}

void IPop_buttons(int x, int y, unsigned short int *menu_state){
	float color[3];
	IPChange = true;
	
	// voltar ao menu principal (<-- back)
	if (x > 30 && x < 150 && y > 25 && y < 60){
		N_ip = 0;
		*menu_state = 0; 
	
	// run	
	}else if (x > 290 && x < 380 && y > 830 && y < 875){		
		if(Bips.empty()) // cria bixinhos para serem desenhados
			for(int i=0; i<n_Bips; i++){
				setColor(color, (rand()%255)/255.0, (rand()%255)/255.0, (rand()%255)/255.0);
			
				Bip A = CreateBip(rand()%10/10.0, ((rand()%20)-10)/10.0, color);
				Bips.push_back(A);
			}
		IPdraw = true;

	// Next	
	}else if (x > 155 && x < 245 && y > 830 && y < 875){
		N_ip =0;
		*menu_state = *menu_state + 1;

	// Nro individuos menu
	}else if (y > 245 && y < 275){	
			if (x > 220 && x < 250) n_Bips = 10;
			else if (x > 265 && x < 295) n_Bips = 25;
			else if (x > 310 && x < 340) n_Bips = 50;
			else if (x > 355 && x < 385) n_Bips = 100;
			
			int size = n_Bips - Bips.size(); // se aumentar o numero de bixinhos, cria novos bixinhos			
			for(int i=0; i<size; i++){
				setColor(color, (rand()%255)/255.0, (rand()%255)/255.0, (rand()%255)/255.0);
			
				Bip A = CreateBip((rand()%10/10.0) +0.02, ((rand()%20)-10)/10.0, color);
				Bips.push_back(A);
			}

	// gene menu	
	}else if (!geneMenu && x > 190 && x < 350 && y > 420 && y < 460)		
		geneMenu = true; 
		
	else if (geneMenu && x > 360 && x < 430){
		if (y > 390 && y < 425) {
			geneMenu = false;
			tipoGene = 1;  // cor		
		}else if (y > 425 && y < 460){
			geneMenu = false;
			tipoGene = 2;  // forma		
		}else if (y > 460 && y < 495){
			geneMenu = false;
			tipoGene = 0;  // cor e forma	
		}
		
	}

	IPChange = true;
	return;
}















