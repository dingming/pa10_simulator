CC = gcc -g
CFLAG	= -ggdb -Wall -O3 -DMACOS

PROG = pa10simu

DEVDIR = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer

INCS = -I$(DEVDIR)/SDKs/MacOSX10.7.sdk/usr/X11/include -I$(DEVDIR)/SDKs/MacOSX10.7.sdk/usr/include -I$(DEVDIR)/SDKs/MacOSX10.7.sdk/System/Library/Frameworks/GLUT.framework/Versions/A/Headers
LIBDIR = -framework OpenGL -framework GLUT -framework Foundation
LIBS	= $(GL_LIBS) $(LIBDIR)
FLG = $(INCS) $(LIBDIR)

SRC = main.c draw.c mygl.c
HEAD = parameter.h draw.h color.h mygl.h 

OBJ = $(SRC:.c=.o)

all: $(PROG)

$(PROG): $(OBJ) $(HEAD)
	$(CC) $(CFLAG) $(INCS) $(LIBS) $(OBJ) -o $@

.c.o:
	$(CC) $(CFLAG) $(INCS) -c $<

clean: 
	$(RM) -f ~* *.o *core core

depent:
	makedepend -- $(CFLAG) $(INCS) -- $(SRC);

remake:
	make clean;
	make;
