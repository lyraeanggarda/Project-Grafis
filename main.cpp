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
#include "math.h"
#include <stdlib.h>
float sudut_ba=0, sudut_b=0;
float rotate_kipas=0;
boolean status_kipas = false;
float view_rotx = 0.0f, view_roty = 0.0f;
int oldMouseX, oldMouseY;
float Cx = 1.2, Cy = 1.10, Cz = 0.5;
float Lx = 1, Ly = 1, Lz = 0;
float Tx = 0, Ty = 1, Tz = 0;

float sudut_x = 0.0f, sudut_y = 0.0f, sudut_z = 0.0f;
float sudut_x2 = 0.0f, sudut_y2 = 0.0f, sudut_z2 = 0.0f;

float angle_depanBelakang = 0.0f;
float angle_depanBelakang2 = 0.0f;
float angle_samping = 0.0f;
float angle_samping2 = 0.0f;
float angle_vertikal = 0.0f;
float angle_vertikal2 = 0.0f;

float toRadians(float angle){
    return angle * M_PI / 180;
}

class Vector{
    public: float x, y, z;

    void set_values (float startX, float startY, float startZ){
        x = startX;
        y = startY;
        z = startZ;
    }

    void vectorRotation(Vector refs, float angle){
        Vector temp = refs;
        float magnitude = sqrt(pow(temp.x, 2) + pow(temp.y, 2) + pow(temp.z, 2));
        temp.x = temp.x / magnitude;
        temp.y = temp.y / magnitude;
        temp.z = temp.z / magnitude;
        float dot_product = (x * temp.x)+(y * temp.y)+(z * temp.z);
        float cross_product_x = (y * temp.z) - (temp.z * z);
        float cross_product_y = -((x * temp.z) - (z * temp.x));
        float cross_product_z = (x * temp.y) - (y * temp.x);
        float last_factor_rodrigues = 1.0f - cos(toRadians(fmod(angle, 360.0f)));
        x = (x * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_x * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * x);
        y = (y * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_y * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * y);
        z = (z * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_z * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * z);
    }
};
Vector linear, lateral, vertikal;

void vectorMovement(float toMove[], float magnitude, float direction){
    float speedX = toMove[0]*magnitude*direction;
    float speedY = toMove[1]*magnitude*direction;
    float speedZ = toMove[2]*magnitude*direction;
    Cx += speedX;
    Cy += speedY;
    Cz += speedZ;
    Lx += speedX;
    Ly += speedY;
    Lz += speedZ;
}

void cameraRotation(Vector refer, double angle){
    float M = sqrt(pow(refer.x, 2) + pow(refer.y, 2) + pow(refer.z, 2));
    float Up_x1 = refer.x / M;
    float Up_y1 = refer.y / M;
    float Up_z1 = refer.z / M;
    float VLx = Lx - Cx;
    float VLy = Ly - Cy;
    float VLz = Lz - Cz;
    float dot_product = (VLx * Up_x1) + (VLy * Up_y1) + (VLz * Up_z1);
    float cross_product_x = (Up_y1 * VLz) - (VLy * Up_z1);
    float cross_product_y = -((Up_x1 * VLz) - (Up_z1 * VLx));
    float cross_product_z = (Up_x1 * VLy) - (Up_y1 * VLx);
    float last_factor_rodrigues = 1.0f - cos(toRadians(angle));
    float Lx1 = (VLx * cos(toRadians(angle))) + (cross_product_x * sin(toRadians(angle))) + (dot_product * last_factor_rodrigues * VLx);
    float Ly1 = (VLy * cos(toRadians(angle))) + (cross_product_y * sin(toRadians(angle))) + (dot_product * last_factor_rodrigues * VLy);
    float Lz1 = (VLz * cos(toRadians(angle))) + (cross_product_z * sin(toRadians(angle))) + (dot_product * last_factor_rodrigues * VLz);

    Lx = Lx1+Cx;
    Ly = Ly1+Cy;
    Lz = Lz1+Cz;
}

void mouseControl(int button, int state, int x, int y){
    oldMouseX = x;
    oldMouseY = y;
}

void mouseMotion(int x, int y){
    int getX = x;
    int getY = y;
    float thetaY = 360.0f*(getX - oldMouseX)/640;
    float thetaX = 360.0f*(getY - oldMouseY)/480;
    oldMouseX = getX;
    oldMouseY = getY;
    view_rotx += thetaX;
    view_roty += thetaY;
}


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


void timer(int value) {
  glutPostRedisplay();
  glutTimerFunc(15, timer, 0);
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

void slot_ram(){
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

        glColor3f(0.7,0.7,0);
        glVertex3f( 0.0f,  0.1f,  0.0f);
        glVertex3f( 0.0f,  0.1f,  -0.1f);
//        glColor3f(1,,0);
        glVertex3f( 0.5f,  0.1f,  -0.1f);
        glVertex3f( 0.5f,  0.1f,  0.0f);
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

void ram() {
    glColor3f(0,1,0);
    glBegin(GL_QUADS);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.6f,0.0f,0.0f);
        glVertex3f(0.6f,0.25f,0.0f);
        glVertex3f(0.0f,0.25f,0.0f);

        glVertex3f(0.0f,0.0f,0.04f);
        glVertex3f(0.6f,0.0f,0.04f);
        glVertex3f(0.6f,0.25f,0.04f);
        glVertex3f(0.0f,0.25f,0.04f);

        glVertex3f(0.0f,0.25f,0.0f);
        glVertex3f(0.6f,0.25f,0.0f);
        glVertex3f(0.6f,0.25f,0.04f);
        glVertex3f(0.0f,0.25f,0.04f);

        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.6f,0.0f,0.0f);
        glVertex3f(0.6f,0.0f,0.04f);
        glVertex3f(0.0f,0.0f,0.04f);

        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.04f);
        glVertex3f(0.0f,0.25f,0.04f);
        glVertex3f(0.0f,0.25f,0.0f);

        glVertex3f(0.6f,0.0f,0.0f);
        glVertex3f(0.6f,0.0f,0.04f);
        glVertex3f(0.6f,0.25f,0.04f);
        glVertex3f(0.6f,0.25f,0.0f);

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

