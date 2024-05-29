#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "drawings.h"
#include "Bixinhos.h"

#include <math.h>
#include <vector>
#include <iostream>
#include <string>


using namespace std;

vector<Bixinho> mB;
int nro_indv_visual = 10;
int nro_indvidous = 0;

int tipoGeme = 2;
int G_m = 1;

int SelecaoShapem = 0;
int Blue_Shape = 0;

int SelecaoCorm = 0;
int Blue_Cor = 0;

bool Blue_reproducao = true;
bool SelecaoReproducaom = true;

// rename to menu_change_flag
bool MChange = true; // indica que ouve um click e deve redesenhar o menu

// rename to run_flag
bool Mdraw = false; // run foi clicado e deve iniciar a simulacao

bool MnextPhase = false; // run foi clicado, bottao de next aparece

bool MgeneMenu = false; // flag para desenhar o menu de multipla escolha de genes


void Mutacao(){
	unsigned char color[3];
	
	setColor(color, WHITE);
	retangle(0.5, 0, 1, 2, color); // limpa bixinhos
	
	setColor(color, 255, 127, 127); // vermelho claro
	retangle(0.5, -0.5, 0.3, 0.3, color); // quadrado de selecao
	
	
	if (Mdraw){ 
		nro_indvidous 	= nro_indv_visual;
		G_m 			= tipoGeme;		
		SelecaoShapem 	= Blue_Shape;
		SelecaoCorm 	= Blue_Cor;
		SelecaoReproducaom = Blue_reproducao;
		Mdraw 			= false;
				
	}
		
	if (!mB.empty())
		for(int i=0; i < nro_indvidous; i++)
			drawBixinho(mB[i], G_m);
	
	
	if(!MChange){// se nao apertar nada no menu, não precisa re-escrever o menu
		setColor(color, LIGHT_GREY);		
		retangle(-0.012, 0, 0.027, 2, color);

	}else{
		MChange = false;
		draw_basic_menu("Mutacao");
		
		nro_individuos(-0.95, 0.7,nro_indv_visual);
		tipo_de_gene(-0.95, 0.5, tipoGeme, MgeneMenu);	
		draw_Selecao(-0.95, 0.4, tipoGeme, Blue_Shape, Blue_Cor);
		draw_Reproducao(-0.95, 0.2, Blue_reproducao);

	}

	if (nro_indvidous){ // se atualizar clicando no run, abilita o botao NEXT
		setColor(color, GREY);
		retangle(-0.55, -0.9, 0.2, 0.09, color);
		
		RenderString(-0.62, -0.92, "Next");
	}

	

	return;
}		


void Repopulatem(){
	char random_indv = rand()%nro_indvidous;
	Bixinho A;

	if (SelecaoReproducaom)
		A = mB[random_indv];
	
	else{	
		char random_indv2 = rand()%nro_indvidous;

		A.radius = 0.05;
		A.x = mB[random_indv].x;
		A.y = mB[random_indv2].y;
		A.theta = ((rand()%20)-10)/10.0;
		A.r = (mB[random_indv].r + mB[random_indv2].r)/2;
		A.g = (mB[random_indv].g + mB[random_indv2].g)/2;
		A.b = (mB[random_indv].b + mB[random_indv2].b)/2;
		A.vel = 0.010;

		if(rand()%2) A.shape = mB[random_indv].shape;
		else A.shape = mB[random_indv2].shape;		
	}

	mB.push_back(A);
	nro_indvidous++; 
}

