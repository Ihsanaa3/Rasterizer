# Compilers
CXX = g++
CC  = gcc

# Compiler Flags
CXXFLAGS = -std=c++17 -Wall -Iinclude -ffunction-sections -fdata-sections
CFLAGS   = -Wall -Iinclude

# List your stationary backend files (now including glad.c inside hsource)
HSOURCE_SRCS =  hsource/extraFunctions.cpp hsource/rotation.cpp \
				hsource/tgaimage.cpp hsource/relativeResPath.cpp 
			
# Automatically turns all .cpp and .c files in HSOURCE_SRCS into .o paths
OBJS = $(patsubst hsource/%.cpp,hsource/%.o,$(filter %.cpp,$(HSOURCE_SRCS))) \
		$(patsubst hsource/%.c,hsource/%.o,$(filter %.c,$(HSOURCE_SRCS))) \	

# Default rule: just build all the object files
all: $(OBJS)

# Compilation Phase for C++ files
hsource/%.o: hsource/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation Phase for C files (like glad.c)
hsource/%.o: hsource/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	del /Q hsource\*.o 


# Comands 
# mingw32-make   
# -> compiles all cpp files into object files 

# mingw32-make clean 
# -> clears and deletes all object files created by previous command 


# C:\msys64\usr\bin\pacman.exe -Ss mingw-w64-ucrt-x86_64-python 
# -> for installing python packages