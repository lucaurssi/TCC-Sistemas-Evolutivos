#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


#include "libs/Bixinhos.h"
#include "libs/main_menu.h"
#include "libs/drawings.h"
#include "libs/init_pop.h"
#include "libs/Selecao.h"
#include "libs/Reproducao.h"
#include "libs/Mutacao.h"
#include "libs/Genocidio.h"

#include <vector>
#include <iostream>

using namespace std;

#define windowWidth 900
#define windowHeight 900



char menu_state = 0;
bool DEBUG = true;

// SV doesn't initialize Bixinhos, the line below supress the warning.
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

// ''Sim_Var'' is declared in Bixinhos.h for convenience
Sim_Var SV = { 
    .N = 0, .N_menu = 10,
    .Gene = 1, .Gene_menu = 1,
    .geneMenu = false,
    .Shape = 0, .Shape_menu = 0,
    .Cor = false, .Cor_menu = false,
    .Breed = true, .Breed_menu = true,
    .Mutation = true, .Mutation_menu = true,
    .Change = true,
    .Run = false,
 };

void interface(){
	//glClear(GL_COLOR_BUFFER_BIT);

	switch (menu_state){
		case 0: main_menu(&SV);
			break;
		case 1:	init_pop(&SV);
			break;
		case 2: Selecao(&SV);
			break;
		case 3:	Reproducao(&SV);
			break;
		case 4:	Mutacao(&SV);
            break;
		case 5:	Genocidio(&SV);
			break;
		default: menu_state = 0;
	}	
    glutSwapBuffers();	
	return;
}

void processInterface(){
	switch (menu_state){
		case 0:	processMenu(&SV);
			break;
		case 1:	processIPop(&SV);
			break;
		case 2:	processSelecao(&SV);
			break;
		case 3: processReproducao(&SV);
			break;
		case 4:	processMutacao(&SV);
			break;
		case 5:	processGenocidio(&SV);
			break;
	}
	return;
}

void button_click(int button, int state, int x, int y){
		
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		if(DEBUG) 
			cout << "mouse: "<< x << ' '<< y << '\n';
		
		switch (menu_state){
			case 0: menu_buttons(x, y, &menu_state, &SV);
				break;
			case 1: IPop_buttons(x, y, &menu_state, &SV);
				break;
			case 2: Selecao_buttons(x, y, &menu_state, &SV);
				break;
			case 3: Reproducao_buttons(x, y, &menu_state, &SV);
				break;
			case 4:	Mutacao_buttons(x, y, &menu_state, &SV);
				break;
			case 5:	Genocidio_buttons(x, y, &menu_state, &SV);
				break;
		}
	}
	return;
}


void timer(int){

	processInterface();

	glutPostRedisplay();
	glutTimerFunc(1000/30, timer, 0);
}

int main(int argc, char** argv){
  
    //----- Create Window -----//
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("TCC");
    glClearColor(1.0, 1.0, 1.0, 1.0);// clear screen

    glutDisplayFunc(interface);// defining drawing function

    glutTimerFunc(0, timer, 0); // clock, processing function here

	glutMouseFunc(button_click);// mouse click handler

    glutMainLoop();
    return 0;
}



