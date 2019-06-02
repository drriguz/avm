CC = clang++
COMPILER_FLAGS = -std=c++11 -Wall
LINKER_FLAGS =

HEADERS =
LIBS = 

APP_OBJS = main.cpp

EXE = hello

all : $(APP_OBJS)
	$(CC) $(APP_OBJS) $(COMPILER_FLAGS) $(HEADERS) $(LIBS) $(LINKER_FLAGS) -o $(EXE)

.PHONY: clean
clean:
	rm -f *.o $(EXE)


