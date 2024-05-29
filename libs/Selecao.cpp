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


vector<Bixinho> Bs;
int nro_visual_indv = 10;
int nro_indv = 0;

int tipoGenes = 2;
int G_s = 1;

int SelecaoShape = 0;
bool SelecaoCor = false;

int blue_shape = 0;
bool blue_cor = false;

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


void Selecao(){
	unsigned char color[3];
	
	setColor(color, WHITE);
	retangle(0.5, 0, 1, 2, color); // limpa bixinhos
	
	setColor(color, 255, 127, 127); // vermelho claro
	retangle(0.5, -0.5, 0.3, 0.3, color); // quadrado de selecao
	
	RenderString(0.4, -0.45, "Selecao");
	
	
	if (Sdraw){ 
		nro_indv 	= nro_visual_indv;
		G_s 		= tipoGenes;		
		SelecaoShape = blue_shape;
		SelecaoCor 	= blue_cor;
		Sdraw 		= false;		
	}
		
	if (!Bs.empty())
		for(int i=0; i < nro_indv; i++)
			drawBixinho(Bs[i], G_s);
	
	
	if(!SChange){// se nao apertar nada no menu, não precisa re-escrever o menu
		setColor(color, LIGHT_GREY);		
		retangle(-0.012, 0, 0.027, 2, color);

	}else{
		SChange = false;
		draw_basic_menu("Selecao");
		
		nro_individuos(-0.95, 0.7,nro_visual_indv);
		tipo_de_gene(-0.95, 0.5, tipoGenes, SgeneMenu);	
		draw_Selecao(-0.95, 0.4, tipoGenes, blue_shape, blue_cor);
	}

	if (nro_indv){ // se atualizar clicando no run, abilita o botao NEXT
		setColor(color, GREY);
		retangle(-0.55, -0.9, 0.2, 0.09, color);
		
		RenderString(-0.62, -0.92, "Next");
	}

	return;
}		


// move os bixinhos na tela de menu
void processSelecao(){ 

	if(Bs.empty()) return;	

	// selecao
	for(int i=0; i<nro_indv; i++){
		
		if (Bs[i].x > 0.3 && Bs[i].x < 0.7 && Bs[i].y < -0.3 && Bs[i].y > -0.7){ // Zona de Selecao
				
			// forma			
			if (tipoGenes == 0 || tipoGenes == 2){
				if (Bs[i].shape != SelecaoShape){ 
					Bs.erase(Bs.begin()+i); 
					nro_indv--; 
				}
			
			}
	
			// Cor
			if (tipoGenes == 1 || tipoGenes == 0){
				if(!SelecaoCor){ // escuro/preto
					if(Bs[i].r + Bs[i].g + Bs[i].b > 192) { Bs.erase(Bs.begin()+i); nro_indv--; }
				}else			   // claro/branco
					if(Bs[i].r + Bs[i].g + Bs[i].b < 512) { Bs.erase(Bs.begin()+i); nro_indv--; }
			}
 		}
		// bixinho não deletado pode mover
		moveBixinho(&Bs[i], Bs[i].vel);
	}
	
	return;
}

void Selecao_buttons(int x, int y, unsigned short int *menu_state){
	unsigned char color[3];
	SChange = true;
	
	// voltar ao menu principal (<-- back)
	if (x > 30 && x < 150 && y > 25 && y < 60){
		nro_indv = 0;		
		*menu_state = 0; 
	
	// run	
	}else if (x > 290 && x < 380 && y > 830 && y < 875){		
		Bs.clear();
		if(Bs.empty() || (int)Bs.size() < nro_visual_indv){ // cria bixinhos para serem desenhados
			int size = nro_visual_indv - Bs.size();			
			for(int i=0; i<size; i++){
				setColor(color, rand()%256, rand()%256, rand()%256);
			
				Bixinho A = CreateBixinho((rand()%10/10.0) +0.02, ((rand()%20)-10)/10.0, color);
				Bs.push_back(A);
			}
		}
		Sdraw = true;
	
	// Next	
	}else if (x > 155 && x < 245 && y > 830 && y < 875){
		nro_indv = 0;
		*menu_state = *menu_state + 1;

	// Nro individuos menu
	}else if (y > 110 && y < 135){	
			if (x > 220 && x < 250) nro_visual_indv = 10;
			else if (x > 265 && x < 295) nro_visual_indv = 25;
			else if (x > 310 && x < 340) nro_visual_indv = 50;
			else if (x > 355 && x < 385) nro_visual_indv = 100;
			

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
			if (x > 165 && x < 195) blue_cor = 0; // preto
			else if (x > 200 && x < 230) blue_cor = 1; // branco
			else if (x > 255 && x < 285) blue_shape = 0; // circulo
			else if (x > 290 && x < 320) blue_shape = 1; // quadrado
			else if (x > 325 && x < 355) blue_shape = 2; // triangulo
	}

	SChange = true;
	return;
}