// move os bixinhos na tela de menu
void processMutacao(){ 
	unsigned char color[3];

	setColor(color, LIGHT_GREY);
	retangle(-0.40, 0.29, 0.4, 0.08, color);

	int right_shape = 0;
	int right_color = 0;	

	// Forma
	if (tipoGeme == 0 || tipoGeme == 2) 		
		for(int i=0; i<nro_indvidous; i++)
	  		if (mB[i].shape == SelecaoShapem)
				right_shape++ ;
	// Cor
	if (tipoGeme == 1 || tipoGeme == 0){
		if(SelecaoCorm == 0) 	// 0  -->	escuro/preto 	
			for(int i=0; i<nro_indvidous; i++){
		  		if (mB[i].r + mB[i].g + mB[i].b < 192)
					right_color++ ;
			}
		else 				// 1 > claro/branco	
			for(int i=0; i<nro_indvidous; i++){
		  		if (mB[i].r + mB[i].g + mB[i].b > 512)
					right_color++ ;
			}
	}
	
	if(tipoGeme == 0 || tipoGeme == 2){
		RenderString(-0.42, 0.28, "Forma:");
		RenderString(-0.25, 0.28, to_string(right_shape));
	}	
	
	if(tipoGeme == 0 || tipoGeme == 1){
		RenderString(-0.63, 0.28, "Cor:");
		RenderString(-0.53, 0.28, to_string(right_color));
	}

	if(mB.empty()) return;	

	// selecao
	for(int i=0; i<nro_indvidous; i++){
		
		if (mB[i].x > 0.3 && mB[i].x < 0.7 && mB[i].y < -0.3 && mB[i].y > -0.7){ // Zona de Selecao
				
			// forma			
			if (tipoGeme == 0 || tipoGeme == 2){
				if (mB[i].shape != SelecaoShapem){ 
					mB.erase(mB.begin()+i); 
					nro_indvidous--; 
					Repopulatem();
				}
			
			}
	
			// Cor
			if (tipoGeme == 1 || tipoGeme == 0){
				if(!SelecaoCorm){ // escuro/preto
					if(mB[i].r + mB[i].g + mB[i].b > 192) { 
						mB.erase(mB.begin()+i); 
						nro_indvidous--;					
						Repopulatem(); 
					}
				}else			   // claro/branco
					if(mB[i].r + mB[i].g + mB[i].b < 512) { 
						mB.erase(mB.begin()+i); 
						nro_indvidous--; 
						Repopulatem();
					}				
			}
 		}
		// bixinho não deletado pode mover
		moveBixinho(&mB[i], mB[i].vel);
	}
	
	return;
}

void Mutacao_buttons(int x, int y, unsigned short int *menu_state){
	unsigned char color[3];
	MChange = true;
	
	// voltar ao menu principal (<-- back)
	if (x > 30 && x < 150 && y > 25 && y < 60){
		nro_indvidous = 0;		
		*menu_state = 0; 
	
	// run	
	}else if (x > 290 && x < 380 && y > 830 && y < 875){		
		
		mB.clear(); 
		
		if(mB.empty() || (int)mB.size() < nro_indv_visual){ // cria bixinhos para serem desenhados
			int size = nro_indv_visual - mB.size();			
			for(int i=0; i<size; i++){
				setColor(color, rand()%256, rand()%256, rand()%256);
			
				Bixinho A = CreateBixinho((rand()%10/10.0) +0.02, ((rand()%20)-10)/10.0, color);
				mB.push_back(A);
			}
		}
		Mdraw = true;
	
	

	// Nro individuos menu
	}else if (y > 110 && y < 135){	
			if (x > 220 && x < 250) nro_indv_visual = 10;
			else if (x > 265 && x < 295) nro_indv_visual = 25;
			else if (x > 310 && x < 340) nro_indv_visual = 50;
			else if (x > 355 && x < 385) nro_indv_visual = 100;

	// gene menu	
	}else if (!MgeneMenu && x > 190 && x < 350 && y > 199 && y < 235){		
		MgeneMenu = true; 
		
	}else if (MgeneMenu && x > 360 && x < 430){
		if (y > 165 && y < 200) {
			MgeneMenu = false;
			tipoGeme = 1;  // cor		
		}else if (y > 200 && y < 235){
			MgeneMenu = false;
			tipoGeme = 2;  // forma		
		}else if (y > 235 && y < 270){
			MgeneMenu = false;
			tipoGeme = 0;  // cor e forma	
		}
		
	// selecao
	}else if (y > 245 && y < 275){	
			if (x > 165 && x < 195) Blue_Cor = 0; // preto
			else if (x > 200 && x < 230) Blue_Cor = 1; // branco
			else if (x > 255 && x < 285) Blue_Shape = 0; // circulo
			else if (x > 290 && x < 320) Blue_Shape = 1; // quadrado
			else if (x > 325 && x < 355) Blue_Shape = 2; // triangulo
	
	}else if (x > 155 && x < 185){	
			if (y > 335 && y < 365) Blue_reproducao = true;
			else if (y > 365 && y < 395) Blue_reproducao = false;
	
	// Next	
	}else if (x > 155 && x < 245 && y > 830 && y < 875){
		nro_indvidous = 0;
		*menu_state = *menu_state + 1;

	}
	MChange = true;
	return;
}















