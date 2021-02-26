#include "draw.h"
#include "color.h"
#include "parameter.h"

extern double JAngle[7];
extern int njoint;

// NEW ONE
/* #define PA10_BODY_COLOR (lblue3) */
/* #define PA10_COVER_COLOR (white) */

// OLD ONE
//#define PA10_BODY_COLOR (white)
#define PA10_BODY_COLOR (grey8)
#define PA10_COVER_COLOR (lightgreen)

void drawObjectArea(double l, double w, double h, double d)
{
	int i,j,k;
	double cx, cy, cz;
	glPushMatrix();
	{
		glDisable (GL_DEPTH_TEST);
		glDisable (GL_LIGHTING);
		for(i=-1;i<=1;i+=2){
			for(j=-1;j<=1;j+=2){
				for(k=-1;k<=1;k+=2){
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
					glBegin(GL_LINES);
					cx = i*(l+d)/2; cy=j*(w+d)/2; cz = (1+k)*(h/2)+k*(d/2);
/* 					printf("%f, %f, %f\n", cx, cy, cz); */
					glVertex3f(cx, cy, cz);
					glVertex3f(cx-i*d, cy, cz);
					glVertex3f(cx, cy, cz);
					glVertex3f(cx, cy-j*d, cz);
					glVertex3f(cx, cy, cz);
					glVertex3f(cx, cy, cz-k*d);
					glEnd();
				}
			}
		}
		glEnable (GL_LIGHTING);
		glEnable (GL_DEPTH_TEST);
/* 		glEnable(GL_LIGHT1); */
	}
	glPopMatrix();
}

void JointOrigin(int n)
{
	double AxisL = 200;
	double AxisR = 10;
//	double AxisOffset = 200;

/* 	glDisable(GL_LIGHT1); */
		glPushMatrix();
		{
			glDisable (GL_DEPTH_TEST);
			glDisable (GL_LIGHTING);
			myglOrigin(0.0, 0.0, 0.0, AxisL, AxisR);
			glEnable (GL_LIGHTING);
			glEnable (GL_DEPTH_TEST);
/* 			glEnable(GL_LIGHT1); */
		}
		glPopMatrix();
}


void drawBase(void)
{
	double rr=2.0;
	double hr=0.1;
	glPushMatrix();
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
		glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
		myglCylinder(rr*pa10_base_r, rr*pa10_base_r, hr*pa10_base_h, ST);
		myglCylinder(pa10_base_r, pa10_base_r, pa10_base_h, ST);
	}
	glPopMatrix();
}

void drawJ1(void)
{	
	glPushMatrix();
	{
		if(njoint==0){
			drawObjectArea(2*pa10_base_r,
						   2*pa10_base_r,
						   pa10_j1_h+pa10_j1_cover_l+2*pa10_j1_cover_r1,
						   area_d);
/* 			JointOrigin(0); */
		}
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
		glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
		myglCylinder(pa10_base_r, pa10_base_r, pa10_j1_h, ST);

		glPushMatrix();
		{
			glRotatef(90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0,
						 pa10_j1_cover_l/2 + pa10_j1_cover_r0,
						 pa10_base_r);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_COVER_COLOR);
			glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_COVER_COLOR);
			myglTrapezium (pa10_j1_cover_r0,
						   pa10_j1_cover_r1,
						   pa10_j1_cover_l,
						   pa10_j1_cover_t, ST);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0,
						 -(pa10_j1_cover_l/2 + pa10_j1_cover_r0),
						 pa10_base_r);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_COVER_COLOR);
			glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_COVER_COLOR);
			myglTrapezium (pa10_j1_cover_r0,
						   pa10_j1_cover_r1,
						   pa10_j1_cover_l,
						   pa10_j1_cover_t, ST);
		}
		glPopMatrix();
	}
	glPopMatrix();

}

void drawJ2(void)
{	
	double hr=0.65;
	double rr=0.9;
	glPushMatrix();
	{
		if(njoint==1){
			drawObjectArea(2*pa10_j2_r0,
						   2*(pa10_base_r+pa10_j1_cover_t),
						   pa10_j2_r0+pa10_j2_h,
						   area_d);
/* 		JointOrigin(1); */
		}
		glPushMatrix();
		{
			glRotatef(90.0, 1, 0, 0);
			glTranslatef(0.0, 0.0, -pa10_base_r);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
			glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
			myglCylinder(pa10_j2_r0, pa10_j2_r0, 2*pa10_base_r, ST);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
			glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
			myglCylinder(pa10_j2_r1, rr*pa10_j2_r1, hr*pa10_j2_h, ST);
			glTranslatef(0.0, 0.0, hr*pa10_j2_h);
			myglCylinder(rr*pa10_j2_r1, pa10_j2_r1, (1-hr)*pa10_j2_h, ST);
		}
		glPopMatrix();
	}
	glPopMatrix();

}


