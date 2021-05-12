CC		= gcc
CFLAGS		= -I $(INC_DIR)
LIBS		= -lbcm2835 -lshiftr

INC_DIR 	= include
SRC_DIR		= src
OBJ_DIR 	= obj

PREFIX		= /usr

_DEPS		= shiftctrl.h
DEPS		= $(patsubst %,$(INC_DIR)/%,$(_DEPS))

_OBJ		= shiftctrl.o util.o
OBJ		= $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

all: shiftctrl 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	mkdir -p $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

shiftctrl: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

install: shiftctrl clean
	mkdir -p $(PREFIX)/bin
	cp shiftctrl $(PREFIX)/bin/shiftctrl
	chmod +x $(PREFIX)/bin/shiftctrl

uninstall:
	rm -f $(PREFIX)/bin/shiftctrl

clean:
	rm -f $(OBJ_DIR)/*.o 

.PHONY: clean install uninstall
