#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "libs/main_menu.h"
#include "libs/drawings.h"
#include "libs/init_pop.h"
#include "libs/Selecao.h"
#include "libs/Reproducao.h"
#include "libs/Mutacao.h"

#include <vector>
#include <iostream>

using namespace std;

#define windowWidth 900
#define windowHeight 900

unsigned short int menu_state = 0;
bool DEBUG = true;






/*

move repopulate() to bixinhos.h

mutação fixa e variada aqui

*/











void interface(){
	//glClear(GL_COLOR_BUFFER_BIT);

	switch (menu_state){
		case 0: main_menu();
			break;
		case 1:	init_pop();
			break;
		case 2: Selecao();
			break;
		case 3:	Reproducao();
			break;
		case 4:	Mutacao();
			break;
		default: menu_state = 0;
	}	
    glutSwapBuffers();	
	return;
}

void processInterface(){
	switch (menu_state){
		case 0:	processMenu();
			break;
		case 1:	processIPop();
			break;
		case 2:	processSelecao();
			break;
		case 3: processReproducao();
			break;
		case 4:	processMutacao();
			break;
	}
	return;
}

void button_click(int button, int state, int x, int y){
		
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		if(DEBUG) 
			cout << "mouse: "<< x << ' '<< y << '\n';
		
		switch (menu_state){
			case 0: menu_buttons(x, y, &menu_state);
				break;
			case 1: IPop_buttons(x, y, &menu_state);
				break;
			case 2: Selecao_buttons(x, y, &menu_state);
				break;
			case 3: Reproducao_buttons(x, y, &menu_state);
				break;
			case 4:	Mutacao_buttons(x, y, &menu_state);
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
  
    //----- Criar janela -----//
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("TCC");
    glClearColor(1.0, 1.0, 1.0, 1.0);// Limpa a tela (red, green, blue, alpha)

    glutDisplayFunc(interface);// Define qual função irá desenhar

    glutTimerFunc(0, timer, 0); // clock

	glutMouseFunc(button_click);// É chamada quando ocorre cliques na tela

    glutMainLoop();
    return 0;
}



