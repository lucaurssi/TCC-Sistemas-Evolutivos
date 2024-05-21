#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <math.h>
#include <string>
#include <iostream>

#define FONT GLUT_BITMAP_TIMES_ROMAN_24

using namespace std;


void setColor(float* color, float R, float G, float B){
	color[0] = R;
	color[1] = G;
	color[2] = B;
	return; 
}

void retangle(float x, float y, float w, float h, float*color){
  // Vai desenhar um polígono de 4 vértices

  glColor3f(color[0], color[1], color[2]);// Define que será desenhar um objeto azul
  glBegin(GL_POLYGON);// Fala para o OpenGL que os próximos pontos serão para desenhar um polígono

  // Adicionada cada vértice do retângulo
  glVertex2d( x-w/2, y-h/2);
  glVertex2d( x-w/2, y+h/2);
  glVertex2d( x+w/2, y+h/2);
  glVertex2d( x+w/2, y-h/2);

  glEnd();// Fala para o OpenGL que terminou de enviar os vértices do polígono
}


void triangle(float x, float y, float h, float b, float*color){
  // O mais polígono mais trivial: 3 vertíces

  glColor3f(color[0], color[1], color[2]);// Define que será desenhar um objeto roxo
  glBegin(GL_POLYGON);

  // Adicionada cada vértice do triângulo
  glVertex2d( x-b/2, y-h/2);
  glVertex2d( x+b/2, y-h/2);
  glVertex2d( x, y+h/2);

  glEnd();// Fala para o OpenGL que terminou de enviar os vértices do polígono
}


void circle(float x, float y, float radius, float*color){
  // Um circulo é desenhado como um polígono de muitos pontos

  glColor3f(color[0], color[1], color[2]);// Define que será desenhar um objeto verde
  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i+=5) {
    // Adicionada cada vértice 2D do circulo
    glVertex2d( radius*cos(i/180.0*M_PI) + x, radius*sin(i/180.0*M_PI) + y);
  }
  glEnd();
}


void strangePolygon(float x, float y, float*color){

  glColor3f(color[0], color[1], color[2]);// Define que será desenhar um objeto preto

  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i+=10) {
    glVertex2d( 0.2*cos(i/180.0*M_PI) + x + cos(i)*0.15,  0.2*sin(i/180.0*M_PI) + y + sin(i)*0.15);
  }
  glEnd();

}

void anotherStrangePolygon(float x, float y, float*color){
  glColor3f(color[0], color[1], color[2]);// Define que será desenhar um objeto amarelo

  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i+=10) {
    glVertex2d( 0.3*cos(i/180.0*M_PI) + x,  0.3*sin(i/180.0*M_PI) + y);
    i+=10;
    glVertex2d( 0.1*cos(i/180.0*M_PI) + x,  0.1*sin(i/180.0*M_PI) + y);
  }
  glEnd();
}


void RenderString(float x, float y, string string){  
	
	glColor3f(0, 0, 0); // black
	glRasterPos2f(x, y); 
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[0]); // write one character
	
	for(int i=1; i<(int)string.length(); i++){
		x = (x*900)+ 2*glutBitmapWidth(FONT, string[i-1]); // move x by the width of the character
		x = x/900;
		glRasterPos2f(x, y);
		glutBitmapCharacter(FONT, string[i]);
	}
}

