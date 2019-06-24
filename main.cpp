#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include "math.h"
#include <iostream>
using namespace std;

bool power = false;
float posX = 0.0f, posY = 0.0f, posZ = -5.0f;


void initGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

float deg2Rad (float sudut) {
	return sudut * (22/7) / 180;
}

void alas(){
    glBegin(GL_QUADS);
      glColor3f(0.0f, 0.4f, 0.0f);
      glVertex3f( 1.0f, 0.2f, -1.0f);
      glVertex3f(-1.0f, 0.2f, -1.0f);
      glVertex3f(-1.0f, 0.2f,  1.0f);
      glVertex3f( 1.0f, 0.2f,  1.0f);

      glVertex3f( 1.0f, -0.2f,  1.0f);
      glVertex3f(-1.0f, -0.2f,  1.0f);
      glVertex3f(-1.0f, -0.2f, -1.0f);
      glVertex3f( 1.0f, -0.2f, -1.0f);

      glVertex3f( 1.0f,  0.2f, 1.0f);
      glVertex3f(-1.0f,  0.2f, 1.0f);
      glVertex3f(-1.0f, -0.2f, 1.0f);
      glVertex3f( 1.0f, -0.2f, 1.0f);

      glVertex3f( 1.0f, -0.2f, -1.0f);
      glVertex3f(-1.0f, -0.2f, -1.0f);
      glVertex3f(-1.0f,  0.2f, -1.0f);
      glVertex3f( 1.0f,  0.2f, -1.0f);

      glVertex3f(-1.0f,  0.2f,  1.0f);
      glVertex3f(-1.0f,  0.2f, -1.0f);
      glVertex3f(-1.0f, -0.2f, -1.0f);
      glVertex3f(-1.0f, -0.2f,  1.0f);

      glVertex3f(1.0f,  0.2f, -1.0f);
      glVertex3f(1.0f,  0.2f,  1.0f);
      glVertex3f(1.0f, -0.2f,  1.0f);
      glVertex3f(1.0f, -0.2f, -1.0f);
   glEnd();
}
void ram(){
    glBegin(GL_QUADS);
      glColor3f(0.0f, 0.0f, 0.0f);
      glVertex3f( 0.05f,  0.0f, -0.7f);
      glVertex3f(-0.05f,  0.0f, -0.7f);
      glVertex3f(-0.05f,  0.0f,  0.7f);
      glVertex3f( 0.05f,  0.0f,  0.7f);

      glVertex3f( 0.05f, -0.0f,  0.7f);
      glVertex3f(-0.05f, -0.0f,  0.7f);
      glVertex3f(-0.05f, -0.0f, -0.7f);
      glVertex3f( 0.05f, -0.0f, -0.7f);

      glVertex3f( 0.05f,  0.0f,  0.7f);
      glVertex3f(-0.05f,  0.0f,  0.7f);
      glVertex3f(-0.05f, -0.0f,  0.7f);
      glVertex3f( 0.05f, -0.0f,  0.7f);

      glVertex3f( 0.05f, -0.0f, -0.7f);
      glVertex3f(-0.05f, -0.0f, -0.7f);
      glVertex3f(-0.05f,  0.0f, -0.7f);
      glVertex3f( 0.05f,  0.0f, -0.7f);

      glVertex3f(-0.05f,  0.0f,  0.7f);
      glVertex3f(-0.05f,  0.0f, -0.7f);
      glVertex3f(-0.05f, -0.0f, -0.7f);
      glVertex3f(-0.05f, -0.0f,  0.7f);

      glVertex3f( 0.05f,  0.0f, -0.7f);
      glVertex3f( 0.05f,  0.0f,  0.7f);
      glVertex3f( 0.05f, -0.0f,  0.7f);
      glVertex3f( 0.05f, -0.0f, -0.7f);
   glEnd();
}
void procie(){
    glBegin(GL_QUADS);
      glColor3f(0.8f, 0.8f, 0.8f);
      glVertex3f( 0.3f,  0.0f, -0.3f);
      glVertex3f(-0.3f,  0.0f, -0.3f);
      glVertex3f(-0.3f,  0.0f,  0.3f);
      glVertex3f( 0.3f,  0.0f,  0.3f);

      glVertex3f( 0.3f, -0.0f,  0.3f);
      glVertex3f(-0.3f, -0.0f,  0.3f);
      glVertex3f(-0.3f, -0.0f, -0.3f);
      glVertex3f( 0.3f, -0.0f, -0.3f);

      glVertex3f( 0.3f,  0.0f,  0.3f);
      glVertex3f(-0.3f,  0.0f,  0.3f);
      glVertex3f(-0.3f, -0.0f,  0.3f);
      glVertex3f( 0.3f, -0.0f,  0.3f);

      glVertex3f( 0.3f, -0.0f, -0.3f);
      glVertex3f(-0.3f, -0.0f, -0.3f);
      glVertex3f(-0.3f,  0.0f, -0.3f);
      glVertex3f( 0.3f,  0.0f, -0.3f);

      glVertex3f(-0.3f,  0.0f,  0.3f);
      glVertex3f(-0.3f,  0.0f, -0.3f);
      glVertex3f(-0.3f, -0.0f, -0.3f);
      glVertex3f(-0.3f, -0.0f,  0.3f);

      glVertex3f( 0.3f,  0.0f, -0.3f);
      glVertex3f( 0.3f,  0.0f,  0.3f);
      glVertex3f( 0.3f, -0.0f,  0.3f);
      glVertex3f( 0.3f, -0.0f, -0.3f);
   glEnd();
}