//RAHAM START

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


float procZ = -0.3f, heatsinkZ = -0.2f, kipasZ = 0.1f;
bool status_proc = false;
int panjang;
void CopotProc(){
    if(!status_proc){
        status_proc = !status_proc;
        for(panjang=0; panjang<=5; panjang++){
            procZ+=0.1;
            heatsinkZ +=0.15;
        }
        kipasZ=1.0F;
    }
    else{
        status_proc = !status_proc;
        for(panjang=0; panjang<=5; panjang++){
            procZ-=0.1;
            heatsinkZ -=0.15;
        }
        kipasZ=0.1F;
    }


}

void Proc(){

 glColor3d(0.0,0.3,0.1);
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

void PinHeatSink(){
     glBegin(GL_QUADS);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.4f,0.0f,0.0f);
        glVertex3f(0.4f,0.0f,0.3f);
        glVertex3f(0.0f,0.0f,0.3f);
     glEnd();
}

void Heatsink(){
    glTranslatef(0.3f,0.7f,heatsinkZ);
    glColor3d(0.7,0.7,0.7);
    AlasProc();
    float ty=0.0f;
    for(int y=0;y<21;y++){
        glPushMatrix();
        glTranslatef(0,ty,0);
            PinHeatSink();
        glPopMatrix();
        ty+=0.02;
    }
}


void KipasCpu(){
    glColor3d(0.2,0.2,0.2);
    glBegin(GL_QUADS);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.1f);
        glVertex3f(0.15f,0.15f,0.1f);
        glVertex3f(0.1f,0.25f,0.0f);
    glEnd();
    glPushMatrix();
    glRotatef(90,0,0,1);
    glBegin(GL_QUADS);
         glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.1f);
        glVertex3f(0.15f,0.15f,0.1f);
        glVertex3f(0.1f,0.25f,0.0f);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glRotatef(180,0,0,1);
    glBegin(GL_QUADS);
         glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.1f);
        glVertex3f(0.15f,0.15f,0.1f);
        glVertex3f(0.1f,0.25f,0.0f);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glRotatef(270,0,0,1);
    glBegin(GL_QUADS);
         glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.1f);
        glVertex3f(0.15f,0.15f,0.1f);
        glVertex3f(0.1f,0.25f,0.0f);
    glEnd();
    glPopMatrix();
}

//RAHAM END


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

        case 80: //P
             if(!status_kipas){
                status_kipas = true;}
                else{
                status_kipas = false;
                }
            /*if(!status_proc){
                panjang = 0;
                status_proc = true;
                }else{
                panjang = 0;
                status_proc = false;}*/
                CopotProc();
            break;

    }

    glutPostRedisplay();
}

static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

        gluLookAt(Cx, Cy, Cz, // eye pos
                Lx, Ly, Lz, // Look At
                Tx, Ty, Tz);  // up;

    glRotatef(view_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(view_roty, 0.0f, 1.0f, 0.0f);

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
        slot_ram();
    glPopMatrix();
    glPushMatrix();
        glColor3d(0,0,0);
        glTranslatef(1.15,0.7,-0.4);
        slot_ram();
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
        glRotatef(sudut_ba,0.0f,0.0f,1.0f);
        fan();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1.01,0.75,gpuZ-0.07);
        glRotatef(90,1,0,0);
        glRotatef(90,0,1,0);
        ram();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1.17,0.75,gpuZ-0.07);
        glRotatef(90,1,0,0);
        glRotatef(90,0,1,0);
        ram();
    glPopMatrix();

    //Rotasi Kipas
    if(status_kipas){
    rotate_kipas = 0;
    }
    else{
    rotate_kipas += 10;
    if(rotate_kipas == 360) {
        rotate_kipas = 0;
    }
    }
    //Copot Proc
    /*if(status_proc){

        for(panjang=0; panjang<=5; panjang++){
            procZ+=0.1;
        }
    }
    else{
        for(panjang=0; panjang<=5; panjang++){
            procZ-=0.1;

        }
    }*/
    /*
    if(status_proc){
        if(panjang <= 5){
            procZ=+0.1;
            panjang++;
        }
    }else{
        if(panjang <= 5){
            procZ=-0.1;
            panjang++;
        }
    }
*/
    glPushMatrix();
    glTranslatef(0.3f,0.7F,procZ);
    Proc();
    glPopMatrix();
    glPushMatrix();
    Heatsink();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.5f,0.9f,kipasZ);
    glRotatef(rotate_kipas,0.0f,0.0f,1.0f);
    KipasCpu();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
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

    glutCreateWindow("Simulasi Komputer");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutReshapeFunc(reshape);

    glutTimerFunc(0, timer, 0);
    initGL();
    glutMouseFunc(mouseControl);
    glutMotionFunc(mouseMotion);
    glutMainLoop();

    return EXIT_SUCCESS;
}
