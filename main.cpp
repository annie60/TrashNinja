/*
 * Ninja Trash
 * Proyecto Graficas Computacional
 * Semestre Ago-Dic 2015
 * Ana Arellano Palacios
 * Luis Alberto Reyna
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
#include "imageloader.h"
using namespace std;
GLMmodel model[6];
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };//Puntual
int ancho=500;
int largo=500;
int xNinja=0;
int yNinja=5;
bool perdio = false;
string fullPath = __FILE__;
//Vida inicial del jugador
int vida=3;
//50 segundos en el cronometro
int tiempo=60;
//Saber en que punto del menu esta
// 1 -home, 2- seleccion de nivel, 3- opciones, 4- en juego
int navegacion=1;
int velocidad=8; //variable para calcular que tan rapido se mueve
//Indica si esta en juego o no (Pausa y continuar)
bool jugando=false;
//Niveles abiertos por el jugador
int nivel = 1;
int nivelActual=1;
//Variable para animacion de letreros
int angulo=-1;
int anguloObj=5;
int anguloObj1=5;
int anguloObj2=5;
int anguloObj3=5;
int anguloObj4=5;
//Contador de puntos actuales
int puntuacionActual=0;
//cantidad de objetos por segundo que aparecen
int objXmin= 20;
//lista de objetos
int arrObj[100][4];
//texturas
 GLuint texName[36];
int cantObj=0;
int velocidadObj=5;
//Mensaje por perdida
string porquePerdio= "";
//Mensaje informativos en caso de no ganar
string mensajes []={"Las manzanas le ayudan a tu cuerpo","El cigarro causa problemas al respirar",
"Tu cuerpo necesita agua"};
//Puntuacion para cada nivel
int puntosMeta [] ={100,250,500};
void loadTexture(Image* image,int k)
{

    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data

}

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
    glOrtho(-width/2, width/2, -height/2, height/2, 1, 150);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    gluLookAt(0, 0, 15, 0, 0, 0, 0, 1,0);
}
//Metodos para dibujar objetos con
// volumen para que parezca 3era dimension
static void manzana(){

    glmDraw(&model[5],GLM_COLOR|GLM_FLAT);

}
static void cigarro(){
    glmDraw(&model[3],GLM_COLOR|GLM_FLAT);
}
static void cerveza(){

    glmDraw(&model[1],GLM_COLOR|GLM_FLAT);

}
static void dona(){
    glmDraw(&model[2],GLM_COLOR|GLM_FLAT);
}
static void agua(){
    glmDraw(&model[4],GLM_COLOR|GLM_FLAT);
}
static void estrellas(int total){
    int xRaster=0;
    for(int x=0;x<total;x++){

        glPushMatrix();
        glTranslatef(xRaster,0,0);
        glmDraw(&model[0],GLM_COLOR|GLM_FLAT);
        glPopMatrix();
        xRaster+=2;
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

    //glColor3f(0, 0,0);

    for(int j=0;j < palabra.length();j++){
       char valor=palabra.at(j);
       glRasterPos2i(xRaster,yRaster);
       glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,valor);
       xRaster+=13;
    }
}
static void timerObj(int i){
if(jugando==true && tiempo > 0 && vida > 0){
    for(int x=0;x<=cantObj; x++){
        arrObj[x][2]=arrObj[x][2]-velocidadObj;
    }
    anguloObj=anguloObj1=anguloObj2=anguloObj3=anguloObj4+=10;
    glutTimerFunc(80,timerObj,1);
    glutPostRedisplay();
    }
}
static void timer(int i){

    //if(navegacion!=4){
    angulo +=10;
    glutTimerFunc(80,timer,1);
    //}
    glutPostRedisplay();

}
static void timerCronometro(int i){
    if(jugando==true && tiempo > 0 && vida > 0){
        if(tiempo%(60/objXmin)==0){
            int type=rand() % 5;
            int xpoint=rand() % (ancho-20) - ((ancho/2)-15);
            int ypoint=rand() % (30) +(largo/2);
            arrObj[cantObj][0]= type  ;
            arrObj[cantObj][1]= xpoint  ;
            arrObj[cantObj][2]= ypoint  ;
            arrObj[cantObj][3]= 0 ;
            cantObj++;
        }
        tiempo-=1;

        glutTimerFunc(1000,timerCronometro,1);
    }else if(jugando==true && (tiempo ==0 || vida ==0)){
        jugando=false;
        //Revisa si se alcanzo la meta del nivel
        if(puntuacionActual < puntosMeta[nivelActual-1] && vida > 0){
        porquePerdio="No dominaste el nivel";
        perdio=true;
        }else if(vida==0){
        porquePerdio="Se acabaron las vidas";
        perdio=true;
        }else if(puntuacionActual >= puntosMeta[nivelActual-1]){
            perdio=false;
            if(nivel<3){
            nivel++;
            }
        }
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
    glPushMatrix();
    glTranslatef(0,0,-1);
    glScalef(40,40,2);
    glColor3f(0.85,0.1,0);
    glutSolidCube(1);
    glPopMatrix();


    ///Techo
    glPushMatrix();
    glScalef(45,45,3);
    glPushMatrix();
    glTranslatef(-0.47,-0.37,1);
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

    glPopMatrix();
    glTranslatef(0,0,0.5);
    letreroChico("H");


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
    glTranslatef(0,5,-5);
    glScalef(5.1,0.7,5.5);
    glutSolidSphere(3.1416,50,50);
    glPopMatrix();
    ///Ojo izquierdo
     glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(5.2,-2,5.3);
    glScalef(0.4,0.3,2);
    glutSolidSphere(3.1416,100,100);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0.9,-1.8,4.7);
    glScalef(3.3,1.5,2);
    glutSolidSphere(3.1416,100,100);
    glPopMatrix();

    ///Ojo derecho
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-5.3,-2,5.3);
    glScalef(0.4,0.3,2);
    glutSolidSphere(3.1416,100,100);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(-0.9,-1.8,4.7);
    glScalef(3.3,1.5,2);
    glutSolidSphere(3.1416,100,100);
    glPopMatrix();
    ///Base
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(0,0,-5);
    glScalef(4,5.5,5);
    glutSolidSphere(3.1416,100,50);
    glPopMatrix();
    ///Frente
    glPushMatrix();
    glTranslatef(0,1,-5);
    glScalef(4.5,5.1,5);
    glutSolidSphere(3.1416,100,50);
    glPopMatrix();
    ///Boca
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-0.2,-10.5,-5);
    glScalef(4.9,2,5.5);
    glutSolidSphere(3.1416,100,50);
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
    glutSolidSphere(3.14,100,50);
    glPopMatrix();
    ///Derecho
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(5.5,2.5,0);
    glRotatef(20,0,-1,1.5);
    glScalef(0.5,1,1);
    glutSolidSphere(3.14,100,50);
    glPopMatrix();
    ///Base
    glColor3f(0.5,0.5,0.5);
    glPushMatrix();
    glTranslatef(0,0,-2);
    glScalef(9,8,3);
    glutSolidCube(1);
    glPopMatrix();
    glColor3f(0.8,0.8,0.8);
    ///Arriba
    glPushMatrix();
    glTranslatef(0,4.5,-1);
    glScalef(1.5,1,3);
    glutWireSphere(3.14,10,10);
     glColor3f(0,0,0);
    glutWireSphere(3.14,5,10);
    glPopMatrix();
    glColor3f(0.5,0.5,0.5);
    ///Abajo
    glPushMatrix();
    glTranslatef(0,-5,0);
    glScalef(1.5,1,3);
    glutSolidSphere(3.14,100,50);
    glPopMatrix();
    ///Decorado
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(0,0,10);
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
    glScalef(18.9,12.9,5);
    glutSolidSphere(3.14,80,50);
    glPopMatrix();
    glColor3f(0.5,0.5,0.5);
    glPushMatrix();
    glScalef(18.5,12.5,5);
    glutSolidSphere(3.14,80,50);
    glPopMatrix();
    glTranslatef(-50,0,0);
}
static void dibujaFondoMensajes(int ancho){
    ///Fondo
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
    glPushMatrix();
    glTranslatef(0,0,-100);
    glColor3f(0.271,0.063,0);
   // glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, texName[0]);
    glBegin(GL_QUADS);
    //glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-(ancho/2),(largo/2));
    //glTexCoord2f(3.0f, 0.0f);
    glVertex2f((ancho/2),(largo/2));
    //glTexCoord2f(3.0f, 5.0f);
    glVertex2f((ancho/2),-(largo/2));
    //glTexCoord2f(0.0f, 5.0f);
    glVertex2f(-(ancho/2),-(largo/2));
    glEnd();
    glPopMatrix();

    ///Barra naranja
    glPushMatrix();
    glTranslatef(0,0,-90);
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
    glRotatef(0.5,0,0,1);
    glTranslatef((-(ancho/4))+ancho/8,(largo/4)+15,2);
    glScalef(300,700,1);
    dibujaBotonMadera(1);
    glPopMatrix();
    glPushMatrix();
    glRotatef(0.5,0,0,1);
    glTranslatef((-(ancho/4))+ancho/6,(largo/3),2.5);
    glScalef(1,10,1);
    glColor3f(0, 0,0);
    letrero("J-Jugar");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-((ancho/2)-50),(largo/4)+40,-45);
    glRotatef(angulo,0,1,0);
    glScalef(0.8,1,1);
    glTranslatef(-35,0,0);
    dibujaTapaBasurero();
    glTranslatef(0,0,20);
    letreroChico("I-Info");
    glPopMatrix();
    ///Parte de abajo
    ///Ninja
    glPushMatrix();
    glTranslatef(0,0,-45);
    glRotatef(15,0,1,0);
    glScalef(3,3,2);
    dibujaCaraNinja(1,1,0);
    glPopMatrix();
    ///Manzana
    glPushMatrix();
    glTranslatef(-(ancho/4),0,-45);
    glRotatef(-70,1,1,0);
    glScalef(20,20,10);
    manzana();
    glPopMatrix();
    ///Cerveza
    glPushMatrix();
    glTranslatef((ancho/4),0,-45);
    glRotatef(-80,1,1,0);
    glScalef(40,55,20);
    cerveza();
    glPopMatrix();
    ///Dona
    glPushMatrix();
    glTranslatef((ancho/4),100,-45);
    glRotatef(95,1,1,0);
    glScalef(20,20,15);
    dona();
    glPopMatrix();
    ///Agua
    glPushMatrix();
    glTranslatef(-(ancho/4),-50,-45);
    glRotatef(95,1,1,0);
    glScalef(30,30,20);
    agua();
    glPopMatrix();
    ///Titulo
     glPushMatrix();
     glColor3f(1,1,1);
    glTranslatef(-(ancho/2.9),-(largo/4),-40);
    glRotatef(-30,1,1,0);
    glScalef(2.5,1,2);
    letrero("TRASH");
    glTranslatef(45,0,-50);
    letrero("NINJA");
    glPopMatrix();

}
static void pantallaInformacion(){
    ///Fondo
    glPushMatrix();
    glTranslatef(0,0,-95);
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
    glTranslatef(-((ancho/2)-50),(largo/3),-45);
    glRotatef(angulo,0,1,0);
    glScalef(1,1,2);
    glTranslatef(-5,0,0);
    dibujaBotonHome(1);
    glPopMatrix();
    ///Instrucciones
    glPushMatrix();
    glTranslatef(-(ancho/4),50,1);
    glPushMatrix();
    glTranslatef(-(ancho/11),-(largo/4),-45);
    glScalef(ancho/1.5,largo/3,2);
    glRotatef(5,0,angulo,1);
    dibujaFondoMensajes(1);
    glPopMatrix();

    letreroChico("Usa las flechas del teclado");
    glTranslatef(0,-25,0);
    letreroChico("para mover al ninja");
    glTranslatef(0,-25,0);
    letreroChico("y atrapar lo que no");
    glTranslatef(0,-25,0);
    letreroChico("es bueno para tu cuerpo.");
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
    glTranslatef(ancho/3,0,-10);
    glScalef(2,2,1);
    dibujaCaraNinja(0,0,1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(ancho/3,-60,-11);
    glScalef(6,5,2);
    dibujaBasurero();
    glPopMatrix();
    ///Cigarro
    glPushMatrix();
    glTranslatef(-(ancho/3.5),-60,-11);
    glRotatef(30,1,1,0);
    glScalef(50,30,20);
    cigarro();
    glPopMatrix();
    ///Cerveza
    glPushMatrix();
    glTranslatef(-(ancho/4.5),-60,-11);
    glRotatef(80,1,1,0);
    glScalef(40,45,20);
    cerveza();
    glPopMatrix();
    ///Dona
    glPushMatrix();
    glTranslatef(-(ancho/7.5),-60,-11);
    glRotatef(80,1,1,0);
    glScalef(20,20,15);
    dona();
    glPopMatrix();

}
static void pantallaSeleccion(){
    ///Fondo
    glPushMatrix();
    glTranslatef(0,0,-90);
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
    glTranslatef((-(ancho/2))+50,largo/2.5,1);
    glScalef(1,1,2);
    dibujaBotonHome(1);
    glPopMatrix();
    ///Instrucciones
    glPushMatrix();
    glTranslatef((-(ancho/2))+150,largo/4,1);
    glScalef(1,1,2);
    glColor3f(0,0,0);
    letrero("Escoge el nivel");
    glPopMatrix();

    ///Niveles
    ///nivel 1
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-(ancho/4),0,-45);
    glRotatef(angulo,0,1,0);
    glScalef(2,2,2);
    dibujaCaraNinja(0,0,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-((ancho/3.5)-15),-50,-40);
    //glRotatef(angulo,0,1,0);
    glScalef(0.5,0.5,1);
    glTranslatef(-55,0,0);
    letreroChico("A-Aprendiz");
    glPopMatrix();
    ///Nivel 2
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(0,0,-45);

    if(nivel > 1){ //Lo muestra deshabilitado si no ha abierto nivel
    glScalef(2,2,1);
    glRotatef(angulo,0,1,0);
    dibujaCaraNinja(0,1,0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-15,-50,-40);
    //glRotatef(angulo,0,1,0);
    glScalef(0.5,0.5,0);
    glTranslatef(-15,0,0);
    letreroChico("N-Novato");
    glPopMatrix();
    }else{
    glScalef(2,2,1);
    dibujaCaraNinja(0,0,0);
    glPopMatrix();
    }


    ///Nivel 3
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(ancho/4,0,-45);
    if(nivel > 2){
    glScalef(2,2,1);
    glRotatef(angulo,0,1,0);
    dibujaCaraNinja(1,0,0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef((ancho/4),-50,-40);
    //glRotatef(angulo,0,1,0);
    glScalef(0.5,0.5,0);
    glTranslatef(-55,0,0);
    letreroChico("M -Maestro");
    glPopMatrix();
    }else{
    glScalef(2,2,1);
    dibujaCaraNinja(0,0,0);
    glPopMatrix();
    }



}
static void juego(){
     ///Fondo
    glPushMatrix();
    glTranslatef(0,0,-100);
    glColor3f(0.96,0.56,0.2);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);

    glVertex2f(-(ancho/2),(largo/2));
    glTexCoord2f(0.0, 1.0f);
    glVertex2f((ancho/2),(largo/2));
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f((ancho/2),-(largo/2));
    glTexCoord2f(1.0, 0.0);
    glVertex2f(-(ancho/2),-(largo/2));
    glEnd();
    glPopMatrix();

    ///Regreso
    glPushMatrix();
    glTranslatef((ancho/3)+40,largo/2.4,0);
    glScalef(1,1,2);
    dibujaBotonHome(1);
    glPopMatrix();
    /*
    ///Piso
    glPushMatrix();
    glTranslatef(0,-300,-95);
    glScalef(ancho-10,(largo/4),1);
    glColor3f(0.96,0.76,0.25);
    glBegin(GL_QUADS);
    glVertex2f(-1,-1);
    glVertex2f(1,-1);
    glVertex2f(1,1);
    glVertex2f(-1,1);
    glEnd();
    glPopMatrix();*/

    ///Cronometro
    glPushMatrix();
    glColor3f(0.462745,0.466667,0.450980);
    glTranslatef((ancho/3)-40,(largo/2.4),1);
    string cronometro=formato(tiempo);
    letrero(cronometro);
    glPopMatrix();
    ///TODO: Agregar letreros con los shortcuts de Pausa, reiniciar y continuar

    ///Puntaje
    glPushMatrix();
    glTranslatef(-((ancho/2)-20),(largo/2.55),0);
    glScalef(1,1,2);
    letreroChico("Puntos:"+static_cast<ostringstream*>( &(ostringstream() << puntuacionActual) )->str());
    glPopMatrix();

    ///Vidas
    glPushMatrix();
    glTranslatef(-((ancho/2)-15),(largo/2.3),0);
    glScalef(15,15,2);
    estrellas(vida);
    glPopMatrix();

    ///Ninja
    glPushMatrix();
    glTranslatef(xNinja,0,0);
    glRotatef(5,1,1,0);

    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(ancho/3,-100,-10);
    glScalef(2,2,1);
    dibujaCaraNinja(0,0,1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(ancho/3,-165,1);
    glScalef(6,5.5,2);
    dibujaBasurero();
    glPopMatrix();

    glPopMatrix();

    if(perdio==false && jugando==true ){

        for(int num=0; num<cantObj ; num++){

            if(arrObj[num][3]==1)
                continue;
            else{
                if(arrObj[num][1]<xNinja+200 && arrObj[num][1]>xNinja+130 && arrObj[num][2]<-60 && arrObj[num][2]>-200){
                    int type = arrObj[num][0];
                    if (type==0 || type==4){
                        if(vida == 0){
                            perdio=true;
                            jugando=false;

                        }else{
                            vida--;
                        }
                    }else{
                        puntuacionActual+=10;

                    }
                    arrObj[num][3]=1;
                }
            }
            ///Objetos
            glPushMatrix();



           // cout<<num << ": " <<arrObj[num][1]<< "  "<<arrObj[num][2]<< endl;
            glTranslatef(arrObj[num][1],arrObj[num][2],-45);
            int type = arrObj[num][0];
            if(type==0){
                glPushMatrix();
                glRotatef(anguloObj,1,1,1);
                glScalef(20,20,20);
                manzana();

                glPopMatrix();
                cigarro();

            }else if(type==1){
                glRotatef(anguloObj1,1,1,1);
                glScalef(50,30,20);
                cigarro();

            }else if(type==2){
                glRotatef(anguloObj2,1,1,0);
                glScalef(40,55,20);
                cerveza();

            }else if(type==3){
                glRotatef(anguloObj3,1,1,0);
                glScalef(20,20,15);
                dona();

            }else if(type==4){
                glRotatef(anguloObj4,1,1,0);
                glScalef(30,30,30);
                agua();

            }

            glPopMatrix();

        }
        //cout<< "-----------------------"<< endl;
    }else if(jugando==false && perdio==false && tiempo==0){
    ///Mensaje gano
    glPushMatrix();
    glTranslatef(-(ancho/4),50,1);

    glPushMatrix();
    glTranslatef(-(ancho/11),-(largo/4),-45);
    glScalef(ancho/1.3,largo/3,2);
    glRotatef(5,0,1,1);
    dibujaFondoMensajes(1);
    glPopMatrix();

    glTranslatef(-50,-30,0);
    glColor3f(1,1,1);
    letrero("¡Felicidades completaste");
    glTranslatef(5,-20,0);
    letrero("el nivel!");
    glTranslatef(10,-50,0);
    letreroChico(mensajes[nivelActual-1]);
    glTranslatef(45,-50,0);

    glPushMatrix();
    glTranslatef(-10,-5,-5);
    glScalef(265,255,2);
    dibujaBotonMadera(1);
    glPopMatrix();

    glColor3f(1,1,1);
    letrero("S-Siguiente");

    glPopMatrix();
    }else if(perdio==true){
    ///Mensaje perdio

    glPushMatrix();
    glTranslatef(-(ancho/4),50,1);

    glPushMatrix();
    glTranslatef(-(ancho/11),-(largo/4),-45);
    glScalef(ancho/1.3,largo/3,2);
    glRotatef(5,0,1,1);
    dibujaFondoMensajes(1);
    glPopMatrix();
    glTranslatef(-20,0,0);
    glColor3f(1,1,1);
    letrero(porquePerdio);

    glTranslatef(-25,-50,0);
    letrero("¡Lo siento! Vuelve a intentar");
    glTranslatef(0,-50,0);
    letreroChico(mensajes[nivelActual-1]);
    glTranslatef(45,-50,0);
    glPushMatrix();

    glTranslatef(-10,-5,-5);
    glScalef(265,255,2);
    dibujaBotonMadera(1);
    glPopMatrix();
    glColor3f(1,1,1);
    letrero("R-Reiniciar");
    glPopMatrix();
    }

}
static void reiniciar(){
    tiempo=60;
    vida=3;
 puntuacionActual=0;
 jugando=true;
 perdio=false;
 cantObj=0;
 glutPostRedisplay();
}
static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
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


