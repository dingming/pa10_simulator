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

#include "draw.h"

#define BUFSIZE	(512)

double rotspeed = 5.0;
double JAngle[7]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
int njoint=-1;

GLfloat vh = 0.0; //set the angle of rotation
GLfloat vv = 0.0; //set the angle of rotation
int vr = 2000;

int clicked=0,nbutton=0;
int bmx=0,bmy=0;//the mouse position before
double tx=0,ty=0,tz=0;

const GLfloat light_position0[] = {2000.0, 1600.0, 2000.0, 1.0 };
const GLfloat light_position1[] = {-2000.0, 1600.0, 2000.0, 1.0};
const GLfloat light_position2[] = {-2000.0, -2000.0, 2000.0, 1.0};

void print_help()
{
	printf("MOUSE:\n");
	printf("\tLeft_Button: \tSelect joint\n");
	printf("\tRight_Button: \tMove View Point\n");
	printf("\tMiddle_Button: \tRotate View Point\n");
	printf("\tWheel_Up/Down: \tMove Joint\n");
	printf("KEY:\n");
	printf("\t\"1~7\": \t\tSelet joint\n");
	printf("\t\"-/+\": \t\tMove joint\n");
	printf("\t\"q/ESC\": \tQuit\n");
}

void light(void){
/* 	GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; //set the light specular to white */
	GLfloat whiteSpecularLight0[] = {0.5, 0.5, 0.5}; //set the light specular to white
	GLfloat whiteSpecularLight2[] = {0.1, 0.1, 0.1}; //set the light specular to white
	GLfloat blackAmbientLight[] = {0.2, 0.2, 0.2}; //set the light ambient to black
/* 	GLfloat whiteAmbientLight[] = {1.0, 1.0, 1.0}; //set the light ambient to white */
	GLfloat whiteDiffuseLight[] = {0.8, 0.8, 0.8}; //set the diffuse light to white
	GLfloat whiteDiffuseLight2[] = {0.1, 0.1, 0.1}; //set the diffuse light to white
/* 	GLfloat greenDiffuse[]={0.0, 1.0, 0.0, 1.0}; */

	GLfloat lmodel_ambient[]={0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	GLfloat light_position1[] = { -2000.0, 1600.0, 2000.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_SPECULAR, whiteSpecularLight0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, blackAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteDiffuseLight);
	glLightfv (GL_LIGHT1, GL_POSITION, light_position1);

	//GLfloat light_position2[] = { -2000.0, 1600.0, 2000.0, 1.0 };
	GLfloat light_position2[] = { -2000.0, -2000.0, 2000.0, 1.0 };
	glLightfv(GL_LIGHT2, GL_SPECULAR, whiteSpecularLight2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, blackAmbientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, whiteDiffuseLight2);
	glLightfv (GL_LIGHT2, GL_POSITION, light_position2);

	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
/* 	glEnable (GL_LIGHT1); */
	glEnable (GL_LIGHT2);
}

void init(void){
	//glClearColor (0.2,0.2,0.3,1.0);
	//glClearColor (0.1,0.1,0.1,1.0); // grey
/* 	glClearColor (1,1,1,1.0); // white */
	glClearColor (0.0,0.0,0.0,1.0); // black

	glColorMaterial(GL_BACK, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glEnable (GL_DEPTH_TEST);
/* 	glEnable (GL_LIGHTING); */
}

void view(void){
	gluLookAt (0.0, vr, 1000.0,
			   0.0, 0.0, 500.0,
			   0.0, 0.0, 1.0);
	glRotatef(vv, 1.0, 0.0, 0.0);
	glRotatef(vh, 0.0, 0.0, 1.0);
}

void showlight(void)
{
	glPushMatrix();
	{
		glTranslatef( light_position0[0], light_position0[1], light_position0[2]);
		glutSolidSphere(50,50,32);
	}
	glPopMatrix();

/* 	glPushMatrix(); */
/* 	{ */
/* 		glTranslatef( light_position1[0], light_position1[1], light_position1[2]); */
/* 		glutSolidSphere(50,50,32); */
/* 	} */
/* 	glPopMatrix(); */

	glPushMatrix();
	{
		glTranslatef( light_position2[0], light_position2[1], light_position2[2]);
		glutSolidSphere(50,50,32);
	}
	glPopMatrix();
}

void display (void)
{
	glClearDepth(1);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	view();
	light();

	// Show Light Position
	showlight();

/* 	drawObjectArea(500, 500, 500, 50); */
	drawFloor(1500, 15); // Floor
	draw_pa10(GL_RENDER);
	glutSwapBuffers();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100000.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard (unsigned char key, int x, int y)
{
	int i;
	if(key>='1' && key<='7'){
		njoint = atoi((char *)&key)-1;
	}
	switch(key)	{
	case '-':
	case '_':
		JAngle[njoint]-=rotspeed;
		break;
	case '=':
	case '+':
		JAngle[njoint]+=rotspeed;
		break;
	case 'r':
		for(i=0;i<7;i++) JAngle[i]=0;
		break;
	case 27:
	case 'q':
		exit (0);
	}
}

void processHits (GLint hits, GLuint buffer[])
{
/* 	int i; */
/* 	printf("hits = %d\n", hits); */
/* 	for(i=0;i<hits;i++){ */
/* 		printf("buffer[%d] = %d\n", i, buffer[i]); */
/* 	} */

/*   int i; */
/*   unsigned int j; */
  GLuint names, *ptr;

/*   printf("hits = %d\n", hits); */
  ptr = (GLuint *) buffer;
/*   for (i = 0; i < hits; i++) {  /\* for each hit  *\/ */
    names = *ptr;
/*     printf(" number of names for hit = %d\n", names); */
    ptr++;
/*     printf("  z1 is %g;", (float) *ptr/0xffffffff); */
    ptr++;
/*     printf(" z2 is %g\n", (float) *ptr/0xffffffff); */
    ptr++;
/*     printf("   the name is "); */
	njoint = *ptr-1;
/*     for (j = 0; j < names; j++) {  /\* for each name *\/ */
/*       printf("%d ", *ptr); */
/*       ptr++; */
/*     } */
/*     printf("\n"); */
/*   } */
	if(njoint<0) njoint=-1;
	if(njoint>6) njoint=6;
}

void selection(int x, int y)
{
   GLuint selectBuf[BUFSIZE];
   GLint hits=-1;
   GLint viewport[4];
   float current_aspect=0.0;
   glGetIntegerv (GL_VIEWPORT, viewport);
   glSelectBuffer (BUFSIZE, selectBuf);
   (void) glRenderMode (GL_SELECT);

   glInitNames();
   glPushName(0);

   glMatrixMode (GL_PROJECTION);

   glPushMatrix ();{
		glLoadIdentity ();
		gluPickMatrix ((GLdouble) ( x),  (GLdouble) (viewport[3] - y),
					   5.0, 5.0, viewport);
		current_aspect = (float)viewport[2]/(float)viewport[3];
		gluPerspective (60, current_aspect, 1.0, 100000.0);
/* 		gluPerspective(60, current_aspect, 1.0, 100.0); */
		glMatrixMode (GL_MODELVIEW);

		draw_pa10(GL_SELECT);
		glMatrixMode (GL_PROJECTION);
   }
   glPopMatrix ();

   hits = glRenderMode (GL_RENDER);
   processHits (hits, selectBuf);
   glMatrixMode (GL_MODELVIEW);
/*    glutPostRedisplay(); */
}

void mouse(int button, int state, int x, int y){
	clicked = state; nbutton=button;
	if(clicked==1){
		switch(button){
		case GLUT_LEFT_BUTTON:
/* 			printf("Select\n"); */
			selection(x, y);
			break;
		case 3:
/* 			printf("up\n"); */
			JAngle[njoint]+=rotspeed;
			break;
		case 4:
/* 			printf("down\n"); */
			JAngle[njoint]-=rotspeed;
			break;
		}
	}
}

void motion(int x, int y){
	int dx=0,dy=0;
	//double C1,C2,S1,S2;
	if(clicked == 0){
		dx = x - bmx;
		dy = y - bmy;
//		printf("%d,%d\n",dx,dy);
		if( abs(dx) > 50 || abs(dy) > 50 ){
			dx=0;dy=0;
		}
		switch(nbutton) {
		case GLUT_RIGHT_BUTTON:
			vr +=(10*dy);
			if(vr<100) vr=100;
			if(vr>10000) vr=10000;
			glutPostRedisplay();
			break;
		case GLUT_MIDDLE_BUTTON:
			vh += dx; 
			vv -= dy;
			glutPostRedisplay();
			break;
		}
		bmx = x; bmy = y;
	}
}

void idle(void)
{
	display();
}

int main (int argc, char **argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_RGB); 
	glutInitWindowSize (1000, 1000);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("PA10 Simulation");
	init();
	glutDisplayFunc (display);
	glutIdleFunc (idle);
	glutKeyboardFunc (keyboard);
	glutMouseFunc   ( mouse ); 
	glutMotionFunc( motion );
	glutReshapeFunc (reshape);
	print_help();
	glutMainLoop ();
	return 0;
}
