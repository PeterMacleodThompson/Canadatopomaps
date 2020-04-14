############################################################
# Peter Thompson May 2015
# oz3 makefile for Canada/topographic maps
# make    runs this makefile
#
# $@ is left side of :
# $^ is right side of :
# $< is 1st dependency of right side of : 

# debug make -d 
# make -p with no makefile dumps database of variables, implicit rules
######################################################################

# source *.c and object *.o subdirectories
SRCDIR = src
OBJDIR = obj


# create a list of source filenames
# SOURCES = extracts all *.c files in the directory specified,
# directory path stripped.   New source directories must be added here!
SOURCES = $(notdir $(wildcard *.c)) \
          $(notdir $(wildcard ./fcninit/*.c)) \
          $(notdir $(wildcard ../1m/run/src/gateway/*.c)) \
          $(notdir $(wildcard ../250k/run/src/gateway/*.c)) \
          $(notdir $(wildcard ../50k/run/src/gateway/*.c)) \
          $(notdir $(wildcard ../250k/run/src/navigate/*.c)) \
          $(notdir $(wildcard ../50k/run/src/navigate/*.c)) \
          $(notdir $(wildcard ./collar/*.c)) \
          $(notdir $(wildcard ../250k/run/src/longlat/*.c)) \
          $(notdir $(wildcard ../50k/run/src/longlat/*.c)) \
          $(notdir $(wildcard /home/peter/bbb2020/oznext/src/init/*.c))

# count and print number of .c files found
FILECOUNT = $(words $(SOURCES))
$(warning  $(FILECOUNT) c programs to be compiled and linked)
$(info  SOURCES ARE AS FOLLOWS $(SOURCES)   )
$(info Expected 29 source files to be compiled! Does it match $(FILECOUNT) )

# define path to souce filenames.  New source directories must be added here!
VPATH = ./fcninit/ : ./collar/ : ../1m/run/src/gateway/ : ../250k/run/src/gateway/ : ../50k/run/src/gateway/ : ../250k/run/src/navigate/ :  ../50k/run/src/navigate/ : ../250k/run/src/longlat/ : ../50k/run/src/longlat/ : /home/peter/bbb2020/oznext/src/init/


# create list of object filenames *.0 from source filenames *.c and print them
XOBJECTS = $(SOURCES:.c=.o)  
OBJECTS = $(patsubst %,$(OBJDIR)/%,$(XOBJECTS))  # prefix with obj/ directory
 $(warning OBJECTS is $(OBJECTS))     # print list of object files for debug


# name executable
EXECUTABLE = main2fortesting         


# compiler and compiler flags to use 
CC = gcc
CFLAGS += -I include/  # -c -M -I  -M replaces makedepend command 
DEBUG = -g   # -g for gdb 
LDFLAGS += # -L /home/peter/Documents/oz/usr/lib/  directory location of libraries
LDLIBS += -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf 




#################################################################
# This is the guts of make - and it is complex!!!!   DO NOT TOUCH
################################################################

.PHONY: all clean distclean help


all: $(EXECUTABLE)     

# gcc obj/myfile1.o obj/myfile2.o... -o ozimage
$(EXECUTABLE): $(OBJECTS)
	@echo Peter linking
	$(CC) $(DEBUG) -o $@ $^ $(LDFLAGS) $(LDLIBS)

# gcc -c src/gofindmeVPATH/myfile1.c....  -o obj/myfile1.o   NOTE %.o: %.c is a convention
$(OBJDIR)/%.o: %.c
	@echo Peter compiling
	$(CC) $(DEBUG) -Wall -c $(CFLAGS) $< -o $@

#####################################################################

clean:
	@echo removing contents of obj and main2fortesting
	rm -v ./obj/*.o; rm -v main2fortesting

distclean:
	@echo removing contents of obj,  main2fortesting and sourcebackup~
	rm -v ./obj/*.o; rm -v main2fortesting; rm -v ./src/hello/*~

help:
	@echo Help is here from Peter 
	@echo Enter helpinfo here....  






