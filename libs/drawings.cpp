#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <math.h>
#include <string>
#include <iostream>
#include "drawings.h"

#define FONT GLUT_BITMAP_TIMES_ROMAN_24

using namespace std;



void setColor(unsigned char* color, unsigned char R, unsigned char G, unsigned char B){
	color[0] = R;
	color[1] = G;
	color[2] = B;
	return; 
}

void retangle(float x, float y, float w, float h, unsigned char*color){
  // Vai desenhar um polígono de 4 vértices

  glColor3ub(color[0], color[1], color[2]);// Define que será desenhar um objeto azul
  glBegin(GL_POLYGON);// Fala para o OpenGL que os próximos pontos serão para desenhar um polígono

  // Adicionada cada vértice do retângulo
  glVertex2d( x-w/2, y-h/2);
  glVertex2d( x-w/2, y+h/2);
  glVertex2d( x+w/2, y+h/2);
  glVertex2d( x+w/2, y-h/2);

  glEnd();// Fala para o OpenGL que terminou de enviar os vértices do polígono
}


void triangle(float x, float y, float h, float b, unsigned char*color){
  // O mais polígono mais trivial: 3 vertíces

  glColor3ub(color[0], color[1], color[2]);// Define que será desenhar um objeto roxo
  glBegin(GL_POLYGON);

  // Adicionada cada vértice do triângulo
  glVertex2d( x-b/2, y-h/2);
  glVertex2d( x+b/2, y-h/2);
  glVertex2d( x, y+h/2);

  glEnd();// Fala para o OpenGL que terminou de enviar os vértices do polígono
}


void circle(float x, float y, float radius, unsigned char*color){
  // Um circulo é desenhado como um polígono de muitos pontos

  glColor3ub(color[0], color[1], color[2]);// Define que será desenhar um objeto verde
  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i+=5) {
    // Adicionada cada vértice 2D do circulo
    glVertex2d( radius*cos(i/180.0*M_PI) + x, radius*sin(i/180.0*M_PI) + y);
  }
  glEnd();
}


void strangePolygon(float x, float y, unsigned char*color){

  glColor3ub(color[0], color[1], color[2]);// Define que será desenhar um objeto preto

  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i+=10) {
    glVertex2d( 0.2*cos(i/180.0*M_PI) + x + cos(i)*0.15,  0.2*sin(i/180.0*M_PI) + y + sin(i)*0.15);
  }
  glEnd();

}

void anotherStrangePolygon(float x, float y, unsigned char*color){
  glColor3ub(color[0], color[1], color[2]);// Define que será desenhar um objeto amarelo

  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i+=10) {
    glVertex2d( 0.3*cos(i/180.0*M_PI) + x,  0.3*sin(i/180.0*M_PI) + y);
    i+=10;
    glVertex2d( 0.1*cos(i/180.0*M_PI) + x,  0.1*sin(i/180.0*M_PI) + y);
  }
  glEnd();
}


void RenderString(float x, float y, string string){  
	
	glColor3ub(0, 0, 0); // black
	glRasterPos2f(x, y); 
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[0]); // write one character
	
	for(int i=1; i<(int)string.length(); i++){
		x = (x*900)+ 2*glutBitmapWidth(FONT, string[i-1]); // move x by the width of the character
		x = x/900;
		glRasterPos2f(x, y);
		glutBitmapCharacter(FONT, string[i]);
	}
}


void draw_basic_menu(string title){
	unsigned char color[3];
	
	
	
	setColor(color, LIGHT_GREY);
	retangle(-0.5, 0, 1, 2, color); // pinta metade da tela de cinza

	RenderString(-0.6, 0.88, title);	
	
	// -------- Back button ----------------

	setColor(color, GREY);
	retangle(-0.8, 0.9, 0.25, 0.075, color); 
	RenderString(-0.91, 0.88, "<-- Back");

	// --------- Run Button -----------------

	setColor(color, GREY);
	retangle(-0.25, -0.9, 0.2, 0.09, color); 

	RenderString(-0.3, -0.92, "Run");
}



void nro_individuos(float x, float y, int Nro_ind){
	unsigned char color[3];

	// Numero de individuos a serem criados
	RenderString(x, y, "Nro. Individuos:");

	setColor(color, GREY);

	RenderString(x+0.44, y-0.06, "10"); 
	circle( x+0.47, y+0.02, 0.03, color);

	RenderString(x+0.54, y-0.06, "25");
	circle( x+0.57, y+0.02, 0.03, color);
	
	RenderString(x+0.64, y-0.06, "50");
	circle( x+0.67, y+0.02, 0.03, color);
	
	RenderString(x+0.73, y-0.06, "100");
	circle( x+0.77, y+0.02, 0.03, color);
	
	// circulo azul na posicao selecionada
	setColor(color, BLUE); // azul
	
	switch (Nro_ind){
		case 10:
			circle( x+0.47, y+0.02, 0.02, color);
			break;
		case 25:
			circle( x+0.57, y+0.02, 0.02, color);
			break;
		case 50:
			circle( x+0.67, y+0.02, 0.02, color);
			break;
		case 100:
			circle( x+0.77, y+0.02, 0.02, color);
	}
}
	
