#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "main_menu.h"
#include "drawings.h"
#include "init_pop.h"

#include <vector>
#include <iostream>


using namespace std;

unsigned short int menu_state = 0;
bool DEBUG = true;

void interface(){
	glClear(GL_COLOR_BUFFER_BIT);

	switch (menu_state){
		case 0:
			main_menu();
			break;

		case 1:
			init_pop();
			break;

		default:
			cout << "E: unknown menu_state.\n" ;
			menu_state = 0;
			return;
	}
	
    glutSwapBuffers();	
	return;
}



void processInterface(){

	switch (menu_state){
		case 0:
			processMenu();
			break;

		case 1:
			processIPop();
			break;

		default:
			cout << "E: unknown menu_state on processInterface()\n" ;
			menu_state = 0;
			return;
	}
	return;
}


void button_click(int button, int state, int x, int y){
		
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){

		// imprime posicao do click caso DEBUG seja 'true'
		if(DEBUG) cout << "mouse: "<< x << ' '<< y << '\n';
		
		switch (menu_state){
			case 0:
				menu_buttons(x, y, &menu_state);
				break;

			case 1:
				IPop_buttons(x, y, &menu_state);
				break;

			default:
				cout << "E: unknown menu_state on button_click()\n" ;
				menu_state = 0;
				return;
		}
		
	}
	return;
}



