// Prénoms, noms et matricule des membres de l'équipe:
// - Mietka BLÉMUR 1539033
// - Khalil MEDAWAR 1391332

#include <iostream>
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <GL/glut.h>
#include "float3.h"
#include "loadtex.h"
using namespace std;


//+++++++++++++++++
//Defines et macros
#define DEG2RAD(a) ((a) * M_PI / 180.0)
#define CLIP(a,min,max) (a < min) ? min : ((a > max) ? max : a)
GLUquadric *sphereSoleil;
GLUquadric *sphereTerre;
GLUquadric *sphereLune;
GLUquadric *sphereJupiter;
GLUquadric *sphereEuropa;
GLUquadric *sphereCallisto;


//++++++++++++++++
//Variables globales utiles
int g_feneID;                   // le ID de la fenêtre graphique GLUT
const int g_largeur = 800;      // la largeur initiale de la fenêtre GLUT
const int g_hauteur = 800;      // la hauteur initiale de la fenêtre GLUT
GLsizei currentW, currentH;     // Largeur et hauteur courantes de la fenêtre graphique (viewport)

#define PI 3.1416
#define RAYON_TERRE 4			// Rayon Terre-Soleil
#define RAYON_JUPITER 7			// Rayon Jupiter-Soleil
#define RAYON_LUNE 1			// Rayon Terre-Lune
#define RAYON_EUROPA 1			// Rayon Jupiter-Europa
#define RAYON_CALLISTO 1.5		// Rayon Jupiter-Callipso

#define EPAISSEUR_TRAIT 3		// Épaisseur du trait en pixel

/*EXIGENCE 5*/

/* Rotation ( Autour d'elle meme ) */
#define ROTATION_SOLEIL 1
#define ROTATION_TERRE  4
#define ROTATION_JUPITER  4.5
#define ROTATION_LUNE 5
#define ROTATION_EUROPA  4.6
#define ROTATION_CALLISTO 4.8
/* Revolution ( Autour de soleil ou planete )*/
#define REVOLUTION_TERRE 2.3
#define REVOLUTION_JUPITER 1.4
#define REVOLUTION_LUNE 2.5
#define REVOLUTION_EUROPA 2.1
#define REVOLUTION_CALLISTO 2.9

//+++++++++++++++

float phi = M_PI/2, theta = M_PI/2;
GLdouble rayon = 26;
int dt=0;

GLuint textureLune, textureTerre, textureSoleil, textureJupiter, textureEuropa, textureCallisto;


int rotate()
{
	dt=(clock()-dt)/40;
	return dt;
}

void dessinerCercle(GLfloat rayon)
{
	glBegin(GL_LINE_STRIP);

	for (int angle = 0; angle <= 360; angle++)
		glVertex2f(rayon*sin(angle*PI/180),rayon*cos(angle*PI/180));

	glEnd();
	return;
}

void dessinerScene()
{
   //modifs ici...
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective( 60.0, (GLdouble) g_largeur / (GLdouble) g_hauteur, 0.1, 300.0 );

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   gluLookAt( rayon*cos(phi)*sin(theta), rayon*sin(theta)*sin(phi), rayon*cos(theta),
              0, 0, 0,
              0, 0, 1 );
   /*DÉBUT E6 : L’orbite des planètes est dessiné sous forme de disque.*/

   //Conserve la couleur courante
   glPushAttrib( GL_CURRENT_BIT );
   //Épaisseur du trait
   glLineWidth(EPAISSEUR_TRAIT);
   //Dessiner la planète Terre avec un rayon bleu
   glColor3f(1,0,0);
   dessinerCercle(RAYON_TERRE);
   //Dessiner la planète Jupiter avec un rayon rouge
   glColor3f(0,0,1);
   dessinerCercle(RAYON_JUPITER);
   //Redistribue la valeur de couleur précédente
   glPopAttrib();
   glPushMatrix();
   
   /*FIN E6 : L’orbite des planètes est dessiné sous forme de disque.*/
   
   glEnable(GL_TEXTURE_2D);
   
   glPushMatrix();
   glRotatef(REVOLUTION_TERRE*rotate(),0,0,1);
   glBindTexture(GL_TEXTURE_2D, textureTerre);
   glTranslatef(-RAYON_TERRE,0,0);
   glRotatef(ROTATION_TERRE*rotate(),0,0,1);
   gluSphere(sphereTerre,0.3,16,32);
  
   glRotatef(REVOLUTION_LUNE*rotate(),0,0,1);
   glBindTexture(GL_TEXTURE_2D, textureLune);
   glTranslatef(-RAYON_LUNE,0,0);
   glRotatef(ROTATION_LUNE*rotate(),0,0,1);
   gluSphere(sphereLune,0.1,32,32);
   glPopMatrix();


   
   glPushMatrix();
   glRotatef(REVOLUTION_JUPITER*rotate(),0,0,1);
   glBindTexture(GL_TEXTURE_2D, textureJupiter);
   glTranslatef(RAYON_JUPITER,0,0);
   glRotatef(ROTATION_JUPITER*rotate(),0,0,1);
   gluSphere(sphereJupiter,0.7,32,32);
   
   //Satellite Europa
   glPushMatrix();
   glRotatef(REVOLUTION_EUROPA*rotate(),0,0,1);
   glBindTexture(GL_TEXTURE_2D, textureEuropa);
   glTranslatef(RAYON_EUROPA,0,0);
   glRotatef(ROTATION_EUROPA*rotate(),0,0,1);
   gluSphere(sphereEuropa,0.1,32,32);
   glPopMatrix();

   /*Satellite Callisto*/
   glPushMatrix();
   glRotatef(REVOLUTION_CALLISTO*rotate(),0,0,1);
   glBindTexture(GL_TEXTURE_2D, textureCallisto);
   glTranslatef(RAYON_CALLISTO,0,0);
   glRotatef(ROTATION_CALLISTO*rotate(),0,0,1);
   gluSphere(sphereCallisto,0.1,32,32);
   glPopMatrix();
   
   glPopMatrix();

   
   //DÉBUT E7: Le soleil est partiellement transparent
   glPushMatrix();
   glEnable(GL_BLEND);
   glDepthMask(GL_FALSE);

   glBlendFunc(GL_ONE, GL_ONE);
   glRotatef(ROTATION_SOLEIL*rotate(),0,0,1);
   glBindTexture(GL_TEXTURE_2D, textureSoleil);
   gluSphere(sphereSoleil,2,16,32);   

   glDepthMask(GL_TRUE);
   glDisable(GL_BLEND);
   glPopMatrix();
   //FIN E7: Le soleil est partiellement transparent 
  
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
   glutSwapBuffers();
}

