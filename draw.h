#ifndef DRAW_H
#define DRAW_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "mygl.h"

void drawObjectArea(double l, double w, double h, double d);
void drawFloor(double width, int n);
void draw_pa10(GLenum mode);

#endif
