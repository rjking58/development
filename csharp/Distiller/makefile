# Makefile for XZite config file tools including the XML distiller and reader.
#

INCDIR = inc/
SRCDIR = src/
OBJDIR = obj/
CC = gcc
CFLAGS = -O2 -I$(INCDIR) -DDEBUG
vpath %.o $(OBJDIR)
vpath %.c $(SRCDIR)
vpath %.h $(INCDIR) /usr/include /usr/include/sys

DISTILLER_OBJS = distiller.o rgetopt.o strlist.o debug.o
READER_OBJS = reader.o rgetopt.o strlist.o debug.o bxml.o
ALL_OBJS = $(DISTILLER_OBJS) $(READER_OBJS)


# Rule to build all targets.
.PHONY : all
all : d r 


.PHONY : force
force: clean all


# Rule to build the Distiller executable.
d : $(DISTILLER_OBJS)
	$(CC) -o $@ $(patsubst %.o,$(OBJDIR)%.o,$(DISTILLER_OBJS))


# Rule to build the Reader executable.
r :	$(READER_OBJS)
	$(CC) -o $@ $(patsubst %.o,$(OBJDIR)%.o,$(READER_OBJS))


# Rule to make a .o from a .c file.
%.o : %.c
	$(CC) $(CFLAGS) -o $(OBJDIR)$@ -c $<


debug.o : debug.h
bxml.o : types.h ascii.h syserr.h bxml.h strlist.h debug.h
distiller.o : types.h ascii.h syserr.h rgetopt.h strlist.h bxml.h
reader.o : types.h ascii.h syserr.h strlist.h bxml.h
rgetopt.o : rgetopt.h types.h
strlist.o : strlist.h


release : CFLAGS = -O2 -DRELEASE -I$(INCDIR)
release : all
.PHONY : release

# Rule to remove all objects and the executable.

clean:

	for i in $(patsubst %.o,$(OBJDIR)%.o,$(ALL_OBJS)); do rm -f $$i; done;
	rm -f r.exe;
	rm -f d.exe;

show:

	@(echo $(ALL_OBJS))
