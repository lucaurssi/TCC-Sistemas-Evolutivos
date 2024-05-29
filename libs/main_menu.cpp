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


vector<Bixinho> Bms;
bool menuChange = true;

void main_menu(){
	unsigned char color[3];

	setColor(color, 255, 255, 255);
	retangle(0.5, 0, 1, 2, color); // limpa bixinhos

	if(Bms.empty()) // cria bixinhos para serem desenhados
		for(int i=0; i<10; i++){
			setColor(color, rand()%256, rand()%256, rand()%256);
		
			Bixinho A = CreateBixinho(rand()%10/10.0, ((rand()%20)-10)/10.0, color);
			Bms.push_back(A);
		}

	
	for(int i=0; i<10; i++)
		drawBixinho(Bms[i], 0);
	
	// ---- menu ----

	setColor(color, LIGHT_GREY);
	
	if(!menuChange){// se nao apertar nada no menu, não precisa re-escrever o menu
		retangle(-0.014, 0, 0.026, 2, color); // limpa 
		

	}else{
	// cinza
		menuChange = false;

		setColor(color, LIGHT_GREY);
		retangle(-0.5, 0, 1, 2, color); // pinta metade da tela de cinza
		

		// cinza, um pouco mais escuro
		setColor(color, GREY);

		retangle(-0.6, 0.8, 0.4, 0.1, color);
		RenderString(-0.79, 0.78, "População inicial");

		retangle(-0.6, 0.6, 0.4, 0.1, color);
		RenderString(-0.79, 0.58, "Selecao");

		retangle(-0.6, 0.4, 0.4, 0.1, color);
		RenderString(-0.79, 0.38, "Reproducao");
	}
	return;
}		

// move os bixinhos na tela de menu
void processMenu(){ 
	if(Bms.empty()) return;	

	// Para mover os bixinhos
	for(int i=0; i<10; i++)
  		moveBixinho(&Bms[i], Bms[i].vel);
	return;

}

void menu_buttons(int x, int y, unsigned short int *menu_state){
	if (x > 270 || x < 90) return; // esquerda e direta dos botoes

	if (y < 112 && y > 65 ){
		*menu_state = 1; // Iniciar Populacao
		menuChange = true;
	}else if (y < 200 && y > 150 ){
		*menu_state = 2; // Selecao
		menuChange = true;
	}else if (y < 290 && y > 245 ){
		*menu_state = 3; // Crossover
		menuChange = true;
	}

	return;
}