void tipo_de_gene(float x, float y, int tipoGene, bool geneMenu){
	unsigned char color[3];

	RenderString(x, y, "Tipo de genes:");

	setColor(color, GREY); // cinza escuro
	retangle(x+0.55, y+0.015, 0.35, 0.075, color); 

	switch (tipoGene){
		case 0:
			RenderString(x+0.4, y, "Cor e Forma");	
			break;
		case 1:
			RenderString(x+0.4, y, "Cor");	
			break;
		case 2:
			RenderString(x+0.4, y, "Forma");				
	}

	if (geneMenu){
		
		setColor(color, GREY); // cinza escuro
		retangle(x+0.83, y-0.065, 0.15, 0.075, color);
		retangle(x+0.83, y+0.005, 0.15, 0.075, color);
		retangle(x+0.83, y+0.075, 0.15, 0.075, color);

		RenderString(x+0.76, y+0.075, "Cor");
		RenderString(x+0.76, y, "Forma");
		RenderString(x+0.76, y-0.08, "C e F");
	}
}
						// -0.95, 0.4
void draw_Selecao(float x, float y, int tipoGene, int Nro_selecao, bool Nro_selecao_2){
	unsigned char color[3];
	
	RenderString(x, y, "Selecao:");

	if (tipoGene == 0 || tipoGene == 2){ // cor&for  && forma
		setColor(color, GREY);

		circle( x+0.55, y+0.02, 0.03, color);	// circulo		
		circle( x+0.62, y+0.02, 0.03, color);	// quadrado
		circle( x+0.69, y+0.02, 0.03, color);	// triangulo

		setColor(color, BLACK);
		circle(  x+0.55, y-0.04, 0.025, color);
		retangle(x+0.62, y-0.04, 0.04, 0.04, color); 
		triangle(x+0.69, y-0.04, 0.05, 0.05, color);
		
		setColor(color, LIGHT_GREY);
		circle(  x+0.55, y-0.04, 0.02, color);
		retangle(x+0.619, y-0.04, 0.03, 0.03, color); 
		triangle(x+0.69, y-0.043, 0.0353, 0.0375, color);
		
		// circulo azul na posicao selecionada
		setColor(color, BLUE); // azul
		
		switch (Nro_selecao){
			case 0:
				circle( x+0.55, y+0.02, 0.02, color);
				break;
			case 1:
				circle( x+0.62, y+0.02, 0.02, color);
				break;
			case 2:
				circle( x+0.69, y+0.02, 0.02, color);
		}
	}

	if (tipoGene == 0 || tipoGene == 1){ // cor c&f

		setColor(color, GREY);

		circle( x+0.35, y+0.02, 0.03, color);	// circulos cinza	
		circle( x+0.43, y+0.02, 0.03, color);	

		setColor(color, BLACK);
		circle( x+0.35, y-0.04, 0.02, color);
		setColor(color, WHITE);
		circle( x+0.43, y-0.04, 0.02, color);
		
		setColor(color, BLUE); // circulo azul
		
		if (Nro_selecao_2)
			circle( x+0.43, y+0.02, 0.02, color);
		else
			circle( x+0.35, y+0.02, 0.02, color);
		
	}
}

void draw_Reproducao(float x, float y, bool blue_reproducao){
	unsigned char color[3];
	
	RenderString(-0.95, 0.28, "Avaliacao:");
	
	RenderString(x, y, "Reproducao:");
	
	setColor(color, GREY); // circulos cinza

	circle( x+0.33, y+0.02, 0.03, color); 	
	RenderString(x+0.4, y, "Asexuada");

	circle( x+0.33, y-0.05, 0.03, color);
	RenderString(x+0.4, y-0.07, "Sexuada");


	setColor(color, BLUE); // circulos azul
	if (blue_reproducao)
		circle( x+0.33, y+0.02, 0.02, color);
	else	
		circle( x+0.33, y-0.05, 0.02, color);
}	

void draw_Mutacao(float x, float y, bool blue_mutacao){
	unsigned char color[3];
	
	RenderString(x, y, "Mutacao:");
	
	setColor(color, GREY); // circulos cinza

	circle( x+0.3, y+0.02, 0.03, color); 	
	RenderString(x+0.34, y, "Fixa");

	circle( x+0.55, y+0.02, 0.03, color);
	RenderString(x+0.59, y, "Variavel");


	setColor(color, BLUE); // circulos azul
	if (blue_mutacao)
		circle( x+0.3, y+0.02, 0.02, color);
	else	
		circle( x+0.55, y+0.02, 0.02, color);
}	
























