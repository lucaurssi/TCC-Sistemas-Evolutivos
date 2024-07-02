#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include "drawings.h"
#include "Bixinhos.h"

#include <math.h>
#include <vector>
using namespace std;


void main_menu( Sim_Var* SV ){
	unsigned char color[3];

	setColor(color, 255, 255, 255);
	retangle(0.5, 0, 1, 2, color); // clear right side of screen

	if(SV->Bixinhos.empty()) // create 'bixinhos''
		for(int i=0; i<10; i++){
			setColor(color, rand()%256, rand()%256, rand()%256);
		
			Bixinho A = CreateBixinho(rand()%10/10.0, ((rand()%20)-10)/10.0, color);
			SV->Bixinhos.push_back(A);
		}

	
	for(int i=0; i<10; i++)
		drawBixinho(SV->Bixinhos[i], 0);
	
	// ---- menu ----

	setColor(color, LIGHT_GREY);
	
	if(!SV->Change){// only draw menu if it was interacted with
		retangle(-0.014, 0, 0.026, 2, color);
		

	}else{
		SV->Change = false;

		setColor(color, LIGHT_GREY);
		retangle(-0.5, 0, 1, 2, color); // paint left side with grey
		
		setColor(color, GREY);

		retangle(-0.6, 0.8, 0.4, 0.1, color);
		RenderString(-0.79, 0.78, "Initial Population");

		retangle(-0.6, 0.6, 0.4, 0.1, color);
		RenderString(-0.79, 0.58, "Selection");

		retangle(-0.6, 0.4, 0.4, 0.1, color);
		RenderString(-0.79, 0.38, "Reproduction");

		retangle(-0.6, 0.2, 0.4, 0.1, color);
		RenderString(-0.79, 0.18, "Mutation");

		retangle(-0.6, 0, 0.4, 0.1, color);
		RenderString(-0.79, -0.02, "Genocide");
	}
	return;
}		


void processMenu( Sim_Var* SV ){ 
	if(SV->Bixinhos.empty()) return;	

	for(int i=0; i<10; i++)
  		moveBixinho(&SV->Bixinhos[i], SV->Bixinhos[i].vel);
	return;

}

void menu_buttons(int x, int y, char *menu_state, Sim_Var* SV ){
	if (x > 270 || x < 90) return; // left and right of buttons

	if (y < 112 && y > 65 ){
		*menu_state = 1; 
		SV->Change = true;
	}else if (y < 200 && y > 150 ){
		*menu_state = 2; 
		SV->Change = true;
	}else if (y < 290 && y > 245 ){
		*menu_state = 3; 
		SV->Change = true;
	}else if (y < 385 && y > 335 ){
		*menu_state = 4; 
		SV->Change = true;
	}else if (y < 475 && y > 430 ){
		*menu_state = 5; 
		SV->Change = true;
	}

	return;
}



