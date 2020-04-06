
// This is demo program for creating a car using OpenGL.
// The car can be run using control keys.
// Original contribution: Sai Kumar Minajagi
// Modified for the purpose of cpsc3710

#include <GL/glut.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>

#define ESCAPE 27

GLint window;
GLint window2;
GLint Xsize = 1000;
GLint Ysize = 800;
GLint nml = 0;

GLfloat xt = 0.0, yt = 0.0, zt = 0.0, xw = 0.0;
GLfloat xs = 1.0, ys = 1.0, zs = 1.0;
GLfloat xangle = 5.0, yangle = 0.0, zangle = 0.0, angle = 0.0;
GLfloat rot = 0;

GLfloat r = 0, g = 0, b = 1;
GLUquadricObj *t;

static void SpecialKeyFunc(int Key, int x, int y);

GLvoid Transform(GLfloat Width, GLfloat Height) {
  glViewport(0, 0, Width, Height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, Width / Height, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

GLvoid InitGL(GLfloat Width, GLfloat Height) {

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glLineWidth(2.0);              /* Add line width,   ditto */
  Transform(Width, Height);   /* Perform the transformation */
  t = gluNewQuadric();
  gluQuadricDrawStyle(t, GLU_FILL);

  glEnable(GL_LIGHTING);

  glEnable(GL_LIGHT0);

  GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
  GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
  GLfloat position[] = { 1.5f, 1.0f, 4.0f, 1.0f };

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT0, GL_POSITION, position);

}

void init() {
  glClearColor(0, 0, 0, 0);
  glPointSize(5.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 900.0, 0.0, 600.0, 50.0, -50.0);
  glutPostRedisplay();
}

void draw2() {
  // cylinder
  glColor3f(1, 0, 0);
  glTranslatef(0, 3, -3);
  glRotatef(90.0, 1.0, 0.0, 0.0); //x
  gluCylinder(t, 1, 1, 3, 10, 10);

  // cube at top
  glRotatef(rot++, 0, 0, 1); //y
  glutSolidCube(2);

  glPopMatrix();
}

GLvoid DrawGLScene() {
  float theta, i;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  InitGL(Xsize, Ysize);

  glClearColor(1, 1, 1, 1);

  glPushMatrix();
  glLoadIdentity();
  glTranslatef(-1.0, 0.0, -3.5);
  glRotatef(xangle, 1.0, 0.0, 0.0);
  glRotatef(yangle, 0.0, 1.0, 0.0);
  glRotatef(zangle, 0.0, 0.0, 1.0);
  glTranslatef(xt, yt, zt);
  glScalef(xs, ys, zs);
  glEnable(GL_COLOR_MATERIAL);

  // For fog effect
  GLfloat fogcolour[4] = {1.0, 1.0, 1.0, 1.0};
  glFogfv(GL_FOG_COLOR, fogcolour);
  glFogf(GL_FOG_DENSITY, 0.1);
  glFogi(GL_FOG_MODE, GL_EXP);
  glFogf(GL_FOG_START, 3.0);
  glFogf(GL_FOG_END, 100.0);
  glHint(GL_FOG_HINT, GL_FASTEST);
  glEnable(GL_FOG);

  glColor3f(1.0, .75, 0.0);
  glPointSize(30.0);
  glBegin(GL_POINTS);
  glVertex3f(0.2, 0.3, 0.3);
  glVertex3f(0.2, 0.3, 0.5);
  glEnd();
  glPointSize(200.0);

  glBegin(GL_QUADS);
  /* top of cube*/
  //************************FRONT BODY****************************************
  glColor3f(r, g, b);
  glVertex3f(0.2, 0.4, 0.6);
  glVertex3f(0.6, 0.5, 0.6);
  glVertex3f(0.6, 0.5, 0.2);
  glVertex3f(0.2, 0.4, 0.2);
  /* bottom of cube*/
  glVertex3f(0.2, 0.4, 0.6);
  glVertex3f(0.6, 0.2, 0.6);
  glVertex3f(0.6, 0.2, 0.2);
  glVertex3f(0.2, 0.2, 0.2);
  /* front of cube*/
  glVertex3f(0.2, 0.2, 0.6);
  glVertex3f(0.2, 0.4, 0.6);
  glVertex3f(0.2, 0.4, 0.2);
  glVertex3f(0.2, 0.2, 0.2);
  /* back of cube.*/
  glVertex3f(0.6, 0.2, 0.6);
  glVertex3f(0.6, 0.5, 0.6);
  glVertex3f(0.6, 0.5, 0.2);
  glVertex3f(0.6, 0.2, 0.2);
  /* left of cube*/
  glVertex3f(0.2, 0.2, 0.6);
  glVertex3f(0.6, 0.2, 0.6);
  glVertex3f(0.6, 0.5, 0.6);
  glVertex3f(0.2, 0.4, 0.6);
  /* Right of cube */
  glVertex3f(0.2, 0.2, 0.2);
  glVertex3f(0.6, 0.2, 0.2);
  glVertex3f(0.6, 0.5, 0.2);
  glVertex3f(0.2, 0.4, 0.2);

  //****************************************************************************
  glVertex3f(0.7, 0.65, 0.6);
  glVertex3f(0.7, 0.65, 0.2);
  glVertex3f(1.7, 0.65, 0.2);
  glVertex3f(1.7, 0.65, 0.6);

  //***************************back guard******************************
  // You can change r, g, b to different colors.
  glColor3f(r, g, b);
  glVertex3f(1.8, 0.5, 0.6);
  glVertex3f(1.8, 0.5, 0.2);
  glVertex3f(2.1, 0.4, 0.2);
  glVertex3f(2.1, 0.4, 0.6);
  /* bottom of cube*/
  glVertex3f(2.1, 0.2, 0.6);
  glVertex3f(2.1, 0.2, 0.2);
  glVertex3f(1.8, 0.2, 0.6);
  glVertex3f(1.8, 0.2, 0.6);
  /* back of cube.*/
  glVertex3f(2.1, 0.4, 0.6);
  glVertex3f(2.1, 0.4, 0.2);
  glVertex3f(2.1, 0.2, 0.2);
  glVertex3f(2.1, 0.2, 0.6);
  /* left of cube*/
  glVertex3f(1.8, 0.2, 0.2);
  glVertex3f(1.8, 0.5, 0.2);
  glVertex3f(2.1, 0.4, 0.2);
  glVertex3f(2.1, 0.2, 0.2);
  /* Right of cube */
  glVertex3f(1.8, 0.2, 0.6);
  glVertex3f(1.8, 0.5, 0.6);
  glVertex3f(2.1, 0.4, 0.6);
  glVertex3f(2.1, 0.2, 0.6);

  //******************MIDDLE BODY************************************
  glVertex3f(0.6, 0.5, 0.6);
  glVertex3f(0.6, 0.2, 0.6);
  glVertex3f(1.8, 0.2, 0.6);
  glVertex3f(1.8, 0.5, 0.6);

  /* bottom of cube*/
  glVertex3f(0.6, 0.2, 0.6);
  glVertex3f(0.6, 0.2, 0.2);
  glVertex3f(1.8, 0.2, 0.2);
  glVertex3f(1.8, 0.2, 0.6);

  /* back of cube.*/
  glVertex3f(0.6, 0.5, 0.2);
  glVertex3f(0.6, 0.2, 0.2);
  glVertex3f(1.8, 0.2, 0.2);
  glVertex3f(1.8, 0.5, 0.2);

  //*********************ENTER WINDOW**********************************
  glColor3f(0.3, 0.3, 0.3);
  glVertex3f(0.77, 0.63, 0.2);
  glVertex3f(0.75, 0.5, 0.2);       //quad front window
  glVertex3f(1.2, 0.5, 0.2);
  glVertex3f(1.22, 0.63, 0.2);

  glVertex3f(1.27, 0.63, .2);
  glVertex3f(1.25, 0.5, 0.2);      //quad back window
  glVertex3f(1.65, 0.5, 0.2);
  glVertex3f(1.67, 0.63, 0.2);

  glColor3f(r, g, b);
  glVertex3f(0.7, 0.65, 0.2);
  glVertex3f(0.7, 0.5, .2);     //first separation
  glVertex3f(0.75, 0.5, 0.2);
  glVertex3f(0.77, 0.65, 0.2);

  glVertex3f(1.2, 0.65, 0.2);
  glVertex3f(1.2, 0.5, .2);     //second separation
  glVertex3f(1.25, 0.5, 0.2);
  glVertex3f(1.27, 0.65, 0.2);

  glVertex3f(1.65, 0.65, 0.2);
  glVertex3f(1.65, 0.5, .2);   //3d separation
  glVertex3f(1.7, 0.5, 0.2);
  glVertex3f(1.7, 0.65, 0.2);

  glVertex3f(0.75, 0.65, 0.2);
  glVertex3f(0.75, 0.63, 0.2);       //line strip
  glVertex3f(1.7, 0.63, 0.2);
  glVertex3f(1.7, 0.65, 0.2);

  glVertex3f(0.75, 0.65, 0.6);
  glVertex3f(0.75, 0.63, 0.6);       //line strip
  glVertex3f(1.7, 0.63, 0.6);
  glVertex3f(1.7, 0.65, 0.6);

  glColor3f(0.3, 0.3, 0.3);
  glVertex3f(0.77, 0.63, 0.6);
  glVertex3f(0.75, 0.5, 0.6);       //quad front window
  glVertex3f(1.2, 0.5, 0.6);
  glVertex3f(1.22, 0.63, 0.6);

  glVertex3f(1.27, 0.63, .6);
  glVertex3f(1.25, 0.5, 0.6);      //quad back window
  glVertex3f(1.65, 0.5, 0.6);
  glVertex3f(1.67, 0.63, 0.6);

  glColor3f(r, g, b);
  glVertex3f(0.7, 0.65, 0.6);
  glVertex3f(0.7, 0.5, .6);     //first separation
  glVertex3f(0.75, 0.5, 0.6);
  glVertex3f(0.77, 0.65, 0.6);

  glVertex3f(1.2, 0.65, 0.6);
  glVertex3f(1.2, 0.5, .6);     //second separation
  glVertex3f(1.25, 0.5, 0.6);
  glVertex3f(1.27, 0.65, 0.6);

  glVertex3f(1.65, 0.65, 0.6);
  glVertex3f(1.65, 0.5, .6);
  glVertex3f(1.7, 0.5, 0.6);
  glVertex3f(1.7, 0.65, 0.6);
  glEnd();


  //**************************************************************
  glBegin(GL_QUADS);

  /* top of cube*/
  glColor3f(0.3, 0.3, 0.3);
  glVertex3f(0.6, 0.5, 0.6);
  glVertex3f(0.6, 0.5, 0.2);       //quad front window
  glVertex3f(0.7, 0.65, 0.2);
  glVertex3f(0.7, 0.65, 0.6);

  glVertex3f(1.7, 0.65, .6);
  glVertex3f(1.7, 0.65, 0.2);      //quad back window
  glVertex3f(1.8, 0.5, 0.2);
  glVertex3f(1.8, 0.5, 0.6);

  //*****************************road and surrounding development***********************************
  glPushMatrix();
  glTranslatef(xw, 0, 0);
  glColor3f(0, 1, 0);
  glVertex3f(-100, 0.1, -100);
  glVertex3f(-100, 0.1, 0);       //a green surroundings
  glVertex3f(100, 0.1, 0);
  glVertex3f(100, 0.1, -100);

  glColor3f(0.7, 0.7, 0.7);
  glVertex3f(-100, 0.1, 0);
  glVertex3f(-100, 0.1, 0.45);       //a long road
  glVertex3f(100, 0.1, 0.45);
  glVertex3f(100, 0.1, 0);

  glColor3f(1.0, 0.75, 0.0);
  glVertex3f(-100, 0.1, 0.45);     //a median
  glVertex3f(-100, 0.1, 0.55);
  glVertex3f(100, 0.1, 0.55);
  glVertex3f(100, 0.1, 0.45);

  glColor3f(0.7, 0.7, 0.7);
  glVertex3f(-100, 0.1, 0.55);
  glVertex3f(-100, 0.1, 1);       //a long road
  glVertex3f(100, 0.1, 1);
  glVertex3f(100, 0.1, 0.55);

  glColor3f(0, 1, 0);
  glVertex3f(-100, 0.1, 1);
  glVertex3f(-100, 0.1, 100);       //a green surroundings
  glVertex3f(100, 0.1, 100);
  glVertex3f(100, 0.1, 1);
  glPopMatrix();
  glEnd();

  glPushMatrix();
  glTranslatef(xw, 0, 0);
  glColor3f(0.5, .2, 0.3);
  glBegin(GL_QUADS);
  for(i = 0; i < 200; i += 0.2) {
    glVertex3f(-100 + i, 0, 1);
    glVertex3f(-99.9 + i, 0, 1);
    glVertex3f(-99.9 + i, 0.2, 1);
    glVertex3f(-100 + i, 0.2, 1);
    i += 0.5;
  }
  for(i = 0; i < 200; i += 0.2) {
    glVertex3f(-100 + i, 0, 0);
    glVertex3f(-99.9 + i, 0, 0);
    glVertex3f(-99.9 + i, 0.2, 0);
    glVertex3f(-100 + i, 0.2, 0);
    i += 0.5;
  }
  glEnd();
  glPopMatrix();

  glBegin(GL_TRIANGLES);                /* start drawing the cube.*/

  /* top of cube*/
  glColor3f(0.3, 0.3, 0.3);
  glVertex3f(0.6, 0.5, 0.6);
  glVertex3f(0.7, 0.65, 0.6);      //tri front window
  glVertex3f(0.7, 0.5, 0.6);

  glVertex3f(0.6, 0.5, 0.2);
  glVertex3f(0.7, 0.65, 0.2);      //tri front window
  glVertex3f(0.7, 0.5, 0.2);

  glVertex3f(1.7, 0.65, 0.2);
  glVertex3f(1.8, 0.5, 0.2);      //tri back window
  glVertex3f(1.7, 0.5, 0.2);

  glVertex3f(1.7, 0.65, 0.6);
  glVertex3f(1.8, 0.5, 0.6);      //tri back window
  glVertex3f(1.7, 0.5, 0.6);
  glEnd();

  //************IGNITION SYSTEM
  glPushMatrix();
  glColor3f(0.3, 0.3, 0.7);
  glTranslatef(1.65, 0.2, 0.3);
  glRotatef(90.0, 0, 1, 0);
  gluCylinder(t, 0.02, 0.03, .5, 10, 10);
  glPopMatrix();

  //********************WHEEL
  glColor3f(0.7, 0.7, 0.7);
  glPushMatrix();
  glBegin(GL_LINE_STRIP);
  for(theta = 0; theta < 360; theta = theta + 40) {
    glVertex3f(0.6, 0.2, 0.62);
    glVertex3f(0.6 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.62);
  }
  glEnd();

  glBegin(GL_LINE_STRIP);
  for(theta = 0; theta < 360; theta = theta + 40) {
    glVertex3f(0.6, 0.2, 0.18);
    glVertex3f(0.6 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.18);
  }
  glEnd();

  glBegin(GL_LINE_STRIP);
  for(theta = 0; theta < 360; theta = theta + 40) {
    glVertex3f(1.7, 0.2, 0.18);
    glVertex3f(1.7 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.18);
  }
  glEnd();

  glBegin(GL_LINE_STRIP);
  for(theta = 0; theta < 360; theta = theta + 40) {
    glVertex3f(1.7, 0.2, 0.62);
    glVertex3f(1.7 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.62);
  }
  glEnd();

  glTranslatef(0.6, 0.2, 0.6);
  glColor3f(0, 0, 0);
  glutSolidTorus(0.025, 0.07, 10, 25);

  glTranslatef(0, 0, -0.4);
  glutSolidTorus(0.025, 0.07, 10, 25);

  glTranslatef(1.1, 0, 0);
  glutSolidTorus(0.025, 0.07, 10, 25);

  glTranslatef(0, 0, 0.4);
  glutSolidTorus(0.025, 0.07, 10, 25);
  glPopMatrix();

  //*************************************************************
  draw2();
  glPopMatrix();


  glEnable(GL_DEPTH_TEST);
  glutPostRedisplay();
  glutSwapBuffers();
}

void NormalKey(GLubyte key, GLint x, GLint y) {
  switch(key)    {
  case ESCAPE :
    printf("escape pressed. exit.\n");
    glutDestroyWindow(window);
    exit(0);
    break;
  case 'x':
    xangle += 5.0;
    glutPostRedisplay();
    break;
  case 'X':
    xangle -= 5.0;
    glutPostRedisplay();
    break;
  case 'y':
    yangle += 5.0;
    glutPostRedisplay();
    break;
  case 'Y':
    yangle -= 5.0;
    glutPostRedisplay();
    break;
  case 'z':
    zangle += 5.0;
    glutPostRedisplay();
    break;
  case 'Z':
    zangle -= 5.0;
    glutPostRedisplay();
    break;
  case 'u':                          /* Move up */
    yt += 0.2;
    glutPostRedisplay();
    break;
  case 'U':
    yt -= 0.2;                      /* Move down */
    glutPostRedisplay();
    break;
  case 'f':                          /* Move forward */
    zt += 0.2;
    glutPostRedisplay();
    break;
  case 'F':
    zt -= 0.2;                      /* Move away */
    glutPostRedisplay();
    break;
  default:
    break;
  }
}

static void SpecialKeyFunc(int Key, int x, int y) {
  switch(Key) {
  case GLUT_KEY_RIGHT:
    angle += 5;
    xw += 0.2;
    glutPostRedisplay();
    break;
  case GLUT_KEY_LEFT:
    angle += 5;
    xw -= 0.2;
    glutPostRedisplay();
    break;
  default:
    break;
  }
}

void colorMenu(int id) {
  switch(id) {
  case 6:
    r = g = 0;
    b = 1;
    glutPostRedisplay();
    break;
  case 7:
    r = 0.8;
    b = g = 0;
    glutPostRedisplay();
    break;
  case 8:
    g = 1;
    r = b = 0;
    glutPostRedisplay();
    break;
  case 9:
    r = b = g = 0;
    glutPostRedisplay();
    break;
  case 10:
    b = 0;
    r = g = 1;
    glutPostRedisplay();
    break;
  case 11:
    b = r = g = .7;
    glutPostRedisplay();
    break;
  default:
    break;
  }
}

int main(int argc, char **argv) {
  printf("Car Animation Demo for CPSC3710\n");
  printf("MOUSE\n");
  printf("\tPRESS RIGHT BUTTON FOR MENU\n");
  printf("KEYBOARD\n");
  printf("\tX-Y-Z KEYS FOR CORRESPONDING ROTATION\n");
  printf("\tU-F FOR CAMERA VIEW SETTINGS\n");
  printf("\tUSE LEFT ARROW(<-) AND RIGHT ARROW(->) TO MOVE CAR\n");
  printf("\tESCAPE TO EXIT\n");

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

  glutInitWindowSize(Xsize, Ysize);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("3D CAR ANIMATION");
  init();
  glutDisplayFunc(DrawGLScene);
  glutKeyboardFunc(NormalKey);
  glutSpecialFunc(SpecialKeyFunc);
  InitGL(Xsize, Ysize);

  glutCreateMenu(colorMenu);
  // You can change the color of the car
  glutAddMenuEntry("blue", 6);
  glutAddMenuEntry("red", 7);
  glutAddMenuEntry("green", 8);
  glutAddMenuEntry("black", 9);
  glutAddMenuEntry("yellow", 10);
  glutAddMenuEntry("grey", 11);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return 1;
}