void draw_basic_menu(string title, int Nro_ind, int tipoGene, bool geneMenu, int Nro_selecao, int Nro_selecao_2){
	float color[3];
	
	
	setColor(color, 0.7, 0.7, 0.7);
	retangle(-0.5, 0, 1, 2, color); // pinta metade da tela de cinza	
	
	setColor(color, 0.5, 0.5, 0.5); // cinza escuro
	retangle(-0.8, 0.9, 0.25, 0.075, color); 
	RenderString(-0.91, 0.88, "<-- Back");

	RenderString(-0.6, 0.88, title);
	

	// ------------------------------------------
	// Numero de individuos a serem criados
	RenderString(-0.95, 0.7, "Nro. Individuos:");

	setColor(color, 0.5, 0.5, 0.5);

	// 10 
	RenderString(-0.51, 0.64, "10"); 
	circle( -0.48, 0.72, 0.03, color);

	// 25
	RenderString(-0.41, 0.64, "25");
	circle( -0.38, 0.72, 0.03, color);
	
	// 50
	RenderString(-0.31, 0.64, "50");
	circle( -0.28, 0.72, 0.03, color);
	
	// 100
	RenderString(-0.22, 0.64, "100");
	circle( -0.18, 0.72, 0.03, color);
	
	
	// circulo azul na posicao selecionada
	setColor(color, 0.1, 0.1, 1); // azul
	
	switch (Nro_ind){
		case 10:
			circle( -0.48, 0.72, 0.02, color);
			break;
		case 25:
			circle( -0.38, 0.72, 0.02, color);
			break;
		case 50:
			circle( -0.28, 0.72, 0.02, color);
			break;
		case 100:
			circle( -0.18, 0.72, 0.02, color);
			break;
		default:
			;
	}
	// ------------------------------------------

	RenderString(-0.95, 0.5, "Tipo de genes:");

	setColor(color, 0.2, 0.2, 0.2);
	retangle(-0.4, 0.515, 0.36, 0.085, color); 
	setColor(color, 0.5, 0.5, 0.5); // cinza escuro
	retangle(-0.4, 0.515, 0.35, 0.075, color); 

	switch (tipoGene){
		case 0:
			RenderString(-0.55, 0.5, "Cor e Forma");	
			break;
		case 1:
			RenderString(-0.55, 0.5, "Cor");	
			break;
		case 2:
			RenderString(-0.55, 0.5, "Forma");	
			break;
		default: 
			cout << "unkown tipoGene" << tipoGene << "\n";				
	}

	if (geneMenu){
		
		setColor(color, 0.5, 0.5, 0.5); // cinza escuro
		retangle(-0.12, 0.435, 0.15, 0.075, color);
		setColor(color, 0.5, 0.5, 0.5); // cinza escuro
		retangle(-0.12, 0.515, 0.15, 0.075, color);
		setColor(color, 0.5, 0.5, 0.5); // cinza escuro
		retangle(-0.12, 0.595, 0.15, 0.075, color);

		RenderString(-0.19, 0.575, "Cor");
		RenderString(-0.19, 0.5, "Forma");
		RenderString(-0.19, 0.42, "C e F");

	}

	// --------- Run Button -----------------
	setColor(color, 0.2, 0.2, 0.2);
	retangle(-0.25, -0.9, 0.2, 0.09, color); 
	setColor(color, 0.5, 0.5, 0.5); // cinza escuro
	retangle(-0.25, -0.9, 0.19, 0.08, color); 
	
	RenderString(-0.3, -0.92, "Run");
	// --------------------------------------
	
	

	// --------------------------------------

	RenderString(-0.95, 0.4, "Selecao:");

	if (tipoGene == 0 || tipoGene == 2){ // cor&for  && forma
		setColor(color, 0.5, 0.5, 0.5);

		circle( -0.4, 0.42, 0.03, color);	// circulo		
		circle( -0.33, 0.42, 0.03, color);	// quadrado
		circle( -0.26, 0.42, 0.03, color);	// triangulo

		setColor(color, 0,0,0);
		circle( -0.4, 0.36, 0.025, color);
		retangle(-0.33, 0.36, 0.04, 0.04, color); 
		triangle(-0.26, 0.36, 0.05, 0.05, color);
		
		setColor(color, 0.7,0.7,0.7);
		circle( -0.4, 0.36, 0.02, color);
		retangle(-0.331, 0.36, 0.03, 0.03, color); 
		triangle(-0.26, 0.357, 0.0353, 0.0375, color);
		
		// circulo azul na posicao selecionada
		setColor(color, 0.1, 0.1, 1); // azul
		
		switch (Nro_selecao){
			case 0:
				circle( -0.4, 0.42, 0.02, color);
				break;
			case 1:
				circle( -0.33, 0.42, 0.02, color);
				break;
			case 2:
				circle( -0.26, 0.42, 0.02, color);
		}
	}

	if (tipoGene == 0 || tipoGene == 1){ // cor c&f

		setColor(color, 0.5, 0.5, 0.5);

		circle( -0.6, 0.42, 0.03, color);	// preto	
		circle( -0.52, 0.42, 0.03, color);	// branco

		setColor(color, 0,0,0);
		circle( -0.6, 0.36, 0.02, color);
		setColor(color, 1,1,1);
		circle( -0.52, 0.36, 0.02, color);
		
		// circulo azul na posicao selecionada
		setColor(color, 0.1, 0.1, 1); // azul
		
		switch (Nro_selecao_2){
			case 0:
				circle( -0.6, 0.42, 0.02, color);
				break;
			case 1:
				circle( -0.52, 0.42, 0.02, color);
		}
	}

	// -------------------------------------
	
	RenderString(-0.95, 0.3, "Fitness:");


}





