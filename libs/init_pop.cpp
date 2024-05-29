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

using namespace std;


vector<Bixinho> Bips;
int n_Bips = 10;
int N_ip = 0;

int tipoGene = 1;
int G_ip = 1;


bool IPChange = true;
bool IPdraw = false;
bool IPnextPhase = false;
bool geneMenu = false;


void init_pop(){
	unsigned char color[3];
	
	setColor(color, WHITE);
	retangle(0.5, 0, 1, 2, color); // limpa bixinhos
	
	
	if (IPdraw){ 
		N_ip = n_Bips;
		G_ip = tipoGene;		
		IPdraw = false;	
		
	}

	if (!Bips.empty())
		for(int i=0; i < N_ip; i++)
			drawBixinho(Bips[i], G_ip);
	
	// ---- menu ----
	

	// cinza
	setColor(color, LIGHT_GREY);
	
	if(!IPChange){// se nao apertar nada no menu, não precisa re-escrever o menu
		retangle(-0.012, 0, 0.027, 2, color);
		

	}else{
		IPChange = false;
		
		retangle(-0.5, 0, 1, 2, color); // pinta metade da tela de cinza
		

		
		setColor(color, GREY); // cinza escuro
		retangle(-0.8, 0.9, 0.25, 0.075, color); 
		RenderString(-0.91, 0.88, "<-- Back");

		RenderString(-0.6, 0.88, "População inicial");

		RenderString(-0.95, 0.65, "O primeiro passo para simular um sistema");
		RenderString(-0.95, 0.60, "evolutivo eh iniciar uma população, o que");
		RenderString(-0.95, 0.55, "significa escolher o numero de individuos");
		RenderString(-0.95, 0.50, "a serem simulados:");
		


		// Componente do menu que escolhe o numero de individuos
		nro_individuos(-0.95, 0.4, n_Bips);


		
		RenderString(-0.95, 0.25, "O segundo passo eh decidir o que sera");
		RenderString(-0.95, 0.20, "simulado. No caso desse exemplo temos");
		RenderString(-0.95, 0.15, "cor e formas de bixinhos.");



		tipo_de_gene(-0.95, 0, tipoGene, geneMenu);	



		RenderString(-0.95, -0.30, "Escolha os genes e o numero de ");
		RenderString(-0.95, -0.35, "individuos acima e clique em 'Run'.");

	// --------------------------------------------------

		// --------- Run Button -----------------
		setColor(color, GREY);
		retangle(-0.25, -0.9, 0.2, 0.09, color);
		
		RenderString(-0.3, -0.92, "Run");
		// --------------------------------------

		if (N_ip){ // se atualizar clicando no run, abilita o botao NEXT
			setColor(color, GREY);
			retangle(-0.55, -0.9, 0.2, 0.09, color); 
			
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
  		moveBixinho(&Bips[i], Bips[i].vel);

	return;
}

void IPop_buttons(int x, int y, unsigned short int *menu_state){
	unsigned char color[3];
	IPChange = true;
	
	// voltar ao menu principal (<-- back)
	if (x > 30 && x < 150 && y > 25 && y < 60){
		N_ip = 0;
		*menu_state = 0; 
	
	// run	
	}else if (x > 290 && x < 380 && y > 830 && y < 875){		
		if(Bips.empty()) // cria bixinhos para serem desenhados
			for(int i=0; i<n_Bips; i++){
				setColor(color, rand()%256, rand()%256, rand()%256);
			
				Bixinho A = CreateBixinho(rand()%10/10.0, ((rand()%20)-10)/10.0, color);
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
				setColor(color, rand()%256, rand()%256, rand()%256);
			
				Bixinho A = CreateBixinho((rand()%10/10.0) +0.02, ((rand()%20)-10)/10.0, color);
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















