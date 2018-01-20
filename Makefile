CC      = gcc
CFLAGS  = -c -Wall -o
LD      = gcc
LDFLAGS = -o $(PROGRAM)
LIBS		= 
INCLUDE = -I./include
SRC_DIR = ./src
OBJ_DIR = ./build
CSRCS		= $(shell ls $(SRC_DIR)/*.c)
OBJS		= $(subst $(SRC_DIR),$(OBJ_DIR), $(CSRCS:.c=.o))
PROGRAM = test

all: $(PROGRAM)

$(PROGRAM): $(OBJS) $(LIBS)
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if [ ! -d $(OBJ_DIR) ];then \
		echo "mkdir -p $(OBJ_DIR)"; mkdir -p $(OBJ_DIR);\
	fi
	$(CC) $< $(INCLUDE) $(CFLAGS) $@

clean:
	rm $(OBJS) $(PROGRAM)

.PHONY: all clean