void kompcu(){
    glBegin(GL_QUADS);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex3f(0.0f,  0.0f, 0.0f);
      glVertex3f(0.0f,  0.0f, 0.5f);
      glVertex3f(0.5f,  0.0f, 0.5f);
      glVertex3f(0.5f,  0.0f, 0.0f);

      glVertex3f(0.0f,  0.1f, 0.0f);
      glVertex3f(0.0f,  0.1f, 0.5f);
      glVertex3f(0.5f,  0.1f, 0.5f);
      glVertex3f(0.5f,  0.1f, 0.0f);

      glColor3f(0.0f, 0.1f, 0.0f);
      glVertex3f(0.0f,  0.0f, 0.0f);
      glVertex3f(0.0f,  0.0f, 0.5f);
      glVertex3f(0.0f,  0.1f, 0.5f);
      glVertex3f(0.0f,  0.1f, 0.0f);

      glVertex3f(0.5f,  0.0f, 0.0f);
      glVertex3f(0.5f,  0.0f, 0.5f);
      glVertex3f(0.5f,  0.1f, 0.5f);
      glVertex3f(0.5f,  0.1f, 0.0f);

    glEnd();
}

void GoldPin(){
    glColor3d(0.7,0.7,0.0);
    glTranslated(0,0,-0.03);
    /*glRotated(90,0,0,1);
    glTranslated(0,0,-0.1);
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj,GLU_FILL);
    gluCylinder(qobj,0.05,0.05,0.05,30,30);*/

    glBegin(GL_QUADS);
        glVertex3f(0.02,0.02,0.0); //A
        glVertex3f(0.02,0.04,0.0); //B
        glVertex3f(0.04,0.04,0.0); //C
        glVertex3f(0.04,0.02,0.0); //D
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(0.02,0.02,0.05); //A+
        glVertex3f(0.02,0.04,0.05); //B+
        glVertex3f(0.04,0.04,0.05); //C+
        glVertex3f(0.04,0.02,0.05); //D+
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(0.02,0.02,0.0); //A
        glVertex3f(0.02,0.04,0.0); //B
        glVertex3f(0.02,0.04,0.05); //B+
        glVertex3f(0.02,0.02,0.05); //A+

        glVertex3f(0.04,0.04,0.0); //C
        glVertex3f(0.04,0.02,0.0); //D
        glVertex3f(0.04,0.02,0.05); //D+
        glVertex3f(0.04,0.04,0.05); //C+

        glVertex3f(0.02,0.04,0.0); //B
        glVertex3f(0.04,0.04,0.0); //C
        glVertex3f(0.04,0.04,0.05); //C+
        glVertex3f(0.02,0.04,0.05); //B+

        glVertex3f(0.02,0.02,0.0); //A
        glVertex3f(0.04,0.02,0.0); //D
        glVertex3f(0.04,0.02,0.05); //D+
        glVertex3f(0.02,0.02,0.05); //A+
    glEnd();
}

void AlasProc(){
    glColor3d(0.0,0.3,0.1);
    glBegin(GL_QUADS);
        glVertex3f(0.0f,0.0f,0.0f); //A
        glVertex3f(0.0f,0.4f,0.0f); //B
        glVertex3f(0.4f,0.4f,0.0f); //C
        glVertex3f(0.4f,0.0f,0.0f); //D

        glVertex3f(0.0f,0.0f,0.05f); //A+
        glVertex3f(0.0f,0.4f,0.05f); //B+
        glVertex3f(0.4f,0.4f,0.05f); //C+
        glVertex3f(0.4f,0.0f,0.05f); //D+

        glVertex3f(0.0f,0.0f,0.0f); //A
        glVertex3f(0.0f,0.4f,0.0f); //B
        glVertex3f(0.0f,0.4f,0.05f); //B+
        glVertex3f(0.0f,0.0f,0.05f); //A+

        glVertex3f(0.4f,0.4f,0.0f); //C
        glVertex3f(0.4f,0.0f,0.0f); //D
        glVertex3f(0.4f,0.0f,0.05f); //D+
        glVertex3f(0.4f,0.4f,0.05f); //C+

        glVertex3f(0.0f,0.4f,0.0f); //B
        glVertex3f(0.4f,0.4f,0.0f); //C
        glVertex3f(0.4f,0.4f,0.05f); //C+
        glVertex3f(0.0f,0.4f,0.05f); //B+

        glVertex3f(0.0f,0.0f,0.0f); //A
        glVertex3f(0.4f,0.0f,0.0f); //D
        glVertex3f(0.4f,0.0f,0.05f); //D+
        glVertex3f(0.0f,0.0f,0.05f); //A+
    glEnd();
}

