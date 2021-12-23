

#include "Render.h"

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>

inline double getErmit3(double p1, double p4, double r1, double r4, double t)
{
  return p1 * (2 * t * t * t - 3 * t * t + 1) + p4 * (-2 * t * t * t + 3 * t * t) + r1 * (t * t * t - 2 * t * t + t) + r4 * (t * t * t - t * t);
}

inline double getBezie(double p0, double p1, double p2, double p3, double t)
{
  return (1 - t) * (1 - t) * (1 - t) * p0 + 3 * t * (1 - t) * (1 - t) * p1 + 3 * t * t * (1 - t) * p2 + t * t * t * p3;
}

double t_max = 0;
void Render(double delta_time)
{    
  t_max += delta_time / 5; 
  if (t_max > 1) t_max = 0;

  double P0[] = { 0,0,0 };
  double P1[] = { 5,5,5 }; 
  double P2[] = { -5,10,5 };
  double P3[] = { 10,10,0 };
  double R1[] = { 0, 10, 10 };
  double R2[] = { 0, 5, 5 };
  double P[3];


  //glBegin(GL_TRIANGLES);
  //glColor3d(0.5, 0.5, 0.5);
  //glVertex3d(0, 0, 1);
  //glVertex3d(0.1, 0.1, 0);
  //glVertex3d(-0.1, 0.1, 0);

  //glVertex3d(0, 0, 1);
  //glVertex3d(-0.1, 0.1, 0);
  //glVertex3d(-0.1, -0.1, 0);

  //glVertex3d(0, 0, 1);
  //glVertex3d(-0.1, -0.1, 0);
  //glVertex3d(0.1, -0.1, 0);

  //glVertex3d(0, 0, 1);
  //glVertex3d(0.1, -0.1, 0);
  //glVertex3d(0.1, 0.1, 0);
  //glEnd();
  glLineWidth(3);
  glPointSize(10);

  glBegin(GL_LINE_STRIP);
  glColor3d(0.5, 0, 0);
  glVertex3d(P0[0], P0[1], P0[2]);
  glVertex3d(P1[0], P1[1], P1[2]);
  glVertex3d(P2[0], P2[1], P2[2]);
  glVertex3d(P3[0], P3[1], P3[2]);
  glEnd();

  glBegin(GL_LINES);
  glColor3d(1, 0, 0);
  for (double t = 0; t <= t_max; t += 0.01)
  {
    P[0] = getBezie(P0[0], P1[0], P2[0], P3[0], t);
    P[1] = getBezie(P0[1], P1[1], P2[1], P3[1], t);
    P[2] = getBezie(P0[2], P1[2], P2[2], P3[2], t);
    glVertex3dv(P);
  }
   glEnd();

   glBegin(GL_LINES);
   glColor3d(0, 0.5, 0);
   glVertex3d(P0[0], P0[1], P0[2]);
   glVertex3d(-P2[0], P2[1], -P2[2]);
   glVertex3d(R1[0], R1[1], R1[2]);
   glVertex3d(-R2[0], R2[1], -R2[2]);
   glEnd();

   glBegin(GL_POINTS);
   glVertex3d(R1[0], R1[1], R1[2]);
   glEnd();

   glBegin(GL_LINES);
   glColor3d(0, 1, 0);
   for (double t = 0; t <= t_max; t += 0.01)
   {
     P[0] = getErmit3(P0[0], -P2[0], R1[0], -R2[0], t);
     P[1] = getErmit3(P0[1], P2[1], R1[1], R2[1], t);
     P[2] = getErmit3(P0[2], -P2[2], R1[2], -R2[2], t);
     glVertex3dv(P);
   }
   glEnd(); 

   glBegin(GL_LINES);
   glColor3d(0, 0, 0.5);
   glVertex3d(-R2[0], -R2[1], -R2[2]);
   glVertex3d(-P2[0], -P2[1], -P2[2]);
   glVertex3d(-R1[0], -R1[1], -R1[2]);
   glVertex3d(-P3[0], -P3[1], -P3[2]);
   glEnd();

   glBegin(GL_POINTS);
   glVertex3d(-R1[0], -R1[1], -R1[2]);
   glEnd();

   glBegin(GL_LINES);
   glColor3d(0, 0, 1);
   for (double t = 0; t <= t_max; t += 0.01)
   {
     P[0] = getErmit3(-R2[0], -P2[0], -R1[0], -P3[0], t);
     P[1] = getErmit3(-R2[1], -P2[1], -R1[1], -P3[1], t);
     P[2] = getErmit3(-R2[2], -P2[2], -R1[2], -P3[2], t);
     glVertex3dv(P);
   }
   glEnd();
   glLineWidth(1);
}   
