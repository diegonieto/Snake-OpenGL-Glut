/*
 Snake game

Copyright (C) 2014  Diego Nieto Muñoz

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Datos de la serpiente //
int activos = 10;     // numero de cuadrados activos
int puntuacion = 0;   // calificacion del jugador actual
int anchoani = 1;
class anilla {        // Tipo anilla de la serpiente
   public:
   int x;
   int y;
};
// Direccion
int dir = GLUT_KEY_LEFT;
anilla comida;
anilla serpiente[1000];
int vel = 1;

// Pantalla
int Ancho = 80;
int Alto = 80;

void DibujaEscena()
{
   // Pone el color de fondo a azul
   glClearColor(0.0, 0.0, 1.0, 1.0);
   // Borra la ventana
   glClear(GL_COLOR_BUFFER_BIT);
   // Pone el color de pintar a rojo
   glColor3f(1.0, 0.0, 0.0);
   // Dibuja un rectángulo sólido
   for (int i=0; i<activos; i++) {
       glRectf (serpiente[i].x,serpiente[i].y,serpiente[i].x+anchoani,serpiente[i].y+anchoani);
   }
   // Dibujar comida
   glColor3f(1.0, 1.0, 0.0);
   glRectf (comida.x,comida.y,comida.x+1,comida.y+1);
   glFlush();
   glutSwapBuffers();
}




void AumentarAnillas() {
   activos+=10;
}

void CambiarDir(int key,int x, int y) {
    switch (key) {
       case GLUT_KEY_LEFT: {
          if (serpiente[0].x - 1 != serpiente[1].x) {
             dir = GLUT_KEY_LEFT;
          }
          break;
       }
       case GLUT_KEY_RIGHT: {
          if (serpiente[0].x + 1 != serpiente[1].x) {
             dir = GLUT_KEY_RIGHT;
          }
          break;
       }
       case GLUT_KEY_UP: {
          if (serpiente[0].y + 1 != serpiente[1].y) {
             dir = GLUT_KEY_UP;
          }
          break;
       }
       case GLUT_KEY_DOWN: {
          if (serpiente[0].y - 1 != serpiente[1].y) {
             dir = GLUT_KEY_DOWN;
          }
          break;
       }
    };
}



void generacomida() {
   bool comprobado = false;
   while (!comprobado) {
      srand (time(NULL));
      comida.x = rand() % Ancho;
      comida.y = rand() % Alto;
      comprobado = true;
      for (int i=0; i<activos && comprobado; i++) {
         if(comida.x == serpiente[i].x && comida.y == serpiente[i].y) {
             comprobado = false;
         }
      }
   }
}


void Retrasar() {
   for (int i=0; i<10000000; i++);
}

void MueveAnillas()
{
   Retrasar();
   for (int i=activos-1; i>0; i--) {
      serpiente[i]=serpiente[i-1];
   }
   glutSpecialFunc(CambiarDir);
   switch (dir) {
       case GLUT_KEY_LEFT: {
          serpiente[0].x-=vel;
          break;
       }
       case GLUT_KEY_RIGHT: {
          serpiente[0].x+=vel;
          break;
       }
       case GLUT_KEY_UP: {
          serpiente[0].y+=vel;
          break;
       }
       case GLUT_KEY_DOWN: {
          serpiente[0].y-=vel;
          break;
       }
    };
    // Detectar salidas de pantalla
    if (serpiente[0].x+1 > Ancho) serpiente[0].x = 0;
    if (serpiente[0].x < 0) serpiente[0].x = Ancho;
    if (serpiente[0].y+1 > Alto) serpiente[0].y = 0;
    if (serpiente[0].y < 0) serpiente[0].y = Alto;
    // Detectar si ha comido o se ha tocado
    for (int i=0; i<activos; i++) {
         if(comida.x == serpiente[i].x && comida.y == serpiente[i].y) {
             i = activos;
             AumentarAnillas();
             generacomida();
         }
         if (serpiente[0].x == serpiente[i+1].x && serpiente[0].y == serpiente[i+1].y) {
             serpiente[0].x = 10;
             serpiente[0].y = 10;
             activos = 10;
             break;
         }
    }
    glutPostRedisplay();
}



void EscalaVentana(GLsizei w, GLsizei h)
{
   // Evita una división por cero
   if (h == 0) h = 1;
   // Ajusta la vista a las dimensiones de la ventana
   glViewport(0, 0, w, h);
   // Reinicia el sistema de coordenadas
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   // Establece el volumen de trabajo
   glOrtho(0.0f, 80.f, 0.0f, 80.f, -1.0, 1.0);
   glFlush();
}


int main(int argc, char **argv)
{
   // Posición inicial de la serpiente
   serpiente[0].x=50;
   serpiente[0].y=50;
   for (int i=1; i<activos; i++) {
      serpiente[i].x = serpiente[0].x + i+1;
      serpiente[i].y = serpiente[0].y;
   }
   generacomida();

   glutInit(&argc, argv);
   // Funciones GLUT para inicializar la ventana
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowSize (600,600);
   glutCreateWindow ("Snake - Diego Nieto Muñoz");
   glutGetMenu();
   // Indicamos la función para el evento Paint
   glutDisplayFunc (DibujaEscena);
   // Indicamos la función para el evento Resize
   glutReshapeFunc (EscalaVentana);
   // Indica la función a llamar cuando se escale la ventana
   glutIdleFunc(MueveAnillas);
   // Lanzamos el bucle indefinido de eventos
   glutMainLoop();

   return 0;
}
