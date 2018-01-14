CC      = gcc
CFLAGS  = -Wall -MMD -MP
LD      = gcc
LDFLAGS = -o $(PROGRAM)
LIBS	=
INCLUDE = -I./include
SRC_DIR = ./src
OBJ_DIR = ./build
CSRCS	= $(shell ls $(SRC_DIR)/*.c)
OBJS	= $(subst $(SRC_DIR),$(OBJ_DIR), $(CSRCS:.c=.o))
PROGRAM = memo
DEPENDS = $(OBJS:.o=.d)

all: $(PROGRAM)

$(PROGRAM): $(OBJS) $(LIBSj)
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if [ ! -d $(OBJ_DIR) ]; then \
		echo "mkdir -p $(OBJ_DIR)"; mkdir -p $(OBJ_DIR);\
	fi
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	rm $(OBJS) $(PROGRAM) $(DEPENDS)

.PHONY: all clean
