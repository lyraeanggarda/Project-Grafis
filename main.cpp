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
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
float sudut_ba=0, sudut_b=0;
boolean status_kipas = false;
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

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
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
        glVertex3f( 0.5f,  0.07f,  0.0f);
        glVertex3f( 0.0f,  0.07f,  0.0f);
        glVertex3f( 0.0f,  0.07f,  0.1f);
        glVertex3f( 0.5f,  0.07f,  0.1f);

        glVertex3f( 0.5f,  0.00f,  0.1f);
        glVertex3f( 0.0f,  0.00f,  0.1f);
        glVertex3f( 0.0f,  0.00f,  0.0f);
        glVertex3f( 0.5f,  0.00f,  0.0f);

        glVertex3f( 0.0f,  0.07f,  0.1f);
        glVertex3f( 0.0f,  0.00f,  0.1f);
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex3f( 0.5f,  0.00f,  0.1f);
        glVertex3f( 0.5f,  0.07f,  0.1f);

        glVertex3f( 0.5f,  0.00f,  0.0f);
        glVertex3f( 0.0f,  0.00f,  0.0f);
        glVertex3f( 0.0f,  0.07f,  0.0f);
        glVertex3f( 0.5f,  0.07f,  0.0f);

        glVertex3f( 0.0f,  0.07f,  0.1f);
        glVertex3f( 0.0f,  0.07f,  0.0f);
        glVertex3f( 0.0f,  0.00f,  0.0f);
        glVertex3f( 0.0f,  0.00f,  0.1f);

        glVertex3f( 0.5f,  0.07f,  0.0f);
        glVertex3f( 0.5f,  0.07f,  0.1f);
        glVertex3f( 0.5f,  0.00f,  0.1f);
        glVertex3f( 0.5f,  0.00f,  0.0f);
    glEnd();
}

void gpu(){
    glBegin(GL_QUADS);

        glVertex3f( 0.7f,  0.0f,  0.4f);
        glVertex3f( 0.0f,  0.0f,  0.4f);
        glVertex3f( 0.0f,  0.15f,  0.4f);
        glVertex3f( 0.7f,  0.15f,  0.4f);

        glVertex3f( 0.7f,  0.15f,  0.0f);
        glVertex3f( 0.0f,  0.15f,  0.0f);
        glVertex3f( 0.0f,  0.0f,  0.0f);
        glVertex3f( 0.7f,  0.0f,  0.0f);

        glVertex3f( 0.0f,  0.15f,  0.4f);
        glVertex3f( 0.0f,  0.15f,  0.0f);
        glVertex3f( 0.7f,  0.15f,  0.0f);
        glVertex3f( 0.7f,  0.15f,  0.4f);

        glVertex3f( 0.7f,  0.0f,  0.0f);
        glVertex3f( 0.0f,  0.0f,  0.0f);
        glVertex3f( 0.0f,  0.0f,  0.4f);
        glVertex3f( 0.7f,  0.0f,  0.4f);

        glVertex3f( 0.0f,  0.15f,  0.4f);
        glVertex3f( 0.0f,  0.0f,  0.4f);
        glVertex3f( 0.0f,  0.0f,  0.0f);
        glVertex3f( 0.0f,  0.15f,  0.0f);

        glVertex3f( 0.7f,  0.0f,  0.4f);
        glVertex3f( 0.7f,  0.15f,  0.4f);
        glVertex3f( 0.7f,  0.15f,  0.0f);
        glVertex3f( 0.7f,  0.0f,  0.0f);
    glEnd();
}

void fan(){
    float pjg_sayap = 0.25f;
      glPushMatrix();
        glTranslatef(0.0f,0.0f,0.0f);
        glRotatef(sudut_ba, 0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
          glVertex3f(0.025f,0.025f,0.0f);
          glVertex3f(0.025f,-0.025f,0.0f);
          glVertex3f(pjg_sayap,-0.05f,0.0f);
          glVertex3f(pjg_sayap,0.05f,0.0f);
        glEnd();
        glBegin(GL_QUADS);
          glVertex3f(0.025f,0.025f,0.0f);
          glVertex3f(-0.025f,0.025f,0.0f);
          glVertex3f(-0.05f,pjg_sayap,0.0f);
          glVertex3f(0.05f,pjg_sayap,0.0f);
        glEnd();
        glBegin(GL_QUADS);
          glVertex3f(-0.025f,0.025f,0.0f);
          glVertex3f(-0.025f,-0.025f,0.0f);
          glVertex3f(-pjg_sayap,-0.05f,0.0f);
          glVertex3f(-pjg_sayap,0.05f,0.0f);
        glEnd();
        glBegin(GL_QUADS);
          glVertex3f(-0.025f,-0.025f,0.0f);
          glVertex3f(0.025f,-0.025f,0.0f);
          glVertex3f(0.05f,-pjg_sayap,0.0f);
          glVertex3f(-0.05f,-pjg_sayap,0.0f);
        glEnd();
      glPopMatrix();

}

void psu() {
    glBegin(GL_QUADS);
      // Top face
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( 0.0f, 0.5f, 0.0f);
      glVertex3f(1.0f, 0.5f, 0.0f);
      glVertex3f(1.0f, 0.5f,  1.0f);
      glVertex3f( 0.0f, 0.5f,  1.0f);

      // Bottom face
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 0.0f, 0.0f,  0.0f);
      glVertex3f(1.0f, 0.0f,  0.0f);
      glVertex3f(1.0f, 0.0f, 1.0f);
      glVertex3f( 0.0f, 0.0f, 1.0f);

      // Front face
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 0.0f,  0.0f, 1.0f);
      glVertex3f(0.5f,  0.0f, 1.0f);
      glVertex3f(0.5f, 0.5f, 1.0f);
      glVertex3f( 0.0f, 0.5f, 1.0f);

