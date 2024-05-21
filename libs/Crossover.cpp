#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include "drawings.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <string>


using namespace std;

typedef struct _bixinho{
  float radius;
  float x;
  float y;
  float theta;
  float r,g,b;
  float vel;
  int shape;
}C; // Bixinho e menu

vector<C> Bc;

int n_Bc = 10;
int N_c = 0;

int tipoGenec = 2;
int G_c = 1;

int SelecaoShapec = 0;
int SelecaoCorc = 0;

int CShape = 0;
int CCor = 0;

/*	 
 quando forma:
	0 > circulo
	1 > quadrado
	2 > triangulo
 quando cor:
	0 > escuro/preto
	1 > claro/branco 	
*/

bool CChange = true; // indica que ouve um click e deve redesenhar o menu

bool Cdraw = false; // run foi clicado e deve iniciar a simulacao

bool CnextPhase = false; // run foi clicado, bottao de next aparece

bool CgeneMenu = false; // flag para desenhar o menu de multipla escolha de genes

C CreateC(float x, float y, float *color){
    C A;  

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

void drawC(C bixinho, int gene){
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
				retangle(x, y, radius*2, radius*2, color);
				break;
			case 2: 
				triangle(x, y, radius*2, radius*2, color);	
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

void moveC(C *bixinho, float distance){
		

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

void Crossover(){
	float color[3];
	
	setColor(color, 1, 1, 1);
	retangle(0.5, 0, 1, 2, color); // limpa bixinhos
	
	setColor(color, 1, 0.5, 0.5); // vermelho claro
	retangle(0.5, -0.5, 0.3, 0.3, color); // quadrado de selecao
	
	
	
	
	if (Cdraw){ 
		N_c 		= n_Bc;
		G_c 		= tipoGenec;		
		SelecaoShapec = CShape;
		SelecaoCorc = CCor;
		Cdraw 		= false;		
	}
		
	if (!Bc.empty())
		for(int i=0; i < N_c; i++)
			drawC(Bc[i], G_c);
	
	
	if(!CChange){// se nao apertar nada no menu, não precisa re-escrever o menu
		setColor(color, 0.7, 0.7, 0.7);		
		retangle(-0.012, 0, 0.027, 2, color);

	}else{
		CChange = false;
		draw_basic_menu("Crossover", n_Bc, tipoGenec, CgeneMenu, CShape, CCor);
		
	}

	

	return;
}		

// Retorna a porcentagem da populacao que atende o criterio de selecao
// utilisa 'N_s' como numero de populacao e
// 'Bs[]' para checar a selecao
string fitnessc(){
		
	if (N_c == 0) return "n/a";
	
	int nro_selecionados = 0;
	int nro_selecionados2 = 0;	

	// Forma
	if (tipoGenec == 0 || tipoGenec == 2) 		
		for(int i=0; i<N_c; i++)
	  		if (Bc[i].shape == SelecaoShapec)
				nro_selecionados++ ;
	// Cor
	if (tipoGenec == 1 || tipoGenec == 0){
		if(SelecaoCorc == 0) 	// 0  -->	escuro/preto 	
			for(int i=0; i<N_c; i++){
		  		if (Bc[i].r + Bc[i].g + Bc[i].b < 1.)
					nro_selecionados2++ ;
			}
		else 				// 1 > claro/branco	
			for(int i=0; i<N_c; i++){
		  		if (Bc[i].r + Bc[i].g + Bc[i].b > 2.)
					nro_selecionados2++ ;
			}
	}

	float porcentagem = (((float)nro_selecionados+ (float)nro_selecionados2) /(float) N_c)*100.;
	if (tipoGenec == 0) porcentagem = porcentagem / 2.;

	string str;
	str.append(to_string((int) (porcentagem)) );
	str.append("%");
	
	return str;
}


// move os bixinhos na tela de menu
void processCrossover(){ 
	float color[3];

	setColor(color, 0.7, 0.7, 0.7);
	retangle(-0.7, 0.3, 0.1, 0.1, color);
	RenderString(-0.75, 0.3, fitnessc() );

	if(Bc.empty()) return;	

	// selecao
	for(int i=0; i<N_c; i++){
		
		if (Bc[i].x > 0.3 && Bc[i].x < 0.7 && Bc[i].y < -0.3 && Bc[i].y > -0.7){ // Zona de Selecao
				
			// forma			
			if (tipoGenec == 0 || tipoGenec == 2){
				if (Bc[i].shape != SelecaoShapec){ 
					Bc.erase(Bc.begin()+i); 
					N_c--; 
				}
			
			}
	
			// Cor
			if (tipoGenec == 1 || tipoGenec == 0){
				if(!SelecaoCorc){ // escuro/preto
					if(Bc[i].r + Bc[i].g + Bc[i].b > 1.) { Bc.erase(Bc.begin()+i); N_c--; }
				}else			   // claro/branco
					if(Bc[i].r + Bc[i].g + Bc[i].b < 2.) { Bc.erase(Bc.begin()+i); N_c--; }
			}
 		}
		// bixinho não deletado pode mover
		moveC(&Bc[i], Bc[i].vel);
	}
	
	return;
}

void Crossover_buttons(int x, int y, unsigned short int *menu_state){
	float color[3];
	CChange = true;
	
	// voltar ao menu principal (<-- back)
	if (x > 30 && x < 150 && y > 25 && y < 60){
		N_c = 0;		
		*menu_state = 0; 
	
	// run	
	}else if (x > 290 && x < 380 && y > 830 && y < 875){		
		if(Bc.empty() || (int)Bc.size() < n_Bc){ // cria bixinhos para serem desenhados
			int size = n_Bc - Bc.size();			
			for(int i=0; i<size; i++){
				setColor(color, (rand()%255)/255.0, (rand()%255)/255.0, (rand()%255)/255.0);
			
				C A = CreateC((rand()%10/10.0) +0.02, ((rand()%20)-10)/10.0, color);
				Bc.push_back(A);
			}
		}
		Cdraw = true;
	
	

	// Nro individuos menu
	}else if (y > 110 && y < 135){	
			if (x > 220 && x < 250) n_Bc = 10;
			else if (x > 265 && x < 295) n_Bc = 25;
			else if (x > 310 && x < 340) n_Bc = 50;
			else if (x > 355 && x < 385) n_Bc = 100;
			
			int size = n_Bc - Bc.size(); // se aumentar o numero de bixinhos, cria novos bixinhos			
			for(int i=0; i<size; i++){
				setColor(color, (rand()%255)/255.0, (rand()%255)/255.0, (rand()%255)/255.0);
			
				C A = CreateC((rand()%10/10.0) +0.02, ((rand()%20)-10)/10.0, color);
				Bc.push_back(A);
			}

	// gene menu	
	}else if (!CgeneMenu && x > 190 && x < 350 && y > 199 && y < 235){		
		CgeneMenu = true; 
		
	}else if (CgeneMenu && x > 360 && x < 430){
		if (y > 165 && y < 200) {
			CgeneMenu = false;
			tipoGenec = 1;  // cor		
		}else if (y > 200 && y < 235){
			CgeneMenu = false;
			tipoGenec = 2;  // forma		
		}else if (y > 235 && y < 270){
			CgeneMenu = false;
			tipoGenec = 0;  // cor e forma	
		}
		
	// selecao
	}else if (y > 245 && y < 275){	
			if (x > 165 && x < 195) CCor = 0; // preto
			else if (x > 200 && x < 230) CCor = 1; // branco
			else if (x > 255 && x < 285) CShape = 0; // circulo
			else if (x > 290 && x < 320) CShape = 1; // quadrado
			else if (x > 325 && x < 355) CShape = 2; // triangulo
	}

	CChange = true;
	return;
}















