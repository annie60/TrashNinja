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
#include<sstream>
#include<stdio.h>
#include <iostream>
#include <math.h>
#include "glm.h"

using namespace std;
GLMmodel model[2];
int ancho=500;
int largo=500;
int xNinja=0;
int yNinja=0;
string fullPath = __FILE__;
//Vida inicial del jugador
int vida=3;
//50 segundos en el cronometro
int tiempo=50;
//Saber en que punto del menu esta
// 1 -home, 2- seleccion de nivel, 3- opciones, 4- en juego
int navegacion=1;
int velocidad=4; //variable para calcular que tan rapido se mueve
bool jugando=false;
//Niveles abiertos por el jugador
int nivel = 1;
//Variable para animacion de letreros
int angulo=-1;
int puntuacionActual=0;
//Mensaje informativos en caso de no ganar
string mensajes []={"Las manzanas son una comida que le ayuda a tu cuerpo","El cigarro puede causarte problemas al respirar"
"Las bebidas con alcohol lastiman a tu estomago","Tu cuerpo necesita agua para poder funcionar"};
//Puntuacion para cada nivel
int puntosMeta [] ={100,250,500};
//Valores de los objetos a recoger
int valoraciones[]={5,10,15,25};
void getParentPath(){
    for (int i = fullPath.length()-1; i>=0 && fullPath[i] != '\\'; i--) {
        fullPath.erase(i,1);
    }
}
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    ancho=width;
    largo=height;
    glClearColor(1,1,1,0);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2, -8, 150);
    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    gluLookAt(0, 0, 15, 0, 0, 0, 0, 1,0);
}
//TODO: Metodos para dibujar objetos con
// volumen para que parezca 3era dimension
static void manzana(){
glPushMatrix();
    glTranslatef(0,0,5);
    glmDraw(&model[0],GLM_COLOR|GLM_FLAT);
    glPopMatrix();
}
static void cigarro(){
}
static void cerveza(){
}
static void papas(){
}
static void agua(){
}
static void estrellas(int total){
    for(int x=0;x<total;x++){

        //TODO:Dibujar estructura de estrella
    }
}
static string formato(int i){
    int temporalMin= 0;
    int temporalSeg;

    temporalSeg=(int)i;

    string minuto=static_cast<ostringstream*>( &(ostringstream() << temporalMin) )->str()+":";
    string segundos;
    if(temporalSeg>=10){
        segundos=static_cast<ostringstream*>( &(ostringstream() << temporalSeg) )->str();
    }else{
        segundos="0"+static_cast<ostringstream*>( &(ostringstream() << temporalSeg) )->str();
    }

    return minuto+segundos;

}

