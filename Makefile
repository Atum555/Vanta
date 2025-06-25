# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/src
.PATH: ${.CURDIR}/src/utils
.PATH: ${.CURDIR}/src/drivers
.PATH: ${.CURDIR}/src/model
.PATH: ${.CURDIR}/src/graphics
 

# source code files to be compiled
SRCS = main.c \
		timer.c \
		kbc.c \
		keyboard.c \
		mouse.c \
		graphics.c \
		management.c \
		\
		utils.c \
		key.c \
		character.c \
		cursor.c \
		line.c \
		buffer.c \
		\
		font16x32.c \
		text_renderer.c \
		buffer_renderer.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -O3 -march=native -mtune=native

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
