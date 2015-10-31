/*
 * Ninja Trash
 * Proyecto Graficas Computacional
 * Semestre Ago-Dic 2015
 */
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include<math.h>
using namespace std;

int ancho=500;
int largo=500;
bool jugando=false;
int nivel = 1;
int puntuacionActual=0;
//Valores de los objetos a recoger
int valoraciones[]={5,10,15,25};

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    ancho=width;
    largo=height;
    glClearColor(1,1,1,0);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2, 1, 150);
    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    gluLookAt(0, 0, 15, 0, 0, 0, 0, 1,0);
}
static void timer(int i){

}
static void dibujaBotonMadera(int ancho){
    glLineWidth(1);
    glColor3f(0.9,0.05,0);
    glPushMatrix();
    glRotatef(-0.5,0,0,1);

    glBegin(GL_QUADS);
    glVertex2f(0.002*ancho,0*ancho);
    glVertex2f(0.002*ancho,0.1*ancho);
    glVertex2f(0.7*ancho,0.09*ancho);
    glVertex2f(0.65*ancho,0*ancho);
    glEnd();
    glPopMatrix();
    glColor3f(0,0,0);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0*ancho,0*ancho);
    glVertex2f(0.03*ancho,0.04*ancho);
    glVertex2f(0*ancho,0.05*ancho);
    glVertex2f(0.05*ancho,0.06*ancho);
    glVertex2f(0*ancho,0.07*ancho);
    glVertex2f(0.05*ancho,0.1*ancho);
    glVertex2f(0.65*ancho,0.085*ancho);
    glVertex2f(0.7*ancho,0.07*ancho);
    glVertex2f(0.65*ancho,0.06*ancho);
    glVertex2f(0.7*ancho,0.05*ancho);
    glVertex2f(0.65*ancho,0.04*ancho);
    glVertex2f(0.55*ancho,0.02*ancho);
    glVertex2f(0.7*ancho,0*ancho);
    glEnd();
    glLineWidth(1);
    glColor3f(0.9,0.05,0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0*ancho,0*ancho);
    glVertex2f(0.02*ancho,0.03*ancho);
    glVertex2f(0*ancho,0.04*ancho);
    glVertex2f(0.04*ancho,0.05*ancho);
    glVertex2f(0*ancho,0.06*ancho);
    glVertex2f(0.04*ancho,0.09*ancho);
    glVertex2f(0.64*ancho,0.084*ancho);
    glVertex2f(0.6*ancho,0.06*ancho);
    glVertex2f(0.64*ancho,0.05*ancho);
    glVertex2f(0.6*ancho,0.04*ancho);
    glVertex2f(0.64*ancho,0.03*ancho);
    glVertex2f(0.54*ancho,0.01*ancho);
    glVertex2f(0.6*ancho,0*ancho);
    glEnd();

}
static void dibujaBotonHome(int ancho){
    //Fondo
    glColor3f(0.85,0.1,0);
    glBegin(GL_QUADS);
    glVertex2f(0*ancho,0*ancho);
    glVertex2f(0*ancho,1*ancho);
    glVertex2f(1*ancho,1*ancho);
    glVertex2f(1*ancho,0*ancho);
    glEnd();
    //Techo
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(0.1*(ancho),0.5*(ancho));
    glVertex2f(0.5*(ancho),0.8*(ancho));
    glVertex2f(0.5*(ancho),0.8*(ancho));
    glVertex2f(0.9*(ancho),0.5*(ancho));
    glEnd();
    //Piso
    glPushMatrix();
    glRotatef(10,0,0,1);
    glBegin(GL_LINES);
    glVertex2f(0.2*ancho,0.1*ancho);
    glVertex2f(0.8*ancho,0.1*ancho);
    glEnd();
    glPopMatrix();
    //Pared izquierda
    glBegin(GL_LINES);
    glVertex2f(0.65*ancho,0.2*ancho);
    glVertex2f(0.65*ancho,0.5*ancho);
    glEnd();
    //Pared derecha
    glBegin(GL_LINES);
    glVertex2f(0.35*ancho,0.15*ancho);
    glVertex2f(0.35*ancho,0.5*ancho);
    glEnd();
}
static void medioCirculo(){
    glBegin(GL_LINE_LOOP);
    double  PI = 3.141592654;
    double angle = 0.0;
    int points = 100;
    for(int i =0; i < points;i++){
    angle = PI * i / points;
    glVertex2f((float)cos(angle),(float)sin(angle));

    }
    glEnd();
}
static void dibujaCaraNinja(int red,int green,int blue){
    glLineWidth(2);


    //Base
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(4,5.5,1);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();

    //Frente
    glPushMatrix();
    glTranslatef(0,1,0);
    glScalef(4.5,5.1,1);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();
    //Cinta
    glPushMatrix();
    glColor3f(red,green,blue);
    glTranslatef(0,5,0);
    glScalef(28.5,2.5,1);
    glutSolidCube(1);
    glPopMatrix();
    //Ojo izquierdo
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(5.5,-2.1,0);
    glScalef(2.3,1.5,1);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(5.5,-2.1,0);
    glScalef(0.4,0.3,0);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();
    //ojo derecho
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(-5.5,-2.1,0);
    glScalef(2.3,1.5,1);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-5.5,-2.1,0);
    glScalef(0.4,0.3,0);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();
    //Boca
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-0.2,-10.5,0);
    glScalef(4.9,2,1);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();

    ////Linea plana
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0,-5.3,0);
    glScalef(3.8,0.5,1);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();


}
static void dibujaBasurero(){
    //Brazos
    //Izquierdo
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(-5.5,2.5,0);
    glRotatef(20,0,-1,-1.5);
    glScalef(0.5,1,1);
    glutSolidSphere(3.14,100,2);
    glPopMatrix();
    //Derecho
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(5.5,2.5,0);
    glRotatef(20,0,-1,1.5);
    glScalef(0.5,1,1);
    glutSolidSphere(3.14,100,2);
    glPopMatrix();
    //Base
    glColor3f(0.5,0.5,0.5);
    glPushMatrix();
    glScalef(9,8,1);
    glutSolidCube(1);
    glPopMatrix();
    glColor3f(0.8,0.8,0.8);
    //Arriba
    glPushMatrix();
    glTranslatef(0,4.5,0);
    glScalef(1.5,1,1);
    glutSolidSphere(3.14,100,2);
    glPopMatrix();
    glColor3f(0.5,0.5,0.5);
    //Abajo
    glPushMatrix();
    glTranslatef(0,-5,0);
    glScalef(1.5,1,1);
    glutSolidSphere(3.14,100,2);
    glPopMatrix();
    //Decorado
    glColor3f(0,0,0);
    glPushMatrix();
    glScalef(3.5,16,1);
    glBegin(GL_LINES);
    glVertex2f(-0.5,-0.5);
    glVertex2f(-0.5,0);
    glVertex2f(0,-0.5);
    glVertex2f(0,0.01);
    glVertex2f(0.5,-0.5);
    glVertex2f(0.5,0);
    glEnd();
    glPopMatrix();


}
static void letrero(string palabra){

    int yRaster=0;
    int xRaster =0;

    glColor3f(0, 0,0);

    for(int j=0;j < palabra.length();j++){
       char valor=palabra.at(j);
       glRasterPos2i(xRaster,yRaster);
       glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,valor);
       xRaster+=10;
    }
}
static void dibujaTapaBasurero(){

}
static void dibujaEstrellas(){

}
static void pantallaInicial(){
    //Fondo
    glColor3f(0.271,0.063,0);
    glBegin(GL_QUADS);
    glVertex2f(-(ancho/2),(largo/2));
    glVertex2f((ancho/2),(largo/2));
    glVertex2f((ancho/2),-(largo/2));
    glVertex2f(-(ancho/2),-(largo/2));
    glEnd();

    //Barra blanca
    glColor3f(0.96,0.56,0.2);
    glBegin(GL_QUADS);
    glVertex2f(-(ancho/2),(largo/2));
    glVertex2f((ancho/2),(largo/2));
    glVertex2f((ancho/2),(largo/4));
    glVertex2f(-(ancho/2),(largo/4));
    glEnd();
    //Separador
    glPushMatrix();
    glColor3f(0,0,0);
    glRotatef(1,0,0,1);
    glLineWidth(1);
    for(int i=0;i<3;i++){
    glBegin(GL_LINES);
    glVertex2f(-(ancho/2),((largo/4)-(1.5*i)));
    glVertex2f((ancho/2),((largo/4)-(1.5*i)));
    glEnd();
    }
    glPopMatrix();
    //Parte de arriba
    glPushMatrix();
    glTranslatef((-(ancho/4))+ancho/8,(largo/4)+15,1);
    glScalef(300,700,1);
    dibujaBotonMadera(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((-(ancho/4))+ancho/5,(largo/4)+20,1);
    glScalef(2.5,10,1);
    letrero("Jugar");
    glPopMatrix();
}
static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pantallaInicial();
    glPushMatrix();
    glTranslatef((-(ancho/2))+50,largo/4,1);
    glScalef(50,50,1);
    dibujaBotonHome(1);
    glPopMatrix();


    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-(ancho/4),0,1);
    glScalef(2,2,0);
    glRotatef(10,1,1,0);
    dibujaCaraNinja(1,0,0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(0,0,1);
    glScalef(2,2,0);
    dibujaCaraNinja(0,1,0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(ancho/4,0,1);
    glScalef(2,2,0);
    dibujaCaraNinja(0,0,1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(ancho/4,-60,1);
    glScalef(6,5,1);
    dibujaBasurero();
    glPopMatrix();

    glutSwapBuffers();
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(ancho,largo);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);




    glutMainLoop();

    return EXIT_SUCCESS;
}
