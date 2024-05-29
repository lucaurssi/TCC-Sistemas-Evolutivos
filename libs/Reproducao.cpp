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


vector<Bixinho> Bc;

int n_Bc = 10;
int N_c = 0;

int tipoGenec = 2;
int G_c = 1;

int SelecaoShapec = 0;
int SelecaoCorc = 0;

int CShape = 0;
int CCor = 0;

bool blue_reproducao = true;
bool SelecaoReproducao = true;

// rename to menu_change_flag
bool CChange = true; // indica que ouve um click e deve redesenhar o menu

// rename to run_flag
bool Cdraw = false; // run foi clicado e deve iniciar a simulacao

bool CnextPhase = false; // run foi clicado, bottao de next aparece

bool CgeneMenu = false; // flag para desenhar o menu de multipla escolha de genes


void Reproducao(){
	unsigned char color[3];
	
	setColor(color, WHITE);
	retangle(0.5, 0, 1, 2, color); // limpa bixinhos
	
	setColor(color, 255, 127, 127); // vermelho claro
	retangle(0.5, -0.5, 0.3, 0.3, color); // quadrado de selecao
	
	
	if (Cdraw){ 
		N_c 		= n_Bc;
		G_c 		= tipoGenec;		
		SelecaoShapec = CShape;
		SelecaoCorc = CCor;
		SelecaoReproducao = blue_reproducao;
		Cdraw 		= false;
				
	}
		
	if (!Bc.empty())
		for(int i=0; i < N_c; i++)
			drawBixinho(Bc[i], G_c);
	
	
	if(!CChange){// se nao apertar nada no menu, não precisa re-escrever o menu
		setColor(color, LIGHT_GREY);		
		retangle(-0.012, 0, 0.027, 2, color);

	}else{
		CChange = false;
		draw_basic_menu("Reproducao");
		
		nro_individuos(-0.95, 0.7,n_Bc);
		tipo_de_gene(-0.95, 0.5, tipoGenec, CgeneMenu);	
		draw_Selecao(-0.95, 0.4, tipoGenec, CShape, CCor);
		draw_Reproducao(-0.95, 0.2, blue_reproducao);

	}

	if (N_c){ // se atualizar clicando no run, abilita o botao NEXT
		setColor(color, GREY);
		retangle(-0.55, -0.9, 0.2, 0.09, color);
		
		RenderString(-0.62, -0.92, "Next");
	}

	

	return;
}		


void Repopulate(){
	char random_indv = rand()%N_c;
	Bixinho A;

	if (SelecaoReproducao)
		A = Bc[random_indv];
	
	else{	
		char random_indv2 = rand()%N_c;

		A.radius = 0.05;
		A.x = Bc[random_indv].x;
		A.y = Bc[random_indv2].y;
		A.theta = ((rand()%20)-10)/10.0;
		A.r = (Bc[random_indv].r + Bc[random_indv2].r)/2;
		A.g = (Bc[random_indv].g + Bc[random_indv2].g)/2;
		A.b = (Bc[random_indv].b + Bc[random_indv2].b)/2;
		A.vel = 0.010;

		if(rand()%2) A.shape = Bc[random_indv].shape;
		else A.shape = Bc[random_indv2].shape;		
	}

	Bc.push_back(A);
	N_c++; 
}

// move os bixinhos na tela de menu
void processReproducao(){ 
	unsigned char color[3];

	setColor(color, LIGHT_GREY);
	retangle(-0.40, 0.29, 0.4, 0.08, color);

	int right_shape = 0;
	int right_color = 0;	

	// Forma
	if (tipoGenec == 0 || tipoGenec == 2) 		
		for(int i=0; i<N_c; i++)
	  		if (Bc[i].shape == SelecaoShapec)
				right_shape++ ;
	// Cor
	if (tipoGenec == 1 || tipoGenec == 0){
		if(SelecaoCorc == 0) 	// 0  -->	escuro/preto 	
			for(int i=0; i<N_c; i++){
		  		if (Bc[i].r + Bc[i].g + Bc[i].b < 192)
					right_color++ ;
			}
		else 				// 1 > claro/branco	
			for(int i=0; i<N_c; i++){
		  		if (Bc[i].r + Bc[i].g + Bc[i].b > 512)
					right_color++ ;
			}
	}
	
	if(tipoGenec == 0 || tipoGenec == 2){
		RenderString(-0.42, 0.28, "Forma:");
		RenderString(-0.25, 0.28, to_string(right_shape));
	}	
	
	if(tipoGenec == 0 || tipoGenec == 1){
		RenderString(-0.63, 0.28, "Cor:");
		RenderString(-0.53, 0.28, to_string(right_color));
	}

	if(Bc.empty()) return;	

	// selecao
	for(int i=0; i<N_c; i++){
		
		if (Bc[i].x > 0.3 && Bc[i].x < 0.7 && Bc[i].y < -0.3 && Bc[i].y > -0.7){ // Zona de Selecao
				
			// forma			
			if (tipoGenec == 0 || tipoGenec == 2){
				if (Bc[i].shape != SelecaoShapec){ 
					Bc.erase(Bc.begin()+i); 
					N_c--; 
					Repopulate();
				}
			
			}
	
			// Cor
			if (tipoGenec == 1 || tipoGenec == 0){
				if(!SelecaoCorc){ // escuro/preto
					if(Bc[i].r + Bc[i].g + Bc[i].b > 192) { 
						Bc.erase(Bc.begin()+i); 
						N_c--;					
						Repopulate(); 
					}
				}else			   // claro/branco
					if(Bc[i].r + Bc[i].g + Bc[i].b < 512) { 
						Bc.erase(Bc.begin()+i); 
						N_c--; 
						Repopulate();
					}				
			}
 		}
		// bixinho não deletado pode mover
		moveBixinho(&Bc[i], Bc[i].vel);
	}
	
	return;
}

void Reproducao_buttons(int x, int y, unsigned short int *menu_state){
	unsigned char color[3];
	CChange = true;
	
	// voltar ao menu principal (<-- back)
	if (x > 30 && x < 150 && y > 25 && y < 60){
		N_c = 0;		
		*menu_state = 0; 
	
	// run	
	}else if (x > 290 && x < 380 && y > 830 && y < 875){		
		
		Bc.clear(); 
		
		if(Bc.empty() || (int)Bc.size() < n_Bc){ // cria bixinhos para serem desenhados
			int size = n_Bc - Bc.size();			
			for(int i=0; i<size; i++){
				setColor(color, rand()%256, rand()%256, rand()%256);
			
				Bixinho A = CreateBixinho((rand()%10/10.0) +0.02, ((rand()%20)-10)/10.0, color);
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
	
	}else if (x > 155 && x < 185){	
			if (y > 335 && y < 365) blue_reproducao = true;
			else if (y > 365 && y < 395) blue_reproducao = false;
	
	// Next	
	}else if (x > 155 && x < 245 && y > 830 && y < 875){
		N_c = 0;
		*menu_state = *menu_state + 1;
	}

	CChange = true;
	return;
}