//      // Back face
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 0.0f, 0.0f, 0.0f);
      glVertex3f(1.0f, 0.0f, 0.0f);
      glVertex3f(1.0f,  0.5f, 0.0f);
      glVertex3f( 0.0f,  0.5f, 0.0f);

//      // Left face
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(0.0f,  0.0f,  1.0f);
      glVertex3f(0.0f,  0.0f, 0.0f);
      glVertex3f(0.0f, 0.5f, 0.0f);
      glVertex3f(0.0f, 0.5f,  1.0f);
//
//      // Right face
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(1.0f, 0.0f, 1.0f);
      glVertex3f(1.0f, 0.0f,  0.0f);
      glVertex3f(1.0f, 0.5f,  0.0f);
      glVertex3f(1.0f, 0.5f, 1.0f);
   glEnd();
}


double rotate_y = 0;
double rotate_x = 0;
double rotate_z = 0;

float gpuZ=-0.3f;
bool statusGPU = false;
void copotGPU(){

    if(!statusGPU){
        statusGPU = true;
        while(gpuZ<0.3f){
            gpuZ+=0.1;
        }
    }
    else{
        statusGPU = false;
        while(gpuZ>-0.3f){
            gpuZ-=0.1;
        }
    }
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case 87: //W
            rotate_x += 5;
            break;

        case 83: //S
            rotate_x -= 5;
            break;

        case 65: //A
            rotate_y += 5;
            break;

        case 68: //D
            rotate_y -= 5;
            break;

        case 81: //Q
            rotate_z -= 5;
            break;

        case 69: //E
            rotate_z += 5;
            break;

        case 86: //V
            copotGPU();
            if(!status_kipas)
                status_kipas = true;
                else
                status_kipas = false;
            break;
    }

    glutPostRedisplay();
}

static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);
    glTranslatef(-0.7,-0.5,-1);
    glRotatef(rotate_x, 1.0,0.0,0.0);
    glRotatef(rotate_y, 0.0,1.0,0.0);
    glRotatef(rotate_z, 0.0,0.0,1.0);
if(status_kipas){
    sudut_ba = 0;
}
else{
  sudut_ba += 50;
  if(sudut_ba == 360) {
      sudut_ba = 0;
  }
}
    glPushMatrix();
        glTranslatef(0,0,-0.4);
        mobo();
    glPopMatrix();
    glPushMatrix();
        glColor3d(0,0,0);
        glTranslatef(0.3,0.7,-0.4);
        cpu();
    glPopMatrix();
    glPushMatrix();
        glColor3d(0,0,0);
        glTranslatef(1.0,0.7,-0.4);
        ram();
    glPopMatrix();
    glPushMatrix();
        glColor3d(0,0,0);
        glTranslatef(1.15,0.7,-0.4);
        ram();
    glPopMatrix();
    glPushMatrix();
        glColor3d(0,0,0);
        glTranslatef(0.2,0.4 ,-0.4);
        vga();
    glPopMatrix();
    glPushMatrix();
        glColor3d(1,0,0);
        glTranslatef(0.2,0.33,gpuZ);
        gpu();
    glPopMatrix();
    glPushMatrix();
        glColor3d(0,0,0);
        glTranslatef(0.53,0.32,gpuZ+0.15);
        glRotatef(90,1,0,0);
        glRotatef(sudut_ba,0.0f,0.0f,1.0f);
        fan();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-1.2,1,-0.6);
        glRotatef(90,1.0f, 0.0f, 0.0f);
        psu();
    glPopMatrix();
    glPushMatrix();
        glColor3d(0,0,0);
        glTranslatef(-0.45,0.1,-0.35);
        glRotatef(90,1,0,0);
        glRotatef(sudut_b,0.0f,0.0f,1.0f);
        fan();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}



static void idle(void)
{
    glutPostRedisplay();
}


void timer(int value) {
  glutPostRedisplay();
  glutTimerFunc(15, timer, 0);
}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Simulasi Komputer");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutReshapeFunc(reshape);

    glutTimerFunc(0, timer, 0);
    initGL();
    glutMainLoop();

    return EXIT_SUCCESS;
}
