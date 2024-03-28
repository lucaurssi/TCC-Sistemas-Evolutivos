#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "libs/menu.h"

using namespace std;

#define windowWidth 900
#define windowHeight 900



void draw(){
    // Importante: Somente será desenhado o que estiver entre glClear e glEnd
    glClear(GL_COLOR_BUFFER_BIT);

    // A tela padrão do OpenGL tem suas coordenadas X e Y de -1 até 1
    // Coordenada (-1 -1) é o canto inferior esquerdo
    // Coordenada (-1 1) é o canto superior esquerdo
    // Coordenada (0 0) é o centro da tela

    bool MENU = true;
    if(MENU) menu();
    

    glutSwapBuffers();
}

void timer(int){

	processMenu();

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

    glutDisplayFunc(draw);// Define qual função irá desenhar
    glutTimerFunc(0, timer, 0); // clock
    glutMainLoop();

    return 0;
}



