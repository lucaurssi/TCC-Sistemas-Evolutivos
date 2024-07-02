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


void init_pop(Sim_Var *SV){
	unsigned char color[3];
	
	setColor(color, WHITE);
	retangle(0.5, 0, 1, 2, color); 
	
	
	if (SV->Run){ 
		SV->N = SV->N_menu;
		SV->Gene = SV->Gene_menu;		
		SV->Run = false;	
		
	}
	if (!SV->Bixinhos.empty())
		for(int i=0; i < SV->N; i++)
			drawBixinho(SV->Bixinhos[i], SV->Gene);
	
	// ---- menu ----
	
	setColor(color, LIGHT_GREY);
	
	if(!SV->Change){
		retangle(-0.012, 0, 0.027, 2, color);
		
	}else{
		SV->Change = false;
		
		retangle(-0.5, 0, 1, 2, color); 
		

		
		setColor(color, GREY);
		retangle(-0.8, 0.9, 0.25, 0.075, color); 
		RenderString(-0.91, 0.88, "<-- Back");

		RenderString(-0.6, 0.88, "Initial Population");

	
		nro_individuos(-0.95, 0.4, SV->N_menu);
		tipo_de_gene(-0.95, 0, SV->Gene_menu, SV->geneMenu);	

		RenderString(-0.95, -0.30, "Choose the genes, the number ");
		RenderString(-0.95, -0.35, "individuals and click Run.");

	// --------------------------------------------------

		// --------- Run Button -----------------
		setColor(color, GREY);
		retangle(-0.25, -0.9, 0.2, 0.09, color);
		
		RenderString(-0.3, -0.92, "Run");
		// --------------------------------------

		if (SV->N){ // ''Next'' button apears after clicking run 
			setColor(color, GREY);
			retangle(-0.55, -0.9, 0.2, 0.09, color); 
			
			RenderString(-0.62, -0.92, "Next");
			RenderString(-0.95, -0.75, "Click on Next bellow.");
		}
	}
	return;
}		

void processIPop(Sim_Var *SV){ 
	if(SV->Bixinhos.empty()) return;	

	for(int i=0; i<SV->N; i++)
  		moveBixinho(&SV->Bixinhos[i], SV->Bixinhos[i].vel);

	return;
}

void IPop_buttons(int x, int y, char *menu_state, Sim_Var *SV){
	unsigned char color[3];
	SV->Change = true;
	
	// <-- back
	if (x > 30 && x < 150 && y > 25 && y < 60){
		SV->N = 0;
		*menu_state = 0; 
	
	// run	
	}else if (x > 290 && x < 380 && y > 830 && y < 875){		
		if(SV->Bixinhos.empty())
			for(int i=0; i<SV->N_menu; i++){
				setColor(color, rand()%256, rand()%256, rand()%256);
			
				Bixinho A = CreateBixinho(rand()%10/10.0, ((rand()%20)-10)/10.0, color);
				SV->Bixinhos.push_back(A);
			}
		SV->Run = true;

	// Next	
	}else if (x > 155 && x < 245 && y > 830 && y < 875){
		SV->N =0;
		*menu_state = *menu_state + 1;

	// Nro individuos menu
	}else if (y > 245 && y < 275){	
			if (x > 220 && x < 250) SV->N_menu = 10;
			else if (x > 265 && x < 295) SV->N_menu = 25;
			else if (x > 310 && x < 340) SV->N_menu = 50;
			else if (x > 355 && x < 385) SV->N_menu = 100;
			
			int size = SV->N_menu - SV->Bixinhos.size(); 			
			for(int i=0; i<size; i++){
				setColor(color, rand()%256, rand()%256, rand()%256);
			
				Bixinho A = CreateBixinho((rand()%10/10.0) +0.02, ((rand()%20)-10)/10.0, color);
				SV->Bixinhos.push_back(A);
			}

	// gene menu	
	}else if (!SV->geneMenu && x > 190 && x < 350 && y > 420 && y < 460)		
		SV->geneMenu = true; 
		
	else if (SV->geneMenu && x > 360 && x < 430){
		if (y > 390 && y < 425) {
			SV->geneMenu = false;
			SV->Gene_menu = 1;  // color		
		}else if (y > 425 && y < 460){
			SV->geneMenu = false;
			SV->Gene_menu = 2;  // form		
		}else if (y > 460 && y < 495){
			SV->geneMenu = false;
			SV->Gene_menu = 0;  // color e form
		}
		
	}

	SV->Change = true;
	return;
}















