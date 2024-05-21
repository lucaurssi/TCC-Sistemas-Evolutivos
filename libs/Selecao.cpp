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
}B; // Bixinho e menu

vector<B> Bs;
int n_Bs = 10;
int N_s = 0;

int tipoGenes = 2;
int G_s = 1;

int SelecaoShape = 0;
int SelecaoCor = 0;

int SShape = 0;
int SCor = 0;

/*	 
 quando forma:
	0 > circulo
	1 > quadrado
	2 > triangulo
 quando cor:
	0 > escuro/preto
	1 > claro/branco 	
*/

bool SChange = true; // indica que ouve um click e deve redesenhar o menu

bool Sdraw = false; // run foi clicado e deve iniciar a simulacao

bool SnextPhase = false; // run foi clicado, bottao de next aparece

bool SgeneMenu = false; // flag para desenhar o menu de multipla escolha de genes

B CreateB(float x, float y, float *color){
    B A;  

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

void drawB(B bixinho, int gene){
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

void moveB(B *bixinho, float distance){
		

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

void Selecao(){
	float color[3];
	
	setColor(color, 1, 1, 1);
	retangle(0.5, 0, 1, 2, color); // limpa bixinhos
	
	setColor(color, 1, 0.5, 0.5); // vermelho claro
	retangle(0.5, -0.5, 0.3, 0.3, color); // quadrado de selecao
	
	RenderString(0.4, -0.45, "Selecao");
	
	
	if (Sdraw){ 
		N_s 		= n_Bs;
		G_s 		= tipoGenes;		
		SelecaoShape = SShape;
		SelecaoCor 	= SCor;
		Sdraw 		= false;		
	}
		
	if (!Bs.empty())
		for(int i=0; i < N_s; i++)
			drawB(Bs[i], G_s);
	
	
	if(!SChange){// se nao apertar nada no menu, não precisa re-escrever o menu
		setColor(color, 0.7, 0.7, 0.7);		
		retangle(-0.012, 0, 0.027, 2, color);

	}else{
		SChange = false;
		draw_basic_menu("Selecao", n_Bs, tipoGenes, SgeneMenu, SShape, SCor);
		
	}

	if (N_s){ // se atualizar clicando no run, abilita o botao NEXT
		setColor(color, 0.2, 0.2, 0.2);
		retangle(-0.55, -0.9, 0.2, 0.09, color); 
		setColor(color, 0.5, 0.5, 0.5); // cinza escuro
		retangle(-0.55, -0.9, 0.19, 0.08, color); 
		
		RenderString(-0.62, -0.92, "Next");
	}

	return;
}		

// Retorna a porcentagem da populacao que atende o criterio de selecao
// utilisa 'N_s' como numero de populacao e
// 'Bs[]' para checar a selecao
string fitness(){
		
	if (N_s == 0) return "n/a";
	
	int nro_selecionados = 0;
	int nro_selecionados2 = 0;	

	// Forma
	if (tipoGenes == 0 || tipoGenes == 2) 		
		for(int i=0; i<N_s; i++)
	  		if (Bs[i].shape == SelecaoShape)
				nro_selecionados++ ;
	// Cor
	if (tipoGenes == 1 || tipoGenes == 0){
		if(SelecaoCor == 0) 	// 0  -->	escuro/preto 	
			for(int i=0; i<N_s; i++){
		  		if (Bs[i].r + Bs[i].g + Bs[i].b < 1.)
					nro_selecionados2++ ;
			}
		else 				// 1 > claro/branco	
			for(int i=0; i<N_s; i++){
		  		if (Bs[i].r + Bs[i].g + Bs[i].b > 2.)
					nro_selecionados2++ ;
			}
	}

	float porcentagem = (((float)nro_selecionados+ (float)nro_selecionados2) /(float) N_s)*100.;
	if (tipoGenes == 0) porcentagem = porcentagem / 2.;

	string str;
	str.append(to_string((int) (porcentagem)) );
	str.append("%");
	
	return str;
}


// move os bixinhos na tela de menu
void processSelecao(){ 
	float color[3];

	setColor(color, 0.7, 0.7, 0.7);
	retangle(-0.7, 0.3, 0.1, 0.1, color);
	RenderString(-0.75, 0.3, fitness() );

	if(Bs.empty()) return;	

	// selecao
	for(int i=0; i<N_s; i++){
		
		if (Bs[i].x > 0.3 && Bs[i].x < 0.7 && Bs[i].y < -0.3 && Bs[i].y > -0.7){ // Zona de Selecao
				
			// forma			
			if (tipoGenes == 0 || tipoGenes == 2){
				if (Bs[i].shape != SelecaoShape){ 
					Bs.erase(Bs.begin()+i); 
					N_s--; 
				}
			
			}
	
			// Cor
			if (tipoGenes == 1 || tipoGenes == 0){
				if(!SelecaoCor){ // escuro/preto
					if(Bs[i].r + Bs[i].g + Bs[i].b > 1.) { Bs.erase(Bs.begin()+i); N_s--; }
				}else			   // claro/branco
					if(Bs[i].r + Bs[i].g + Bs[i].b < 2.) { Bs.erase(Bs.begin()+i); N_s--; }
			}
 		}
		// bixinho não deletado pode mover
		moveB(&Bs[i], Bs[i].vel);
	}
	
	return;
}

void Selecao_buttons(int x, int y, unsigned short int *menu_state){
	float color[3];
	SChange = true;
	
	// voltar ao menu principal (<-- back)
	if (x > 30 && x < 150 && y > 25 && y < 60){
		N_s = 0;		
		*menu_state = 0; 
	
	// run	
	}else if (x > 290 && x < 380 && y > 830 && y < 875){		
		if(Bs.empty() || (int)Bs.size() < n_Bs){ // cria bixinhos para serem desenhados
			int size = n_Bs - Bs.size();			
			for(int i=0; i<size; i++){
				setColor(color, (rand()%255)/255.0, (rand()%255)/255.0, (rand()%255)/255.0);
			
				B A = CreateB((rand()%10/10.0) +0.02, ((rand()%20)-10)/10.0, color);
				Bs.push_back(A);
			}
		}
		Sdraw = true;
	
	// Next	
	}else if (x > 155 && x < 245 && y > 830 && y < 875){
		N_s = 0;
		*menu_state = *menu_state + 1;

	// Nro individuos menu
	}else if (y > 110 && y < 135){	
			if (x > 220 && x < 250) n_Bs = 10;
			else if (x > 265 && x < 295) n_Bs = 25;
			else if (x > 310 && x < 340) n_Bs = 50;
			else if (x > 355 && x < 385) n_Bs = 100;
			
			int size = n_Bs - Bs.size(); // se aumentar o numero de bixinhos, cria novos bixinhos			
			for(int i=0; i<size; i++){
				setColor(color, (rand()%255)/255.0, (rand()%255)/255.0, (rand()%255)/255.0);
			
				B A = CreateB((rand()%10/10.0) +0.02, ((rand()%20)-10)/10.0, color);
				Bs.push_back(A);
			}

	// gene menu	
	}else if (!SgeneMenu && x > 190 && x < 350 && y > 199 && y < 235){		
		SgeneMenu = true; 
		
	}else if (SgeneMenu && x > 360 && x < 430){
		if (y > 165 && y < 200) {
			SgeneMenu = false;
			tipoGenes = 1;  // cor		
		}else if (y > 200 && y < 235){
			SgeneMenu = false;
			tipoGenes = 2;  // forma		
		}else if (y > 235 && y < 270){
			SgeneMenu = false;
			tipoGenes = 0;  // cor e forma	
		}
		
	// selecao
	}else if (y > 245 && y < 275){	
			if (x > 165 && x < 195) SCor = 0; // preto
			else if (x > 200 && x < 230) SCor = 1; // branco
			else if (x > 255 && x < 285) SShape = 0; // circulo
			else if (x > 290 && x < 320) SShape = 1; // quadrado
			else if (x > 325 && x < 355) SShape = 2; // triangulo
	}

	SChange = true;
	return;
}















