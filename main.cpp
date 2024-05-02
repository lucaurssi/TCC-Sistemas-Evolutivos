#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "libs/interface.h"

using namespace std;

#define windowWidth 900
#define windowHeight 900



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