void drawJ3(void)
{	
	glPushMatrix();
	{
		if(njoint==2){
			drawObjectArea(2*(pa10_j3_r+pa10_j3_cover_t),
						   2*(pa10_j3_cover_r0+pa10_j3_cover_t),
						   2*pa10_j3_cover_r0+pa10_j3_cover_l,
						   area_d);
/* 		JointOrigin(); */
		}

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
		glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
		myglCylinder(pa10_j3_r, pa10_j3_r, pa10_j3_h, ST);

		glPushMatrix();
		{
			glRotatef(90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0,
						 pa10_j3_cover_l/2 + pa10_j3_cover_r0,
						 pa10_j3_r);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_COVER_COLOR);
			glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_COVER_COLOR);
			myglTrapezium (pa10_j3_cover_r0,
						   pa10_j3_cover_r1,
						   pa10_j3_cover_l,
						   pa10_j3_cover_t, ST);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0,
						 -(pa10_j3_cover_l/2 + pa10_j3_cover_r0),
						 pa10_j3_r);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_COVER_COLOR);
			glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_COVER_COLOR);
			myglTrapezium (pa10_j3_cover_r0,
						   pa10_j3_cover_r1,
						   pa10_j3_cover_l,
						   pa10_j3_cover_t, ST);
		}
		glPopMatrix();
	}
	glPopMatrix();

}

void drawJ4(void)
{	
	double hr=0.65;
	double rr=0.7;
	glPushMatrix();
	{
		if(njoint==3){
			drawObjectArea(2*pa10_j4_r0,
						   2*(pa10_j3_r+pa10_j3_cover_t),
						   pa10_j4_r1+pa10_j4_h,
						   area_d);
/* 		JointOrigin(); */
		}

		glPushMatrix();
		{
			glRotatef(90.0, 1, 0, 0);
			glTranslatef(0.0, 0.0, -pa10_j3_r);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
			glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
			myglCylinder(pa10_j4_r0, pa10_j4_r0, 2*pa10_j3_r, ST);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
			glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
			myglCylinder(pa10_j4_r1, rr*pa10_j4_r1, hr*pa10_j4_h, ST);
			glTranslatef(0.0, 0.0, hr*pa10_j4_h);
			myglCylinder(rr*pa10_j4_r1, pa10_j4_r1, (1-hr)*pa10_j4_h, ST);
		}
		glPopMatrix();
	}
	glPopMatrix();

}

void drawJ5(void)
{	
	glPushMatrix();
	{
		if(njoint==4){
			drawObjectArea(2*(pa10_j5_cover_r0+pa10_j5_cover_t),
						   2*(pa10_j5_r+pa10_j5_cover_t),
						   2*pa10_j5_cover_r0+pa10_j5_cover_l,
						   area_d);
/* 		JointOrigin(); */
		}

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
		glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
		myglCylinder(pa10_j5_r, pa10_j5_r, pa10_j5_h, ST);

		glPushMatrix();
		{
			glRotatef(90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0,
						 pa10_j5_cover_l/2 + pa10_j5_cover_r0,
						 pa10_j5_r);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_COVER_COLOR);
			glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_COVER_COLOR);
			myglTrapezium (pa10_j5_cover_r0,
						   pa10_j5_cover_r1,
						   pa10_j5_cover_l,
						   pa10_j5_cover_t, ST);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0,
						 -(pa10_j5_cover_l/2 + pa10_j5_cover_r0),
						 pa10_j5_r);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_COVER_COLOR);
			glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_COVER_COLOR);
			myglTrapezium (pa10_j5_cover_r0,
						   pa10_j5_cover_r1,
						   pa10_j5_cover_l,
						   pa10_j5_cover_t, ST);
		}
		glPopMatrix();
	}
	glPopMatrix();

}

