CC := gcc
TOPDIR := $(CURDIR)
COREDIR := $(TOPDIR)/Core
MSGDIR := $(COREDIR)/Message
BUILDDIR := $(TOPDIR)/Build
SOURCE := $(wildcard $(COREDIR)/*/src/*)
OBJ := $(patsubst %.c,%.o,$(SOURCE))
INC := $(addprefix -I,$(wildcard $(COREDIR)/*/inc))
INCMSG:=-I$(TOPDIR)/Msg/inc
BUILDOBJ := $(wildcard $(BUILDDIR)/*.o)

CFLAGS := -g -std=gnu11 $(INC) $(INCMSG) -lpaho-mqtt3a -lpaho-mqtt3c -lcjson

all: clean prepare build main

prepare:
	mkdir $(BUILDDIR)
	$(TOPDIR)/Msg/parse_c.sh

build: $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)
	mv $@ $(BUILDDIR)/$(notdir $@)

main: $(BUILDOBJ)
	$(CC) -o $@ main.c $? $(CFLAGS)

clean:
	rm -rf $(BUILDDIR)
	rm -f $(MSGDIR)/src/*.c
	rm -f $(MSGDIR)/inc/*.h
	rm -f main

.PHONY: clean prepare build





