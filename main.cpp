/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f, z=5.0f;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
void processNormalKeys(unsigned char key, int xx, int yy) {

        if (key == 27)
              exit(0);
}
void pressKey(int key, int xx, int yy) {

       switch (key) {
             case GLUT_KEY_UP : deltaMove = 0.5f; break;
             case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
       }
}

void releaseKey(int key, int x, int y) {

        switch (key) {
             case GLUT_KEY_UP :
             case GLUT_KEY_DOWN : deltaMove = 0;break;
        }
}
void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}
void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}
void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
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
static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    if (deltaMove)
		computePos(deltaMove);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, 1.0f, z,
			x+lx, 1.0f,  z+lz,
			0.0f, 1.0f,  0.0f);
    glColor3d(1,0,0);

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
    glutSwapBuffers();

}



static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
    glutMainLoop();

    return EXIT_SUCCESS;
}
