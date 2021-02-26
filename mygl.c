#include "mygl.h"

void SetNormal(double *p1,double *p2,double*p3,double *normal)
{
	//double normal[3];
	double x1=p1[0]-p2[0],x2=p2[0]-p3[0];
	double y1=p1[1]-p2[1],y2=p2[1]-p3[1];
	double z1=p1[2]-p2[2],z2=p2[2]-p3[2];
	double det=0;
	int i;

	normal[0]=y1*z2-y2*z1;
	normal[1]=z1*x2-z2*x1;
	normal[2]=-x1*y2+x2*y1;
	
	for(i=0;i<3;i++){
		det += normal[i]*normal[i];
	}
	
	det = sqrt(det);

	for(i=0;i<3;i++){
		normal[i] /= det;
	}
	//glNormal3dv(normal);
}


void myglCylinder(double r0, double r1, double l, int st)
{
    int i;
	double normal[3];
	glPushMatrix();
	for(i = 1; i <= st; i++) {
		double lng0 = 2 * M_PI * (double) (i-1) / st;
		double x0 = cos(lng0);
		double y0 = sin(lng0);

		double lng1 = 2 * M_PI * (double) i / st;
		double x1 = cos(lng1);
		double y1 = sin(lng1);
		
		double p[3][3];
		
		// bottom
		p[0][0] = 0;p[0][1] = 0; p[0][2]= 0;
		p[1][0] = x0 * r1;p[1][1] =  y0 * r1; p[1][2]= 0;
		p[2][0] = x1 * r1;p[2][1] =  y1 * r1; p[2][2]= 0;
		SetNormal(p[0],p[1],p[2],normal);
		glNormal3dv(normal);
		glBegin(GL_POLYGON);
		glVertex3f(0, 0, 0);
		glVertex3f(x0 * r0, y0 * r0, 0);
		glVertex3f(x1 * r0, y1 * r0, 0);
		glEnd();

		// Cylinder
		p[0][0] = x0 * r0;p[0][1] =  y0 * r0; p[0][2]= 0;
		p[1][0] = x0 * r1;p[1][1] =  y0 * r1; p[1][2]= l;
		p[2][0] = x1 * r1;p[2][1] =  y1 * r1; p[2][2]= l;

		SetNormal(p[2],p[1],p[0],normal);
		glNormal3dv(normal);
		glBegin(GL_POLYGON);
		glVertex3f(x0 * r0, y0 * r0, 0);
		glVertex3f(x0 * r1, y0 * r1, l);
		glVertex3f(x1 * r1, y1 * r1, l);
		glVertex3f(x1 * r0, y1 * r0, 0);
		glEnd();

		// top
		p[0][0] = 0;p[0][1] = 0; p[0][2]= l;
		p[1][0] = x0 * r1;p[1][1] =  y0 * r1; p[1][2]= l;
		p[2][0] = x1 * r1;p[2][1] =  y1 * r1; p[2][2]= l;
		SetNormal(p[2],p[1],p[0],normal);
		glNormal3dv(normal);
		glBegin(GL_POLYGON);
		glVertex3f(0, 0, l);
		glVertex3f(x0 * r1, y0 * r1, l);
		glVertex3f(x1 * r1, y1 * r1, l);
		glEnd();
	}	
	glPopMatrix();
}

