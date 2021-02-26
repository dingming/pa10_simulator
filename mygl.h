#ifndef MYGL_H
#define MYGL_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#ifdef MACOS
#include <glut.h>
#else
#include <GL/glut.h>
#endif

void SetNormal(double *p1,double *p2,double*p3,double *normal);

void myglCylinder(double r0, double r1, double l, int st);

void myglTrapezium(double r0, double r1, double l, double h, int st);

void myglOrigin(double ox, double oy, double oz, double axisl, double r);

#endif