static void letreroChico(string palabra){

    int yRaster=0;
    int xRaster =0;

    glColor3f(0, 0,0);

    for(int j=0;j < palabra.length();j++){
       char valor=palabra.at(j);
       glRasterPos2i(xRaster,yRaster);
       glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,valor);
       xRaster+=10;
    }
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
static void timer(int i){
    if(jugando==true){
            tiempo-=1;
        glutTimerFunc(1000,timer,1);
    }


    glutPostRedisplay();

}
static void dibujaBotonMadera(int ancho){
    /*glLineWidth(1);
    glColor3f(0.9,0.05,0);

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(0.002*ancho,0*ancho);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(0.002*ancho,0.1*ancho);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(0.7*ancho,0.09*ancho);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(0.65*ancho,0*ancho);
    glEnd();
    glPopMatrix();*/
    glLineWidth(1);
    glColor3f(0.9,0.05,0);

    glPushMatrix();

    glBegin(GL_QUADS);
    glTranslatef(0,0,-1);
    glVertex2f(0.002*ancho,0*ancho);
    glVertex2f(0.002*ancho,0.1*ancho);
    glVertex2f(0.7*ancho,0.09*ancho);
    glVertex2f(0.65*ancho,0*ancho);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,2);
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
    glPopMatrix();

}
static void dibujaBotonHome(int ancho){
    ///Fondo
    glColor3f(0.85,0.1,0);
    glBegin(GL_QUADS);
    glVertex2f(0*ancho,0*ancho);
    glVertex2f(0*ancho,1*ancho);
    glVertex2f(1*ancho,1*ancho);
    glVertex2f(1*ancho,0*ancho);
    glEnd();
    glPushMatrix();
    glTranslatef(0,0,5);
    ///Techo
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(0.1*(ancho),0.5*(ancho));
    glVertex2f(0.5*(ancho),0.8*(ancho));
    glVertex2f(0.5*(ancho),0.8*(ancho));
    glVertex2f(0.9*(ancho),0.5*(ancho));
    glEnd();
    ///Piso
    glPushMatrix();
    glRotatef(10,0,0,1);
    glBegin(GL_LINES);
    glVertex2f(0.2*ancho,0.1*ancho);
    glVertex2f(0.8*ancho,0.1*ancho);
    glEnd();
    glPopMatrix();
    ///Pared izquierda
    glBegin(GL_LINES);
    glVertex2f(0.65*ancho,0.2*ancho);
    glVertex2f(0.65*ancho,0.5*ancho);
    glEnd();
    ///Pared derecha
    glBegin(GL_LINES);
    glVertex2f(0.35*ancho,0.15*ancho);
    glVertex2f(0.35*ancho,0.5*ancho);
    glEnd();
    glPushMatrix();
    glTranslatef(0.42,0.3,0);
    letreroChico("H");
    glPopMatrix();
    glPopMatrix();
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

    ///Cinta
    glPushMatrix();
    glColor3f(red,green,blue);
    glTranslatef(0,5,3);
    glScalef(28.5,2.5,1);
    glutSolidCube(1);
    glPopMatrix();
    ///Ojo izquierdo
     glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(5.5,-2.1,4.5);
    glScalef(0.4,0.3,1);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(5.5,-2.1,5.5);
    glScalef(2.3,1.5,2);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();

    ///ojo derecho
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-5.5,-2.1,4.5);
    glScalef(0.4,0.3,1);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(-5.5,-2.1,5.5);
    glScalef(2.3,1.5,2);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();

    ///Base
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(0,0,0);
    glScalef(4,5.5,1);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();
    ///Frente
    glPushMatrix();

    glScalef(4.5,5.1,1);
    glTranslatef(0,1,0);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();
    ///Boca
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-0.2,-10.5,0);
    glScalef(4.9,2,1);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();

    ///Linea plana
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0,-5.3,2);
    glScalef(3.8,0.5,1);
    glutSolidSphere(3.1416,100,2);
    glPopMatrix();


}
static void dibujaBasurero(){
    ///Brazos
    ///Izquierdo
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(-5.5,2.5,0);
    glRotatef(20,0,-1,-1.5);
    glScalef(0.5,1,1);
    glutSolidSphere(3.14,100,2);
    glPopMatrix();
    ///Derecho
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(5.5,2.5,0);
    glRotatef(20,0,-1,1.5);
    glScalef(0.5,1,1);
    glutSolidSphere(3.14,100,2);
    glPopMatrix();
    ///Base
    glColor3f(0.5,0.5,0.5);
    glPushMatrix();
    glScalef(9,8,1);
    glutSolidCube(1);
    glPopMatrix();
    glColor3f(0.8,0.8,0.8);
    ///Arriba
    glPushMatrix();
    glTranslatef(0,4.5,0);
    glScalef(1.5,1,1);
    glutSolidSphere(3.14,100,2);
    glPopMatrix();
    glColor3f(0.5,0.5,0.5);
    ///Abajo
    glPushMatrix();
    glTranslatef(0,-5,0);
    glScalef(1.5,1,1);
    glutSolidSphere(3.14,100,2);
    glPopMatrix();
    ///Decorado
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(0,0,2);
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
static void dibujaTapaBasurero(){
    glTranslatef(30,10,0);
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(0,0,-1);
    glScalef(18.9,12.9,1);
    glutSolidSphere(3.14,80,2);
    glPopMatrix();
    glColor3f(0.5,0.5,0.5);
    glPushMatrix();
    glScalef(18.5,12.5,1);
    glutSolidSphere(3.14,80,2);
    glPopMatrix();
    glTranslatef(-50,0,0);
}
static void dibujaFondoMensajes(int ancho){
    //Fondo
    glColor3f(0.85,0.1,0);
    glBegin(GL_QUADS);
    glVertex2f(0*ancho,0*ancho);
    glVertex2f(0*ancho,1*ancho);
    glVertex2f(1*ancho,1*ancho);
    glVertex2f(1*ancho,0*ancho);
    glEnd();
}
static void pantallaInicial(){
    ///Fondo
    glColor3f(0.271,0.063,0);
    glBegin(GL_QUADS);
    glVertex2f(-(ancho/2),(largo/2));
    glVertex2f((ancho/2),(largo/2));
    glVertex2f((ancho/2),-(largo/2));
    glVertex2f(-(ancho/2),-(largo/2));
    glEnd();

    ///Barra blanca
    glPushMatrix();
    glTranslatef(0,0,1);
    glColor3f(0.96,0.56,0.2);
    glBegin(GL_QUADS);
    glVertex2f(-(ancho/2),(largo/2));
    glVertex2f((ancho/2),(largo/2));
    glVertex2f((ancho/2),(largo/4));
    glVertex2f(-(ancho/2),(largo/4));
    glEnd();
    glPopMatrix();
    ///Separador
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(0,0,2);
    glRotatef(1,0,0,1.5);
    glLineWidth(1);
    glTranslatef(0,0,1);
    for(int i=0;i<3;i++){
    glBegin(GL_LINES);
    glVertex2f(-(ancho/2),((largo/4)-(1.5*i)));
    glVertex2f((ancho/2),((largo/4)-(1.5*i)));
    glEnd();
    }
    glPopMatrix();
    ///Parte de arriba
    glPushMatrix();
    glRotatef(0.5*angulo,0,0,1);
    glTranslatef((-(ancho/4))+ancho/8,(largo/4)+15,2);
    glScalef(300,700,1);
    dibujaBotonMadera(1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(0.5*angulo,0,0,1);
    glTranslatef((-(ancho/4))+ancho/6,(largo/3),2.5);
    glScalef(2.5,10,1);
    letrero("J-Jugar");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-((ancho/2)-50),(largo/4)+40,2);
    dibujaTapaBasurero();
    glColor3f(0,0,0);
    glTranslatef(25,0,3);
    letreroChico("I-Info");
    glPopMatrix();


}
static void pantallaInformacion(){
    ///Fondo
    glPushMatrix();
    glTranslatef(0,0,-20);
    glColor3f(0.96,0.56,0.2);
    glBegin(GL_QUADS);
    glVertex2f(-(ancho/2),(largo/2));
    glVertex2f((ancho/2),(largo/2));
    glVertex2f((ancho/2),-(largo/2));
    glVertex2f(-(ancho/2),-(largo/2));
    glEnd();
    glPopMatrix();
    ///Regreso
    glPushMatrix();
    glTranslatef((-(ancho/2))+50,largo/3,1);
    glScalef(50,50,1);
    dibujaBotonHome(1);
    glPopMatrix();
    ///Instrucciones
    glPushMatrix();
    glTranslatef(-(ancho/4),50,1);
    glPushMatrix();
    glTranslatef(-(ancho/11),-(largo/4),-15);
    glScalef(ancho/1.5,largo/3,2);
    glRotatef(5*angulo,0,angulo,1);
    dibujaFondoMensajes(1);
    glPopMatrix();

    letreroChico("Usa las flechas del teclado");
    glTranslatef(0,-50,0);
    letreroChico("para mover al ninja");
    glTranslatef(0,-50,0);
    letreroChico("y atrapar lo que no sirve.");
    glTranslatef(0,-100,0);
    letreroChico("Hecho por:");
    glTranslatef(0,-20,0);
    letreroChico("Ana Arellano");
    glTranslatef(0,-20,0);
    letreroChico("Luis Reyna");
    glPopMatrix();

    ///Ninja

    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(ancho/3,0,1);
    glScalef(2,2,0);
    dibujaCaraNinja(0,0,1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(ancho/3,-60,1);
    glScalef(6,5,1);
    dibujaBasurero();
    glPopMatrix();

}
static void pantallaSeleccion(){
    ///Fondo
    glColor3f(0.96,0.56,0.2);
    glBegin(GL_QUADS);
    glVertex2f(-(ancho/2),(largo/2));
    glVertex2f((ancho/2),(largo/2));
    glVertex2f((ancho/2),-(largo/2));
    glVertex2f(-(ancho/2),-(largo/2));
    glEnd();
    ///Regreso
    glPushMatrix();
    glTranslatef((-(ancho/2))+50,largo/3,1);
    glScalef(50,50,1);
    dibujaBotonHome(1);
    glPopMatrix();
    ///Niveles
    ///nivel 1
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-(ancho/4),0,1);
    glScalef(2,2,0);
    //glRotatef(10,1,1,0);
    dibujaCaraNinja(0,0,1);
    glTranslatef(-25,-30,0);
    glScalef(0.5,0.5,0);
    letreroChico("A-Aprendiz");
    glPopMatrix();
    ///Nivel 2
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(0,0,1);
    glScalef(2,2,0);
    if(nivel > 1){ //Lo muestra deshabilitado si no ha abierto nivel
    dibujaCaraNinja(0,1,0);
    glTranslatef(-25,-30,0);
    glScalef(0.5,0.5,0);
    letreroChico("N-Novato");
    }else{
    dibujaCaraNinja(0,0,0);
    }
    glPopMatrix();

    ///Nivel 3
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(ancho/4,0,1);
    glScalef(2,2,0);
    if(nivel > 2){
    dibujaCaraNinja(1,0,0);
    glTranslatef(-25,-30,0);
    glScalef(0.5,0.5,0);
    letreroChico("M-Maestro");
    }else{
    dibujaCaraNinja(0,0,0);
    }
    glPopMatrix();


}
static void juego(){
    ///Fondo
    glPushMatrix();
    glTranslatef(0,0,-100);
    glColor3f(0.96,0.56,0.2);
    glBegin(GL_QUADS);
    glVertex2f(-(ancho/2),(largo/2));
    glVertex2f((ancho/2),(largo/2));
    glVertex2f((ancho/2),-(largo/2));
    glVertex2f(-(ancho/2),-(largo/2));
    glEnd();
    glPopMatrix();
    ///Regreso
    glPushMatrix();
    glTranslatef((-(ancho/2))+50,largo/3,1);
    glScalef(50,50,1);
    dibujaBotonHome(1);
    glPopMatrix();
    ///Piso
    glPushMatrix();
    glTranslatef(0,-200,-95);
    glScalef(ancho-10,(largo/4),1);
    glColor3f(0.96,0.76,0.25);
    glBegin(GL_QUADS);
    glVertex2f(-1,-1);
    glVertex2f(1,-1);
    glVertex2f(1,1);
    glVertex2f(-1,1);
    glEnd();
    glPopMatrix();

    ///Cronometro
    glPushMatrix();
    glTranslatef((ancho/3),(largo/2.5),0);
    string cronometro=formato(tiempo);
    letrero(cronometro);

    glPopMatrix();
    //TODO: Agregar letreros con los shortcuts de Pausa, reiniciar y continuar
    //TODO: Agregar el despliegue de las estrellas
    //TODO: Implementar despliegue de mensajes en caso de perdida
    ///Ninja
    glPushMatrix();
    //glRotatef(5,1,1,0);
    glTranslatef(xNinja,yNinja,1);

    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(ancho/3,0,1);
    glScalef(2,2,0);
    dibujaCaraNinja(0,0,1);
    glPopMatrix();
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(ancho/3,-60,1);
    glScalef(6,5,1);
    dibujaBasurero();
    glPopMatrix();
    glPopMatrix();
    manzana();

}
static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch(navegacion){
        case 1:
            pantallaInicial();
            break;
        case 2:
            pantallaSeleccion();
            break;
        case 3:
            pantallaInformacion();
            break;
        case 4://
            juego();
            break;
        default:
            return;
    }

    glutSwapBuffers();
}

