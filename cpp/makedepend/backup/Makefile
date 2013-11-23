#
#	$Source: /afs/athena.mit.edu/mit/zephyr/src/makedepend.new/RCS/Makefile,v $
#	$Author: jtkohl $
#	$Header: /afs/athena.mit.edu/mit/zephyr/src/makedepend.new/RCS/Makefile,v 1.2 89/07/25 09:08:21 jtkohl Exp $
#	$Locker:  $
#
# Makefile for the "makedepend" routine.  This file was derived from
# the Makefile in the X11 release sources.

CC = cc -Dsvr4
CPP = /lib/cpp
LD = ld
MAKE = make
DEPEND = /usr/athena/makedepend
CDEBUGFLAGS = -g
DESTDIR =

TAGS = ctags
CFLAGS = $(CDEBUGFLAGS) $(INCLUDES) $(DEFINES)
LDFLAGS = $(CDEBUGFLAGS) $(SYS_LIBRARIES)
RM_CMD = rm -f *.CKP *.ln *.BAK *.bak *.o core errs ,* *~ *.a \
 	 tags TAGS make.log cpp.c cpy.? yylex.c

# Sources for C preprocessor:
# Note, that if these are not available, remove cpp.c and cpy.y from SRCS
# and the -DCPP from the DEFINES.
#   SRCS = include.c main.c parse.c pr.c cppsetup.c cpp.c cpy.y
#   OBJS = include.o main.o parse.o pr.o cppsetup.o cpp.o cpy.o
#DEFINES = -DCPP '-DINCLUDEDIR="/usr/include"'

# We are currently running without the preprocessor sources
# (these sources are somewhat vendor specific)

    SRCS = include.c main.c parse.c pr.c cppsetup.c
    OBJS = include.o main.o parse.o pr.o cppsetup.o
 DEFINES = '-DINCLUDEDIR="/usr/include"'


all: makedepend

makedepend: $(OBJS)
	rm -f $@
	$(CC) -o $@ $(OBJS)  $(LDFLAGS)

$(CPPSRC)/cpy.y:
	make md -DCPPSRC=/source/`machtype`/lib/cpp

cpy.c: cpy.y yylex.c
	yacc cpy.y
	sed -e '/^# *line/d' < y.tab.c > cpy.c
	rm -f y.tab.c

cpy.y: $(CPPSRC)/cpy.y
	rm -f $@
	cp $(CPPSRC)/cpy.y .

yylex.c: $(CPPSRC)/yylex.c
	rm -f $@
	sed -e 's/#if pdp11 | vax | mc68000/& | ns16000 | ibm032/' \
		$(CPPSRC)/yylex.c > yylex.c

cpp.c: $(CPPSRC)/cpp.c cpp.ed
	rm -f cpp.c
	/lib/cpp $(CPPSRC)/cpp.c \
		| cb \
		| sed -e '/^$$/d' -e '/^#/d' -e 's/	/ /g' > cpp.c
	sed -e '/^#/d' < cpp.ed | ed - cpp.c

cpp.o: cpp.c
cpy.o: cpy.c

clean:
	rm -f makedepend $(RM_CMD) \#* *.o

depend:
	$(DEPEND) -s "# DO NOT DELETE" $(CFLAGS) $(SRCS)

tags:
	$(TAGS) -w *.[ch]
	$(TAGS) -xw *.[ch] > TAGS

install:
	install -s -c -m 755 makedepend $(DESTDIR)/usr/athena
	install -c -m 0444 makedepend.1 $(DESTDIR)/usr/man/man1


# DO NOT DELETE

include.o: def.h /usr/include/stdio.h /usr/include/ctype.h
include.o: /usr/include/sys/types.h /usr/include/fcntl.h
include.o: /usr/include/sys/stat.h
main.o: def.h /usr/include/stdio.h /usr/include/ctype.h
main.o: /usr/include/sys/types.h /usr/include/fcntl.h /usr/include/sys/stat.h
main.o: /usr/include/sys/signal.h
parse.o: def.h /usr/include/stdio.h /usr/include/ctype.h
parse.o: /usr/include/sys/types.h /usr/include/fcntl.h
parse.o: /usr/include/sys/stat.h /usr/include/sys/signal.h
pr.o: def.h /usr/include/stdio.h /usr/include/ctype.h
pr.o: /usr/include/sys/types.h /usr/include/fcntl.h /usr/include/sys/stat.h
cppsetup.o: def.h /usr/include/stdio.h /usr/include/ctype.h
cppsetup.o: /usr/include/sys/types.h /usr/include/fcntl.h
cppsetup.o: /usr/include/sys/stat.h
cpy.o: yylex.c
