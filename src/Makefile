CC := gcc
TOPDIR := $(CURDIR)
CORE_DIR := $(TOPDIR)/Core
BUILD_DIR := $(TOPDIR)/Build

CFLAGS := -g -Wall -std=c11 -pthread

all: clean build

build:
	mkdir $(BUILD_DIR)
	$(MAKE) -C $(CORE_DIR) \
				CROSS_COMPILE=$(CC)\
				TOPDIR=$(TOPDIR) \
				CORE_DIR=$(CORE_DIR)\
				BUILD_DIR=$(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean





