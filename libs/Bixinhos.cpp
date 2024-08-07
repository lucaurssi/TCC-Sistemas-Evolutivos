#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include "drawings.h"
#include "Bixinhos.h"

#include <math.h>

Bixinho CreateBixinho(float x, float y, unsigned char *color){
    Bixinho A;  

    A.radius = 0.05;
    A.x = x;
    A.y = y;
    A.theta = ((rand()%20)-10)/10.0;
    A.r = color[0];
    A.g = color[1];
    A.b = color[2];
    A.vel = 0.010;
	A.shape = rand()%3;

    return A; 
}

void drawBixinho(Bixinho bixinho, int gene){
	// Função para desenhar o bixinho	
	unsigned char color[3]; 
	setColor(color, bixinho.r, bixinho.g, bixinho.b);
	
	if (gene == 2) // forma apenas
		setColor(color, GREY); // cinza claro
	

	float radius = bixinho.radius;
	float x = bixinho.x;
	float y = bixinho.y;
	float theta = bixinho.theta;
	int shape = bixinho.shape;

	//----- Desenha corpo do bixinho -----//

	if (gene == 1) // apenas cor
		triangle(x, y, radius*2, radius*2, color);
	else {
		switch (shape){
			case 0:		
				circle(x, y, radius, color);
				break;
			case 1:			
				retangle(x, y, radius*2, radius*2, color);
				break;
			case 2: 
				triangle(x, y, radius*2, radius*2, color);	
				break;
		
		}
	}

	//----- Desenha olho direito do bixinho -----//
	float eyeRadius = radius/8;
	float eyeDist = M_PI/6;

	glColor3ub(0, 0, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i+=5) {
		float shiftX = radius/2*cos(theta-eyeDist);
		float shiftY = radius/2*sin(theta-eyeDist);
		glVertex2d( eyeRadius*cos(i/180.0*M_PI) + x + shiftX, eyeRadius*sin(i/180.0*M_PI) + y + shiftY);
	}
	glEnd();

	//----- Desenha olho esquerdo do bixinho -----//
	glColor3ub(0, 0, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i+=5) {
		float shiftX = radius/2*cos(theta+eyeDist);
		float shiftY = radius/2*sin(theta+eyeDist);

		glVertex2d( eyeRadius*cos(i/180.0*M_PI) + x + shiftX, eyeRadius*sin(i/180.0*M_PI) + y + shiftY);
	}
  	glEnd();
}

void moveBixinho(Bixinho *bixinho, float distance){
		

	bixinho->theta+= ((rand()%11)-5)/100.0 ; // atualiza angulo

	// Para mover para onde ele está olhando (na direção theta)
	bixinho->x = bixinho->x + distance*cos(bixinho->theta);
	bixinho->y = bixinho->y + distance*sin(bixinho->theta);

	// Impede que o wilson saia da tela
	bixinho->x = bixinho->x>1 ? 0.04 : bixinho->x;
	bixinho->y = bixinho->y>1 ? -1 : bixinho->y;
	bixinho->x = bixinho->x<0.03 ? 1 : bixinho->x;
	bixinho->y = bixinho->y<-1 ? 1 : bixinho->y;

}


void Repopulate(Sim_Var *SV, bool mutation){
	char random_indv = rand()%SV->N;
	Bixinho A;

	if (SV->Breed) // if asexual, just copy another bixinho
		A = SV->Bixinhos[random_indv];
	
	else{	// crossover
		char random_indv2 = rand()%SV->N;

		A.radius = 0.05;
		A.x = SV->Bixinhos[random_indv].x;
		A.y = SV->Bixinhos[random_indv2].y;
		A.theta = ((rand()%20)-10)/10.0;
		A.r = (SV->Bixinhos[random_indv].r + SV->Bixinhos[random_indv2].r)/2;
		A.g = (SV->Bixinhos[random_indv].g + SV->Bixinhos[random_indv2].g)/2;
		A.b = (SV->Bixinhos[random_indv].b + SV->Bixinhos[random_indv2].b)/2;
		A.vel = 0.010;

		if(rand()%2) A.shape = SV->Bixinhos[random_indv].shape;
		else A.shape = SV->Bixinhos[random_indv2].shape;		
	}

    if(mutation){
        if(SV->Mutation){ // fixed mutation value 
            if(rand()%100 == 0) // 1% chance of changing shape
                A.shape = (A.shape+1)%3; 

            // +1/-1 in every primary color, unless it's the cap, 0 or 255
            if(rand()%2) A.r = (A.r == 0) ? A.r : A.r-1;
            else A.r = (A.r == 255) ? A.r : A.r+1;

            if(rand()%2) A.g = (A.g == 0) ? A.g : A.g-1;
            else A.g = (A.g == 255) ? A.g : A.g+1;

            if(rand()%2) A.b = (A.b == 0) ? A.b : A.b-1;
            else A.b = (A.b == 255) ? A.b : A.b+1;

        }else{ // chaging mutation value
            if(rand()%100 == 0) 
                A.shape = (A.shape+1)%3; 

            if(rand()%2) A.r = (A.r == 0) ? A.r : A.r-1;
            else A.r = (A.r == 255) ? A.r : A.r+1;

            if(rand()%2) A.g = (A.g == 0) ? A.g : A.g-1;
            else A.g = (A.g == 255) ? A.g : A.g+1;

            if(rand()%2) A.b = (A.b == 0) ? A.b : A.b-1;
            else A.b = (A.b == 255) ? A.b : A.b+1;
        }
    }
    

	SV->Bixinhos.push_back(A);
	SV->N++; 
}