void myglTrapezium(double r0, double r1, double l, double h, int st)
{
    int i;
	double normal[3];
	double p[3][3];

	glPushMatrix();
	for(i = 1; i <= st/2; i++) {
		double lng0 = 2 * M_PI * (double) (i-1) / st;
		double x0 = cos(lng0);
		double y0 = sin(lng0);
		double lng1 = 2 * M_PI * (double) i / st;
		double x1 = cos(lng1);
		double y1 = sin(lng1);
		
		// bottom
		p[0][0] = 0;p[0][1] = 0; p[0][2]= 0;
		p[1][0] = x0 * r1;p[1][1] =  y0 * r1; p[1][2]= 0;
		p[2][0] = x1 * r1;p[2][1] =  y1 * r1; p[2][2]= 0;
		SetNormal(p[0],p[1],p[2],normal);
		glNormal3dv(normal);
		glBegin(GL_POLYGON);
		glVertex3f(0, 0 + (l/2), 0);
		glVertex3f(x0 * r0, y0 * r0 + (l/2), 0);
		glVertex3f(x1 * r0, y1 * r0 + (l/2), 0);
		glEnd();

		// Cylinder
		p[0][0] = x0 * r0;p[0][1] =  y0 * r0; p[0][2]= 0;
		p[1][0] = x0 * r1;p[1][1] =  y0 * r1; p[1][2]= h;
		p[2][0] = x1 * r1;p[2][1] =  y1 * r1; p[2][2]= h;
		SetNormal(p[2],p[1],p[0],normal);
		glNormal3dv(normal);
		glBegin(GL_POLYGON);
		glVertex3f(x0 * r0, y0 * r0 + (l/2), 0);
		glVertex3f(x0 * r1, y0 * r1 + (l/2), h);
		glVertex3f(x1 * r1, y1 * r1 + (l/2), h);
		glVertex3f(x1 * r0, y1 * r0 + (l/2), 0);
		glEnd();

		// top
		p[0][0] = 0;p[0][1] = 0; p[0][2]= h;
		p[1][0] = x0 * r1;p[1][1] =  y0 * r1; p[1][2]= h;
		p[2][0] = x1 * r1;p[2][1] =  y1 * r1; p[2][2]= h;
		SetNormal(p[2],p[1],p[0],normal);
		glNormal3dv(normal);
		glBegin(GL_POLYGON);
		glVertex3f(0, 0 + (l/2), h);
		glVertex3f(x0 * r1, y0 * r1 + (l/2), h);
		glVertex3f(x1 * r1, y1 * r1 + (l/2), h);
		glEnd();
	}	

	p[0][0] = r0;p[0][1] = 0 + (l/2); p[0][2]= 0;
	p[1][0] = -r0;p[1][1] = 0 + (l/2); p[1][2]= 0;
	p[2][0] = -r0;p[2][1] = 0 - (l/2); p[2][2]= 0;
	SetNormal(p[0],p[1],p[2],normal);
	glNormal3dv(normal);
	glBegin(GL_POLYGON);
	glVertex3f(r0, 0 + (l/2), 0);
	glVertex3f(-r0, 0 + (l/2), 0);
	glVertex3f(-r0, 0 - (l/2), 0);
	glVertex3f(r0, 0 - (l/2), 0);
	glEnd();
	
	p[0][0] = r1;p[0][1] = 0 + (l/2); p[0][2]= h;
	p[1][0] = r0;p[1][1] = 0 + (l/2); p[1][2]= 0;
	p[2][0] = r0;p[2][1] = 0 - (l/2); p[2][2]= 0;
	SetNormal(p[2],p[1],p[0],normal);
	glNormal3dv(normal);
	glBegin(GL_POLYGON);
	glVertex3f(r1, 0 + (l/2), h);
	glVertex3f(r0, 0 + (l/2), 0);
	glVertex3f(r0, 0 - (l/2), 0);
	glVertex3f(r1, 0 - (l/2), h);
	glEnd();

	p[0][0] = -r1;p[0][1] = 0 + (l/2); p[0][2]= h;
	p[1][0] = -r0;p[1][1] = 0 + (l/2); p[1][2]= 0;
	p[2][0] = -r0;p[2][1] = 0 - (l/2); p[2][2]= 0;
	SetNormal(p[0],p[1],p[2],normal);
	glNormal3dv(normal);
	glBegin(GL_POLYGON);
	glVertex3f(-r1, 0 + (l/2), h);
	glVertex3f(-r0, 0 + (l/2), 0);
	glVertex3f(-r0, 0 - (l/2), 0);
	glVertex3f(-r1, 0 - (l/2), h);
	glEnd();

	p[0][0] = r1;p[0][1] = 0 + (l/2); p[0][2]= h;
	p[1][0] = -r1;p[1][1] = 0 + (l/2); p[1][2]= h;
	p[2][0] = -r1;p[2][1] = 0 - (l/2); p[2][2]= h;
	SetNormal(p[2],p[1],p[0],normal);
	glNormal3dv(normal);
	glBegin(GL_POLYGON);
	glVertex3f(r1, 0 + (l/2), h);
	glVertex3f(-r1, 0 + (l/2), h);
	glVertex3f(-r1, 0 - (l/2), h);
	glVertex3f(r1, 0 - (l/2), h);
	glEnd();

	for(i = (st/2)+1; i <= st; i++) {
		double lng0 = 2 * M_PI * (double) (i-1) / st;
		double x0 = cos(lng0);
		double y0 = sin(lng0);
		double lng1 = 2 * M_PI * (double) i / st;
		double x1 = cos(lng1);
		double y1 = sin(lng1);
		
		// bottom
		p[0][0] = 0;p[0][1] = 0; p[0][2]= 0;
		p[1][0] = x0 * r1;p[1][1] =  y0 * r1; p[1][2]= 0;
		p[2][0] = x1 * r1;p[2][1] =  y1 * r1; p[2][2]= 0;
		SetNormal(p[0],p[1],p[2],normal);
		glNormal3dv(normal);
		glBegin(GL_POLYGON);
		glVertex3f(0, 0 - (l/2), 0);
		glVertex3f(x0 * r0, y0 * r0 - (l/2), 0);
		glVertex3f(x1 * r0, y1 * r0 - (l/2), 0);
		glEnd();

		// Cylinder
		p[0][0] = x0 * r0;p[0][1] =  y0 * r0; p[0][2]= 0;
		p[1][0] = x0 * r1;p[1][1] =  y0 * r1; p[1][2]= h;
		p[2][0] = x1 * r1;p[2][1] =  y1 * r1; p[2][2]= h;
		SetNormal(p[2],p[1],p[0],normal);
		glNormal3dv(normal);
		glBegin(GL_POLYGON);
		glVertex3f(x0 * r0, y0 * r0 - (l/2), 0);
		glVertex3f(x0 * r1, y0 * r1 - (l/2), h);
		glVertex3f(x1 * r1, y1 * r1 - (l/2), h);
		glVertex3f(x1 * r0, y1 * r0 - (l/2), 0);
		glEnd();

		// top
		p[0][0] = 0;p[0][1] = 0; p[0][2]= h;
		p[1][0] = x0 * r1;p[1][1] =  y0 * r1; p[1][2]= h;
		p[2][0] = x1 * r1;p[2][1] =  y1 * r1; p[2][2]= h;
		SetNormal(p[2],p[1],p[0],normal);
		glNormal3dv(normal);
		glBegin(GL_POLYGON);
		glVertex3f(0, 0 - (l/2), h);
		glVertex3f(x0 * r1, y0 * r1 - (l/2), h);
		glVertex3f(x1 * r1, y1 * r1 - (l/2), h);
		glEnd();
	}	

	glPopMatrix();
}


/************************************/
/*ox,oy,oz : origin position        */
/*	axisl: length of every axis     */
/*	r: arrow                        */
/************************************/
void myglOrigin(double ox, double oy, double oz, double axisl, double r)
{
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(ox,oy,oz);
		glBegin(GL_LINES);
		// x-axis
		glColor3f(1,0,0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(axisl, 0.0, 0.0);
		glEnd();
		glPushMatrix();
		glTranslatef(axisl, 0.0, 0.0);
		glRotatef(90, 0,1,0);
		glutSolidCone( r, 4*r, 8, 8);
		glPopMatrix();
		// y-axis
		glBegin(GL_LINES);
		glColor3f(0,1,0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, axisl, 0.0);
		glEnd();
		glPushMatrix();
		glTranslatef(0.0, axisl, 0.0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone( r, 4*r, 8, 8);
		glPopMatrix();
		// z-axis
		glBegin(GL_LINES);
		glColor3f(0,0,1);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, axisl);
		glEnd();
		glPushMatrix();
		glTranslatef(0.0, 0.0, axisl);
		glutSolidCone( r, 4*r, 8, 8);
		glPopMatrix();
		// origin point

		glColor3f(1,0,0);
		glutSolidSphere(r, 8, 8);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}
