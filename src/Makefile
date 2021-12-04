CC := gcc
TOPDIR := $(CURDIR)
COREDIR := $(TOPDIR)/Core
BUILDDIR := $(TOPDIR)/Build
SOURCE := $(wildcard $(COREDIR)/*/src/*)
OBJ := $(patsubst %.c,%.o,$(SOURCE))
INC := $(addprefix -I,$(wildcard $(COREDIR)/*/inc))

CFLAGS := -g -std=gnu11 -pthread $(INC)

all: clean prepare build

prepare:
	mkdir $(BUILDDIR)

build: $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)
	mv $@ $(BUILDDIR)/$(notdir $@)

clean:
	rm -rf $(BUILDDIR)

.PHONY: clean prepare build buildmain





