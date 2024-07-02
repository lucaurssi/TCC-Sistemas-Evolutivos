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



void Genocidio(Sim_Var *SV){
	unsigned char color[3];
	
	setColor(color, WHITE);
	retangle(0.5, 0, 1, 2, color); 
	
	setColor(color, 255, 127, 127); 
	retangle(0.5, -0.5, 0.3, 0.3, color);
	
	
	if (SV->Run){ 
		SV->N 	    = SV->N_menu;
		SV->Gene 	= SV->Gene_menu;		
		SV->Shape   = SV->Shape_menu;
		SV->Cor     = SV->Cor_menu;
		SV->Breed   = SV->Breed_menu;
		SV->Mutation= SV->Mutation_menu;
		SV->Run 	= false;
				
	}
		
	if (!SV->Bixinhos.empty())
		for(int i=0; i < SV->N; i++)
			drawBixinho(SV->Bixinhos[i], SV->Gene);
	
	
	if(!SV->Change){
		setColor(color, LIGHT_GREY);		
		retangle(-0.012, 0, 0.027, 2, color);

	}else{
		SV->Change = false;
		draw_basic_menu("Genocide");
		
		nro_individuos(-0.95, 0.7,SV->N_menu);
		tipo_de_gene(-0.95, 0.5, SV->Gene_menu, SV->geneMenu);	
		draw_Selecao(-0.95, 0.4, SV->Gene_menu, SV->Shape_menu, SV->Cor_menu);
		draw_Reproducao(-0.95, 0.2, SV->Breed_menu);
        draw_Mutacao(-0.95, 0, SV->Mutation_menu);
	}

	if (SV->N){
		setColor(color, GREY);
		retangle(-0.55, -0.9, 0.2, 0.09, color);
		
		RenderString(-0.62, -0.92, "Next");
	}

	

	return;
}		


void processGenocidio(Sim_Var *SV){ 
	unsigned char color[3];

	setColor(color, LIGHT_GREY);
	retangle(-0.40, 0.29, 0.4, 0.08, color);

	int right_shape = 0;
	int right_color = 0;	

	// Form
	if (SV->Gene_menu == 0 || SV->Gene_menu == 2) 		
		for(int i=0; i<SV->N; i++)
	  		if (SV->Bixinhos[i].shape == SV->Shape)
				right_shape++ ;
	// Color
	if (SV->Gene_menu == 1 || SV->Gene_menu == 0){
		if(SV->Cor == 0)	
			for(int i=0; i<SV->N; i++){
		  		if (SV->Bixinhos[i].r + SV->Bixinhos[i].g + SV->Bixinhos[i].b < 192)
					right_color++ ;
			}
		else 
			for(int i=0; i<SV->N; i++){
		  		if (SV->Bixinhos[i].r + SV->Bixinhos[i].g + SV->Bixinhos[i].b > 512)
					right_color++ ;
			}
	}
	
	if(SV->Gene_menu == 0 || SV->Gene_menu == 2){
		RenderString(-0.42, 0.28, "Form:");
		RenderString(-0.25, 0.28, to_string(right_shape));
	}	
	
	if(SV->Gene_menu == 0 || SV->Gene_menu == 1){
		RenderString(-0.63, 0.28, "Cor:");
		RenderString(-0.53, 0.28, to_string(right_color));
	}

	if(SV->Bixinhos.empty()) return;	

	// selection
	for(int i=0; i<SV->N; i++){
		if (SV->Bixinhos[i].x > 0.3 && SV->Bixinhos[i].x < 0.7 && SV->Bixinhos[i].y < -0.3 && SV->Bixinhos[i].y > -0.7){ 
				
			// form		
			if (SV->Gene_menu == 0 || SV->Gene_menu == 2){
				if (SV->Bixinhos[i].shape != SV->Shape){ 
					SV->Bixinhos.erase(SV->Bixinhos.begin()+i); 
					SV->N--; 
					Repopulate(SV, true); // true on the mutation flag
				}
			
			}
	
			// Color
			if (SV->Gene_menu == 1 || SV->Gene_menu == 0){
				if(!SV->Cor){ 
					if(SV->Bixinhos[i].r + SV->Bixinhos[i].g + SV->Bixinhos[i].b > 192) { 
						SV->Bixinhos.erase(SV->Bixinhos.begin()+i); 
						SV->N--;					
						Repopulate(SV, true); 
					}
				}else
					if(SV->Bixinhos[i].r + SV->Bixinhos[i].g + SV->Bixinhos[i].b < 512) { 
						SV->Bixinhos.erase(SV->Bixinhos.begin()+i); 
						SV->N--; 
						Repopulate(SV, true);
					}				
			}
 		}
		moveBixinho(&SV->Bixinhos[i], SV->Bixinhos[i].vel);
	}
	return;
}

void Genocidio_buttons(int x, int y, char *menu_state, Sim_Var *SV){
	unsigned char color[3];
	SV->Change = true;
	
	// back
	if (x > 30 && x < 150 && y > 25 && y < 60){
		SV->N = 0;		
		*menu_state = 0; 
	
	// run	
	}else if (x > 290 && x < 380 && y > 830 && y < 875){		
		
		SV->Bixinhos.clear(); 
		
		if(SV->Bixinhos.empty() || (int)SV->Bixinhos.size() < SV->N_menu){
			int size = SV->N_menu - SV->Bixinhos.size();			
			for(int i=0; i<size; i++){
				setColor(color, rand()%256, rand()%256, rand()%256);
			
				Bixinho A = CreateBixinho((rand()%10/10.0) +0.02, ((rand()%20)-10)/10.0, color);
				SV->Bixinhos.push_back(A);
			}
		}
		SV->Run = true;
	

	// Nro individuos menu
	}else if (y > 110 && y < 135){	
			if (x > 220 && x < 250) SV->N_menu = 10;
			else if (x > 265 && x < 295) SV->N_menu = 25;
			else if (x > 310 && x < 340) SV->N_menu = 50;
			else if (x > 355 && x < 385) SV->N_menu = 100;

	// gene menu	
	}else if (!SV->geneMenu && x > 190 && x < 350 && y > 199 && y < 235){		
		SV->geneMenu = true; 
		
	}else if (SV->geneMenu && x > 360 && x < 430){
		if (y > 165 && y < 200) {
			SV->geneMenu = false;
			SV->Gene_menu = 1;  // color		
		}else if (y > 200 && y < 235){
			SV->geneMenu = false;
			SV->Gene_menu = 2;  // form		
		}else if (y > 235 && y < 270){
			SV->geneMenu = false;
			SV->Gene_menu = 0;  // color & form
		}
		
	// selecao
	}else if (y > 245 && y < 275){	
			if (x > 165 && x < 195) SV->Cor_menu = 0; 
			else if (x > 200 && x < 230) SV->Cor_menu = 1;
			else if (x > 255 && x < 285) SV->Shape_menu = 0; 
			else if (x > 290 && x < 320) SV->Shape_menu = 1; 
			else if (x > 325 && x < 355) SV->Shape_menu = 2; 
	
	}else if (x > 155 && x < 185 && y < 395){	
			if (y > 335 && y < 365) SV->Breed_menu = true;
			else if (y > 365 && y < 395) SV->Breed_menu = false;

	}else if (y > 430 && y < 455){	
			if (x > 145 && x < 175) SV->Mutation_menu = true;
			else if (x > 255 && x < 285) SV->Mutation_menu = false;
	
	// Next	
	}else if (x > 155 && x < 245 && y > 830 && y < 875){
		SV->N = 0;
		*menu_state = *menu_state + 1;
	}

	SV->Change = true;
	return;
}















