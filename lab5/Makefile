# Makefile for the lab4 driver (based on that of hello).

COMPILER_TYPE= gnu

CC=gcc

PROG=	lab5
SRCS=	lab5.c vbe.c test5.c video_gr.c timer.c keyboard.c test3.c read_xpm.c set_pixel.S

CCFLAGS= -Wall

DPADD+=	${LIBDRIVER} ${LIBSYS}
LDADD+= -llm  -ldriver -lsys 

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>