void init(){
    int i=0;
    getParentPath();
    glEnable(GL_NORMALIZE);
    string ruta = fullPath+ "imagenes/Estrella.obj";
    model[0]= *glmReadOBJ(ruta.c_str());
    glmUnitize(&model[0]);
    glmVertexNormals(&model[0],90.0,GL_TRUE);
    ruta = fullPath+ "imagenes/beer.obj";
    model[1]= *glmReadOBJ(ruta.c_str());
    glmUnitize(&model[1]);
    glmVertexNormals(&model[1],90.0,GL_TRUE);
    ruta = fullPath+ "imagenes/Donut.obj";
    model[2]= *glmReadOBJ(ruta.c_str());
    glmUnitize(&model[2]);
    glmVertexNormals(&model[2],90.0,GL_TRUE);
    ruta = fullPath+ "imagenes/cigarette.obj";
    model[3]= *glmReadOBJ(ruta.c_str());
    glmUnitize(&model[3]);
    glmVertexNormals(&model[3],90.0,GL_TRUE);
    ruta = fullPath+ "imagenes/water.obj";
    model[4]= *glmReadOBJ(ruta.c_str());
    glmUnitize(&model[4]);
    glmVertexNormals(&model[4],90.0,GL_TRUE);
    ruta = fullPath+ "imagenes/apple.obj";
    model[5]= *glmReadOBJ(ruta.c_str());
    glmUnitize(&model[5]);
    glmVertexNormals(&model[5],90.0,GL_TRUE);
    ///Luces
    GLfloat light_ambient[] = { 0.9, 0.9, 0.9, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    // glEnable(GL_COLOR_MATERIAL);
    glGenTextures(36, texName); //Make room for our texture
    Image* image;
    ruta=fullPath + "imagenes/background.bmp";

    image = loadBMP(ruta.c_str());
    loadTexture(image,i);
    i++;

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
  case 'c':///Continuar
  case 'C':
    if(navegacion==4){
    jugando=true;
    glutTimerFunc(1000,timerCronometro,1);
     glutTimerFunc(500,timerObj,1);
    }
    //glutPostRedisplay();
    break;
  case 'h':
  case 'H':
    //if(jugando==true){
    tiempo=60;
    vida=3;
    puntuacionActual=0;
    perdio=false;
    cantObj=0;
    jugando=false;
    //}
    //glutTimerFunc(100,timer,1);
    navegacion=1;
    break;
  case 'i':
  case 'I':
    if(navegacion==1){
    jugando=false;
    navegacion=3;
    }
    break;
  case 'a': ///aprendiz
  case 'A':
      if(navegacion ==2){
        nivelActual=1;
      navegacion=4;
      velocidadObj=5;
      objXmin=20;
      jugando=true;
      glutTimerFunc(1000,timerCronometro,1);
      glutTimerFunc(500,timerObj,1);
      }
    break;
  case 'n':///novato
  case 'N':
      if(nivel > 1 && navegacion==2){
        nivelActual=2;
        navegacion=4;
        velocidadObj=10;
        objXmin=35;
        jugando=true;
        glutTimerFunc(1000,timerCronometro,1);
      glutTimerFunc(500,timerObj,1);
      }
    break;
  case 'm':///maestro
  case 'M':
      if(nivel > 2 && navegacion==2){
        nivelActual=3;
        navegacion=4;
        jugando=true;
        velocidadObj=15;
        objXmin=35;
        glutTimerFunc(1000,timerCronometro,1);
      glutTimerFunc(500,timerObj,1);
      }
    break;
  case 'R':
  case 'r':
    if(navegacion == 4 && perdio==true){
    reiniciar();
    glutTimerFunc(1000,timerCronometro,1);
    glutTimerFunc(500,timerObj,1);
    }
    break;
  case 'S':
  case 's':
    if(navegacion == 4 && jugando==false && perdio==false){
        reiniciar();
        navegacion=2;
    }
    glutPostRedisplay();
    break;
  default:
    return;
  }
  glutPostRedisplay();
}
static void mover(int key,int x,int y){
if(jugando==true){
 switch(key){
 /*case GLUT_KEY_DOWN:

    if(yNinja<-(largo/4))
        break;
    yNinja+= velocidad*-1;
     break;
 case GLUT_KEY_UP:
    if(yNinja>0)
        break;
    yNinja+= velocidad*1;
    break;*/
 case GLUT_KEY_LEFT:
    if(xNinja<-(ancho/1.35)|| jugando==false)
        break;
    xNinja+= velocidad*-1;
    //yNinja*=(-1);
    break;
 case GLUT_KEY_RIGHT:
    if(xNinja>(ancho/12.5) || jugando==false)
        break;
    xNinja+= velocidad*1;
    //yNinja*=(-1);
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

    glutTimerFunc(100,timer,1);
    glutKeyboardFunc(key);
    glutKeyboardUpFunc(key);

    glutMainLoop();

    return EXIT_SUCCESS;
}
#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
{

}

Image::~Image()
{
    delete[] pixels;
}

namespace
{
//Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes)
    {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }

//Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes)
    {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }

//Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input)
    {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }

//Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input)
    {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }

//Just like auto_ptr, but for arrays
    template<class T>
    class auto_array
    {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) :
                array(array_), isReleased(false)
        {
        }

        auto_array(const auto_array<T> &aarray)
        {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        ~auto_array()
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
        }

        T* get() const
        {
            return array;
        }

        T &operator*() const
        {
            return *array;
        }

        void operator=(const auto_array<T> &aarray)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        T* operator->() const
        {
            return array;
        }

        T* release()
        {
            isReleased = true;
            return array;
        }

        void reset(T* array_ = NULL)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = array_;
        }

        T* operator+(int i)
        {
            return array + i;
        }

        T &operator[](int i)
        {
            return array[i];
        }
    };
}

Image* loadBMP(const char* filename)
{
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);

    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    switch (headerSize)
    {
    case 40:
        //V3
        width = readInt(input);
        height = readInt(input);
        input.ignore(2);
        assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
        assert(readShort(input) == 0 || !"Image is compressed");
        break;
    case 12:
        //OS/2 V1
        width = readShort(input);
        height = readShort(input);
        input.ignore(2);
        assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
        break;
    case 64:
        //OS/2 V2
        assert(!"Can't load OS/2 V2 bitmaps");
        break;
    case 108:
        //Windows V4
        assert(!"Can't load Windows V4 bitmaps");
        break;
    case 124:
        //Windows V5
        assert(!"Can't load Windows V5 bitmaps");
        break;
    default:
        assert(!"Unknown bitmap format");
    }

    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);

    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                pixels2[3 * (width * y + x) + c] =
                    pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    return new Image(pixels2.release(), width, height);
}