void KepalaProc(){
    glColor3d(0.3,0.3,0.3);
    glBegin(GL_QUADS);
        glVertex3f(0.05f,0.05f,0.05f); //A
        glVertex3f(0.05f,0.35f,0.05f); //B
        glVertex3f(0.35f,0.35f,0.05f); //C
        glVertex3f(0.35f,0.05f,0.05f); //D

        glVertex3f(0.05f,0.05f,0.1f); //A+
        glVertex3f(0.05f,0.35f,0.1f); //B+
        glVertex3f(0.35f,0.35f,0.1f); //C+
        glVertex3f(0.35f,0.05f,0.1f); //D+

        glVertex3f(0.05f,0.05f,0.05f); //A
        glVertex3f(0.05f,0.35f,0.05f); //B
        glVertex3f(0.05f,0.35f,0.1f); //B+
        glVertex3f(0.05f,0.05f,0.1f); //A+

        glVertex3f(0.35f,0.35f,0.05f); //C
        glVertex3f(0.35f,0.05f,0.05f); //D
        glVertex3f(0.35f,0.05f,0.1f); //D+
        glVertex3f(0.35f,0.35f,0.1f); //C+

        glVertex3f(0.05f,0.35f,0.05f); //B
        glVertex3f(0.35f,0.35f,0.05f); //C
        glVertex3f(0.35f,0.35f,0.1f); //C+
        glVertex3f(0.05f,0.35f,0.1f); //B+

        glVertex3f(0.05f,0.05f,0.05f); //A
        glVertex3f(0.35f,0.05f,0.05f); //D
        glVertex3f(0.35f,0.05f,0.1f); //D+
        glVertex3f(0.05f,0.05f,0.1f); //A+
    glEnd();
}

float procY=0.0f;
bool status = false;
void CopotProc(){
    int panjang;

    if(!status){
        status = true;
        for(panjang=0; panjang<=5; panjang++){
            procY+=0.1;
        }
    }
    else{
        status = false;
        for(panjang=0; panjang<=5; panjang++){
            procY-=0.1;
        }
    }
}
void Proc(){
 glTranslatef(0.0f,procY,0.0f);
 AlasProc();
 KepalaProc();

 float tx=0.0f,ty=0.0f;
 for(int y=0;y<=11;y++){
    for(int x=0;x<=11;x++){
        glPushMatrix();
        glTranslatef(tx,ty,0);
        GoldPin();
        glPopMatrix();
        tx+=0.03;
    }
    tx=0.0f;
    ty+=0.03;
 }
}

void Mobo(){

    glPushMatrix();
        glRotated(60,1,0,0);
        alas();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.6f, 0.0f, 0.0f);
        glRotated(60,1,0,0);
        ram();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.8f, 0.0f, 0.0f);
        glRotated(60,1,0,0);
        ram();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-0.1f, 0.4f, 0.0f);
        glRotated(60,1,0,0);
        procie();
    glPopMatrix();
    }

void keyFunction(unsigned char key, int x, int y){
    switch(key){
        case 73: // I
            power = true;
        break;
        case 79: // O
            while (posY > 0) {
                keyFunction('L', 0, 0);
            }

            power = false;
        break;
        case 75: // K
            if (power == true)
                posY += 0.2f;
        break;
        case 76: // L
            if (power == true)
                posY -= 0.2f;
        break;
        case 87: // W
            if (power == true)
                posZ -= 0.2f;
        break;
        case 83: // S
            if (power == true)
                posZ += 0.2f;
        break;
        case 65: // A
            if (power == true)
                posX -= 0.2f;
        break;
        case 68: // D
            if (power == true)
                posX += 0.2f;
        break;
        case 67: //c
            CopotProc();
        break;
    }
}


GLfloat angle = 0.0f;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(posX,posY,posZ);

    Mobo();
    //kompcu();
    glPushMatrix();
    glRotated(-30,1,0,0);
    glTranslatef(-0.3f,-0.4f,1.0f);
    Proc();
    glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(15, timer, 0);
}

void reshape(GLsizei width, GLsizei height)
{
	if (height == 0)
		height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("3d-animation");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	initGL();
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(keyFunction);
	glutMainLoop();
	return 0;
}