void chargerTextures()
{
   LoadGLTextures( "textures/terre.bmp", textureTerre );
   LoadGLTextures( "textures/soleil.bmp", textureSoleil );
   LoadGLTextures( "textures/lune.bmp" ,textureLune );
   LoadGLTextures( "textures/jupiter.bmp", textureJupiter );
   LoadGLTextures( "textures/europa.bmp", textureEuropa );
   LoadGLTextures( "textures/callisto.bmp", textureCallisto );
}

void initGL()
{
   // donner la couleur de fond
   glClearColor( 0.0, 0.0, 0.0, 1.0 );

   // activer les etats openGL
   glEnable(GL_NORMALIZE);
   glEnable(GL_DEPTH_TEST);

   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

   sphereSoleil = gluNewQuadric();
   gluQuadricNormals( sphereSoleil, GLU_SMOOTH );
   gluQuadricDrawStyle( sphereSoleil, GLU_FILL );
   gluQuadricTexture( sphereSoleil, GL_TRUE );

   sphereLune = gluNewQuadric();
   gluQuadricNormals( sphereLune, GLU_SMOOTH );
   gluQuadricDrawStyle( sphereLune, GLU_FILL );
   gluQuadricTexture( sphereLune, GL_TRUE );

   sphereTerre = gluNewQuadric();
   gluQuadricNormals( sphereTerre, GLU_SMOOTH );
   gluQuadricDrawStyle( sphereTerre, GLU_FILL );
   gluQuadricTexture( sphereTerre, GL_TRUE );

   sphereJupiter = gluNewQuadric();
   gluQuadricNormals( sphereJupiter, GLU_SMOOTH );
   gluQuadricDrawStyle( sphereJupiter, GLU_FILL );
   gluQuadricTexture( sphereJupiter, GL_TRUE );

   sphereEuropa = gluNewQuadric();
   gluQuadricNormals( sphereEuropa, GLU_SMOOTH );
   gluQuadricDrawStyle( sphereEuropa, GLU_FILL );
   gluQuadricTexture( sphereEuropa, GL_TRUE );

   sphereCallisto = gluNewQuadric();
   gluQuadricNormals( sphereCallisto, GLU_SMOOTH );
   gluQuadricDrawStyle( sphereCallisto, GLU_FILL );
   gluQuadricTexture( sphereCallisto, GL_TRUE );

   chargerTextures();
}

void idle()
{
   glutPostRedisplay();
}

void keyboard(unsigned char touche, int x, int y)
{
   switch ( touche )
   {
   case 27: // escape
      glutDestroyWindow(g_feneID);
      exit(0);
      break;
   }
}

void keyboardSpecial(int touche, int x, int y)
{
}

void resize(GLsizei w, GLsizei h)
{
   currentW = w;
   currentH = h;
   glViewport( 0, 0, w, h );
   glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y)
{
}

void mouseMove(int x, int y)
{
   static int lastx=0, lasty=0;
   static bool init=true;
   if ( init )
   {
      lastx = x; lasty = y; init = false;
   }
   phi += (x-lastx) / 20.0;
   theta += (y-lasty) / 15.0;
   lastx = x;
   lasty = y;
}

int main(int argc,char *argv[])
{
   // initialisation de GLUT
   glutInit(&argc, argv);
   // parametrage de l'affichage
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   // taille de la fenetre
   glutInitWindowSize(g_largeur, g_hauteur);
   // creation de la fenetre
   g_feneID = glutCreateWindow("INF2705");
   // referencement de la fonction de rappel pour l'affichage
   glutDisplayFunc(dessinerScene);
   // referencement de la fonction de rappel pour l'attente
   glutIdleFunc(idle);
   // referencement de la fonction de gestion des touches
   glutKeyboardFunc(keyboard);
   // referencement de la fonction de gestion spéciale des touches extended
   glutSpecialFunc(keyboardSpecial);
   // referencement de la fonction de rappel pour le redimensionnement
   glutReshapeFunc(resize);
   // référencement de la fonction de rappel pour le mouvement de la souris
   glutMotionFunc(mouseMove);
   // référencement de la fonction de rappel pour le clic de la souris
   glutMouseFunc(mouseClick);

   //glewInit();

   initGL();

   // boucle principale de gestion des evenements
   glutMainLoop();

   // le programme n'arrivera jamais jusqu'ici
   return EXIT_SUCCESS;
}