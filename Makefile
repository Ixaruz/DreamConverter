LIBADDDIRS	:= libs/LibACNH/

# Sources
SOURCES     := 	source \
				$(foreach dir,$(LIBADDDIRS),$(dir)/source)

INCLUDES    :=  include \
                ../include

# Compiler Settings
BUILD           := build
OUTPUT          := DreamConverter
DBGFLAGS = -g -O0 -femit-class-debug-always
RELFLAGS = -O3 -s


INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBADDDIRS),-I$(CURDIR)/$(dir)/include)

CFLAGS = -flto -Wall -Wextra -I. $(INCLUDE)
CXXFLAGS = $(CFLAGS) -std=gnu++20
CC = gcc
CXX = g++
LIBS  =

	export LD	:=	$(CXX)

ifeq ($(DEBUG_MODE), 1)
	CFLAGS += $(DBGFLAGS)
else
	CFLAGS += $(RELFLAGS)
endif

ifeq ($(OS),Windows_NT)
    #Windows
    CFLAGS += -Wno-unused-but-set-variable
    LIBS += -static-libgcc -static-libstdc++
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        # OS X
        CFLAGS +=
        LIBS += -liconv
    else
        # Linux
        CFLAGS += -Wno-unused-but-set-variable
        LIBS +=
    endif
endif


#all c files
CFILES		:=	$(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))
#all cpp files
CPPFILES	:=	$(foreach dir,$(SOURCES),$(wildcard $(dir)/*.cpp))
#all assemply files
SFILES		:=	$(foreach dir,$(SOURCES),$(wildcard $(dir)/*.s))

# All .o files
OFILES	:=	$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
# Gcc/Clang will create these .d files containing dependencies.
DEPENDS = $(OBJ:%.o=%.d)


.PHONY: all clean test

all: $(OFILES)
	$(CXX) -o $(OUTPUT) $(CXXFLAGS) $(LIBS) $(OFILES)

debug: clean
	@$(MAKE) --no-print-directory DEBUG_MODE=1

clean:
	rm -rf $(OUTPUT) $(OUTPUT).exe $(OFILES)

re: clean all

test: clean all
	@echo !!! Testing now !!!
	@echo
	@./$(OUTPUT)
