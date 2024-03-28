#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "drawings.h"
#include <math.h>
#include <vector>

using namespace std;

float color[3] = {0.9, 0.5, 0.7}; //cinza

vector<Bixinho> Bixinhos;

void menu(){
	if(Bixinhos.empty()){
		for(int i=0; i<10; i++){
			color[0] = (rand()%255)/255.0;
			color[1] = (rand()%255)/255.0;
			color[2] = (rand()%255)/255.0;
		
			Bixinho A = CreateBixinho(rand()%10/10.0, ((rand()%20)-10)/10.0, color);
			Bixinhos.push_back(A);
		}
	}
	
	for(int i=0; i<10; i++)
		drawBixinho(Bixinhos[i]);
	
	// ---- menu ----

	color[0] = 0.7; // cinza mais escuro
	color[1] = 0.7;
	color[2] = 0.7;

	 
	retangle(-0.5, 0, 1, 2, color); // pinta metade da tela de cinza

	color[0] = 0.5; // cinza mais escuro
	color[1] = 0.5;
	color[2] = 0.5;

	retangle(-0.5, 0, 0.5, 0.1, color);
	retangle(-0.5, 0.3, 0.5, 0.1, color);
	retangle(-0.5, -0.3, 0.5, 0.1, color);
	
	
}

void moveBixinho(Bixinho *bixinho, float distance){
		

	bixinho->theta+= ((rand()%11)-5)/100.0 ; // atualiza angulo

	// Para mover para onde ele está olhando (na direção theta)
	bixinho->x = bixinho->x + distance*cos(bixinho->theta);
	bixinho->y = bixinho->y + distance*sin(bixinho->theta);

	// Impede que o wilson saia da tela
	bixinho->x = bixinho->x>1 ? 0 : bixinho->x;
	bixinho->y = bixinho->y>1 ? -1 : bixinho->y;
	bixinho->x = bixinho->x<0 ? 1 : bixinho->x;
	bixinho->y = bixinho->y<-1 ? 1 : bixinho->y;

}

void processMenu(){
	if(Bixinhos.empty()) return;	
	// Para mover os bixinhos
	for(int i=0; i<10; i++)
  		moveBixinho(&Bixinhos[i], Bixinhos[i].vel);

}



