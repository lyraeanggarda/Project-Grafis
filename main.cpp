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

static int slices = 16;
static int stacks = 16;

/* GLUT callback Handlers */

void initGL()
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glShadeModel(GL_SMOOTH);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat high_shininess[] = { 100.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
}

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

void mobo(){
    glBegin(GL_QUADS);
        //Depan
        glColor3f(0.0f, 0.3f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 0.5f, 0.0f);
        glVertex3f(1.5f, 0.0f, 0.0f);
        glVertex3f(1.5f, 1.5f, 0.0f);
        glColor3f(0.0f, 0.3f, 0.0f);
        glVertex3f(0.0f, 1.5f, 0.0f);

        //bawah
        glColor3f(0.0f, 0.3f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, -0.2f);
        glColor3f(0.0f, 0.3f, 0.0f);
        glVertex3f(1.5f, 0.0f, -0.2f);
        glColor3f(0.0f, 0.3f, 0.0f);
        glVertex3f(1.5f, 0.0f, 0.0f);

        //kiri
        glColor3f(0.0f, 0.3f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, -0.2f);
        glVertex3f(0.0f, 1.5f, -0.2f);
        glVertex3f(0.0f, 1.5f, 0.0f);

        //kanan
        glColor3f(0.0f, 0.3f, 0.0f);
        glVertex3f(1.5f, 0.0f, 0.0f);
        glVertex3f(1.5f, 0.0f, -0.2f);
        glVertex3f(1.5f, 1.5f, -0.2f);
        glVertex3f(1.5f, 1.5f, 0.0f);

        //atas
        glColor3f(0.0f, 0.3f, 0.0f);
        glVertex3f(0.0f, 1.5f, 0.0f);
        glVertex3f(0.0f, 1.5f, -0.2f);
        glVertex3f(1.5f, 1.5f, -0.2f);
        glVertex3f(1.5f, 1.5f, 0.0f);

        //belakang
        glColor3f(0.0f, 0.3f, 0.0f);
        glVertex3f(0.0f, 0.0f, -0.2f);
        glVertex3f(1.5f, 0.0f, -0.2f);
        glVertex3f(1.5f, 1.5f, -0.2f);
        glVertex3f(0.0f, 1.5f, -0.2f);
    glEnd();
}

void cpu(){
    glBegin(GL_QUADS);
//        glVertex3f(0.0f, 0.0f, 0.0f);
//        glVertex3f(0.4f, 0.0f, 0.0f);
//        glVertex3f(0.4f, 0.4f, 0.0f);
//        glVertex3f(0.0f, 0.4f, 0.0f);

        glVertex3f( 0.4f,  0.4f,  0.0f);
        glVertex3f( 0.0f,  0.4f,  0.0f);
        glVertex3f( 0.0f,  0.4f,  0.1f);
        glVertex3f( 0.4f,  0.4f,  0.1f);

        glVertex3f( 0.4f,  0.0f,  0.1f);
        glVertex3f( 0.0f,  0.0f,  0.1f);
        glVertex3f( 0.0f,  0.0f,  0.0f);
        glVertex3f( 0.4f,  0.0f,  0.0f);

        glVertex3f( 0.0f,  0.4f,  0.1f);
        glVertex3f( 0.0f,  0.0f,  0.1f);
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex3f( 0.4f,  0.0f,  0.1f);
        glVertex3f( 0.4f,  0.4f,  0.1f);

        glVertex3f( 0.4f,  0.0f,  0.0f);
        glVertex3f( 0.0f,  0.0f,  0.0f);
        glVertex3f( 0.0f,  0.4f,  0.0f);
        glVertex3f( 0.4f,  0.4f,  0.0f);

        glVertex3f( 0.0f,  0.4f,  0.1f);
        glVertex3f( 0.0f,  0.4f,  0.0f);
        glVertex3f( 0.0f,  0.0f,  0.0f);
        glVertex3f( 0.0f,  0.0f,  0.1f);

        glVertex3f( 0.4f,  0.4f,  0.0f);
        glVertex3f( 0.4f,  0.4f,  0.1f);
        glVertex3f( 0.4f,  0.0f,  0.1f);
        glVertex3f( 0.4f,  0.0f,  0.0f);
    glEnd();
}

