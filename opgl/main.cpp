#include <chrono>
#include <cstdlib>
#include <iostream>
#include "glut.h"
#include "GLU.h"
#include "GL.h"


GLfloat Piramidrotat = 0.0f;
float position_x = 0.0f;
float position_y = 0.0f;
float position_z = -10.0f;
int chngtm = 17;


void display() {

  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(position_x, position_y, position_z);
    glRotatef(Piramidrotat, 1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    glVertex3f(0.0f, 1.f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); 
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

   
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex3f(0.0f, -1.0f, -1.0f);


    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex3f(1.0f, -1.0f, 1.0f);


    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(0.0f, -1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex3f(1.0f, -1.0f, 1.0f);

    glEnd();

    glutSwapBuffers();
    Piramidrotat += 3.0f;
}

void clock(int value) {
    glutPostRedisplay();
    glutTimerFunc(chngtm, clock, 0);
}

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //zeby nie przechodzilo
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}


void adjust(GLsizei width, GLsizei height) {
    if (height == 0) {
        height = 1;
    }
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void MOVE_BUTTONS(unsigned char key, int x, int y)
{


    switch (key) {
    case 'w':
        position_y -= +0.1f;
        break;
    case 'a':
        position_x += +0.1f;
        break;
    case 's':
        position_y += +0.1f;
        break;
    case 'd':
        position_x -= +0.1f;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInitWindowSize(450, 450);
    glutInitWindowPosition(100, 100);
    glutInit(&argc, argv);
    glutTimerFunc(0, clock, 0);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutCreateWindow("Piramida lb6");
    glutDisplayFunc(display);
    glutReshapeFunc(adjust);
    glutKeyboardFunc(MOVE_BUTTONS);
    initGL();
    glutMainLoop();
    return 0;
    //Klawiszologia:
 //w - gora
 //s - dol
 //a - lewo
 //d - prawo


}