void drawJ6(void)
{	
	double rr=0.8;
	double hr=0.1;
	glPushMatrix();
	{
		if(njoint==5){
/* 		JointOrigin(); */
		}

		glPushMatrix();
		{
			glRotatef(90.0, 1, 0, 0);
			glTranslatef(0.0, 0.0, -pa10_j5_r);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
			glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
			myglCylinder(pa10_j6_r0, pa10_j6_r0, 2*pa10_j5_r, ST);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0.0, 0.0, -pa10_j6_l);
			glTranslatef(0.0, 0.0, pa10_j6_h);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
			glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
			myglCylinder(rr*pa10_j6_r1, pa10_j6_r1, hr*pa10_j6_l, ST);
			glTranslatef(0.0, 0.0, hr*pa10_j6_l);
			myglCylinder(pa10_j6_r1, pa10_j6_r1, (1-hr)*pa10_j6_l, ST);
			if(njoint==5){
				drawObjectArea(2*pa10_j6_r0,
							   2*pa10_j6_r1,
							   pa10_j6_l,
							   area_d);
			}
		}
		glPopMatrix();
	}
	glPopMatrix();

}

void drawJ7(void)
{	
	double hr = 0.6;
	glPushMatrix();
	{
		if(njoint==6){
			drawObjectArea(2*pa10_j7_r1,
						   2*pa10_j7_r1,
						   pa10_j7_h,
						   area_d);
/* 		JointOrigin(); */
		}

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
		glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, PA10_BODY_COLOR);
		myglCylinder(pa10_j7_r, pa10_j7_r, hr*pa10_j7_h, ST);
		glTranslatef(0.0, 0.0, hr*pa10_j7_h);
		myglCylinder(pa10_j7_r1, pa10_j7_r1, (1-hr)*pa10_j7_h, ST);
	}
	glPopMatrix();

}


void drawFloor(double width, int n)
{
	int i;
	double slan = width/n;
  
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, white);

	glPushMatrix();
	{
		glColor3fv(white);
		for (i=-n;i<n+1;i++)
		{ 
			glBegin(GL_LINES);
			glVertex3f(slan*i, width, 0.0);
			glVertex3f(slan*i, -width, 0.0);
			glEnd();
		}
		for (i=-n;i<n+1;i++)
		{
			glBegin(GL_LINES);
			glVertex3f(-width, -i*slan, 0.0);
			glVertex3f(width, -i*slan, 0.0);
			glEnd();
		}
	}
	glPopMatrix();
}


void draw_pa10(GLenum mode)
{
	glPushMatrix();
	{
		myglOrigin(0,0,0,100, 10);
		// Base
		drawBase();
		// Joint 1
		glTranslatef( 0.0, 0.0, pa10_base_h);
		glRotatef(JAngle[0], 0, 0, 1);
		if (mode == GL_SELECT){
			glLoadName(1);
		}
		drawJ1();
		// Joint 2
		glTranslatef( 0.0, 0.0, pa10_j1_cover_l+pa10_j1_cover_r0);
		glRotatef(JAngle[1], 0, 1, 0);
		if (mode == GL_SELECT){
			glLoadName(2);
		}
		drawJ2();
		// Joint 3
		glTranslatef( 0.0, 0.0, pa10_j2_h);
		glRotatef(JAngle[2], 0, 0, 1);
		if (mode == GL_SELECT){
			glLoadName(3);
		}
		drawJ3();
		// Joint 4
		glTranslatef( 0.0, 0.0, pa10_j3_cover_l + pa10_j3_cover_r0);
		glRotatef(JAngle[3], 0, 1, 0);
		if (mode == GL_SELECT){
			glLoadName(4);
		}
		drawJ4();
        // Joint 5
		glTranslatef( 0.0, 0.0, pa10_j4_h);
		glRotatef(JAngle[4], 0, 0, 1);
		if (mode == GL_SELECT){
			glLoadName(5);
		}
		drawJ5();
        // Joint 5
		glTranslatef( 0.0, 0.0, pa10_j5_cover_l + pa10_j5_cover_r0);
		glRotatef(JAngle[5], 0, 1, 0);
		if (mode == GL_SELECT){
			glLoadName(6);
		}
		drawJ6();
		// Joint 6
		glTranslatef( 0.0, 0.0, pa10_j6_h);
		glRotatef(JAngle[6], 0, 0, 1);
		if (mode == GL_SELECT){
			glLoadName(7);
		}
		drawJ7();
		// Joint 7
		glTranslatef( 0.0, 0.0, pa10_j7_h);
		myglOrigin(0,0,0,100, 10);
	}
	glPopMatrix();
}