void ram(){
    glBegin(GL_QUADS);
        glVertex3f( 0.07f,  0.7f,  0.0f);
        glVertex3f( 0.00f,  0.7f,  0.0f);
        glVertex3f( 0.00f,  0.7f,  0.1f);
        glVertex3f( 0.07f,  0.7f,  0.1f);

        glVertex3f( 0.07f,  0.0f,  0.1f);
        glVertex3f( 0.00f,  0.0f,  0.1f);
        glVertex3f( 0.00f,  0.0f,  0.0f);
        glVertex3f( 0.07f,  0.0f,  0.0f);

        glVertex3f( 0.00f,  0.7f,  0.1f);
        glVertex3f( 0.00f,  0.0f,  0.1f);
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex3f( 0.07f,  0.0f,  0.1f);
        glVertex3f( 0.07f,  0.7f,  0.1f);

        glVertex3f( 0.07f,  0.0f,  0.0f);
        glVertex3f( 0.00f,  0.0f,  0.0f);
        glVertex3f( 0.00f,  0.7f,  0.0f);
        glVertex3f( 0.07f,  0.7f,  0.0f);

        glVertex3f( 0.00f,  0.7f,  0.1f);
        glVertex3f( 0.00f,  0.7f,  0.0f);
        glVertex3f( 0.00f,  0.0f,  0.0f);
        glVertex3f( 0.00f,  0.0f,  0.1f);

        glVertex3f( 0.07f,  0.7f,  0.0f);
        glVertex3f( 0.07f,  0.7f,  0.1f);
        glVertex3f( 0.07f,  0.0f,  0.1f);
        glVertex3f( 0.07f,  0.0f,  0.0f);
    glEnd();
}

void vga(){
    glBegin(GL_QUADS);
        glVertex3f( 0.9f,  0.07f,  0.0f);
        glVertex3f( 0.0f,  0.07f,  0.0f);
        glVertex3f( 0.0f,  0.07f,  0.1f);
        glVertex3f( 0.9f,  0.07f,  0.1f);

        glVertex3f( 0.9f,  0.00f,  0.1f);
        glVertex3f( 0.0f,  0.00f,  0.1f);
        glVertex3f( 0.0f,  0.00f,  0.0f);
        glVertex3f( 0.9f,  0.00f,  0.0f);

        glVertex3f( 0.0f,  0.07f,  0.1f);
        glVertex3f( 0.0f,  0.00f,  0.1f);
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex3f( 0.9f,  0.00f,  0.1f);
        glVertex3f( 0.9f,  0.07f,  0.1f);

        glVertex3f( 0.9f,  0.00f,  0.0f);
        glVertex3f( 0.0f,  0.00f,  0.0f);
        glVertex3f( 0.0f,  0.07f,  0.0f);
        glVertex3f( 0.9f,  0.07f,  0.0f);

        glVertex3f( 0.0f,  0.07f,  0.1f);
        glVertex3f( 0.0f,  0.07f,  0.0f);
        glVertex3f( 0.0f,  0.00f,  0.0f);
        glVertex3f( 0.0f,  0.00f,  0.1f);

        glVertex3f( 0.9f,  0.07f,  0.0f);
        glVertex3f( 0.9f,  0.07f,  0.1f);
        glVertex3f( 0.9f,  0.00f,  0.1f);
        glVertex3f( 0.9f,  0.00f,  0.0f);
    glEnd();
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
        //glColor3d(0,0.5,0);
        glTranslated(-0.7,-0.5,-3);
        glRotated(-30,1,0,0);
        mobo();
    glPopMatrix();
    glPushMatrix();
        glColor3d(0,0,0);
        glTranslated(-0.3,0.2,-3);
        glRotated(-30,1,0,0);
        cpu();
    glPopMatrix();
    glPushMatrix();
        glColor3d(0,0,0);
        glTranslated(0.3,0,-3);
        glRotated(-30,1,0,0);
        ram();
    glPopMatrix();
    glPushMatrix();
        glColor3d(0,0,0);
        glTranslated(0.45,0,-3);
        glRotated(-30,1,0,0);
        ram();
    glPopMatrix();
    glPushMatrix();
        glColor3d(0,0,0);
        glTranslated(-0.5,-0.3,-3);
        glRotated(-30,1,0,0);
        vga();
    glPopMatrix();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}



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
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    initGL();
    glutMainLoop();

    return EXIT_SUCCESS;
}