static void reiniciar(){
tiempo=50;
vida=3;
 puntuacionActual=0;
 jugando=false;
 glutPostRedisplay();
}
void init(){
    getParentPath();
    glEnable(GL_NORMALIZE);
    string ruta = fullPath + "imagenes/" + "apple.obj";
    model[0]= *glmReadOBJ(ruta.c_str());
    glmUnitize(&model[0]);
    glmVertexNormals(&model[0],90.0,GL_TRUE);
    glEnable(GL_DEPTH_TEST);

}
static void key(unsigned char k, int x, int y){
  switch (k) {
  case 'E':  /* Escape */
  case 'e':
    exit(0);
    break;
  case 'p'://Pausar
  case 'P':
    if(navegacion==4){
    jugando=false;
    glutPostRedisplay();
    }
    break;
  case 'j':
  case'J':
    if(navegacion==1){
    navegacion=2;

    }

    break;
  case 'c'://Continuar
  case 'C':
    if(navegacion==4){
    jugando=true;
    glutPostRedisplay();
    }
    break;
  case 'h':
  case 'H':
    if(jugando==true){
    jugando=false;
    reiniciar();
    }
    navegacion=1;
    break;
  case 'i':
  case 'I':
    if(navegacion==1){
    jugando=false;
    navegacion=3;
    }
    break;
  case 'a': //aprendiz
  case 'A':
      if(navegacion ==2){
      navegacion=4;
      jugando=true;
      glutTimerFunc(1000,timer,1);
      }
    break;
  case 'n'://novato
  case 'N':
      if(nivel > 1 && navegacion==2){
        navegacion=4;
        jugando=true;
        glutTimerFunc(1000,timer,1);
      }
    break;
  case 'm'://maestro
  case 'M':
      if(nivel > 2 && navegacion==2){
            navegacion=4;
        jugando=true;
        glutTimerFunc(1000,timer,1);
      }
    break;
  case 'R':
  case 'r':
    reiniciar(); //todo:falta por implementar
    break;

  default:
    return;
  }
  glutPostRedisplay();
}
static void mover(int key,int x,int y){
if(jugando==true){
 switch(key){
 case GLUT_KEY_DOWN:

    if(yNinja<-(largo/4))
        break;
    yNinja+= velocidad*-1;
     break;
 case GLUT_KEY_UP:
    if(yNinja>0)
        break;
    yNinja+= velocidad*1;
    break;
 case GLUT_KEY_LEFT:
    if(xNinja<-(ancho/1.35))
        break;
    xNinja+= velocidad*-1;
    break;
 case GLUT_KEY_RIGHT:
    if(xNinja>(ancho/12.5))
        break;
    xNinja+= velocidad*1;
    break;
 default:
    return;
 }
}
 glutPostRedisplay();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(ancho,largo);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Trash Ninja");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    glutSpecialFunc(mover);
    glutSpecialUpFunc(mover);


    glutKeyboardFunc(key);
    glutKeyboardUpFunc(key);

    glutMainLoop();

    return EXIT_SUCCESS;
}
