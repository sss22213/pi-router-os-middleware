CURDIR := $(TOPDIR)/Core
PACKAGE_LIST := $(filter-out %Makefile, $(wildcard $(CURDIR)/*))

build:
	$(foreach package_name,$(PACKAGE_LIST), $(MAKE) -C $(package_name)\
					CROSS_COMPILE=$(CROSS_COMPILE)\
					TOPDIR=$(TOPDIR)\
					CORE_DIR=$(CORE_DIR)\
					BUILD_DIR=$(BUILD_DIR);)