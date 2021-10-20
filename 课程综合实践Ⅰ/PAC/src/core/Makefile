include ../../Makefile.inc

CORE_MODULE := $(patsubst %.c, %_c.o, $(wildcard *.c))
CORE_MODULE += $(patsubst %.cc, %_cc.o, $(wildcard *.cc))
CORE_MODULE += $(patsubst %.cpp, %_cpp.o, $(wildcard *.cpp))
CORE_MODULE += $(patsubst %.cxx, %_cxx.o, $(wildcard *.cxx))

CORE_PROJECT_ROOT_DIR := $(subst src/core,,$(CURRENT_DIR))

#这个很重要，否则每次会因为找不到相应的文件而重新编译
#VPATH = ../../obj/:../../lib
#下面这两行与上面这行等价
vpath %.o $(CORE_PROJECT_ROOT_DIR)/obj/
vpath %.a $(CORE_PROJECT_ROOT_DIR)/lib/


CORE_MODULE_TO_ARCHIVE := $(addprefix $(CORE_PROJECT_ROOT_DIR)/obj/, $(CORE_MODULE))

STATIC_LIB_NAME := libcore.a
define compile-cmd
        $(CC) $(CFLAGS) -I$(INC_PATH) -I$(EXTERNAL_INC_PATH) -I$(EXTERNAL_INC_EIGEN_PATH) -L$(LIB_PATH) -L$(EXTERNAL_LIB_PATH) -o 
$(addprefix ../../obj/, $@) -c $<
endef
define archive-cmd
        $(AR) $(ARFLAGS) -o $(addprefix ../../lib/, $@) $(CORE_MODULE_TO_ARCHIVE)
endef
all:$(CORE_MODULE) $(STATIC_LIB_NAME)
%_c.o:%.c
        $(compile-cmd)
%_cc.o:%.cc
        $(compile-cmd)
%_cpp.o:%.cpp
        $(compile-cmd)
%_cxx.o:%.cxx
        $(compile-cmd)
$(STATIC_LIB_NAME):$(CORE_MODULE)
        rm -rf ../../bin/*
        $(archive-cmd)
.phony:clean
clean:
        rm -rf ../../lib/$(STATIC_LIB_NAME)