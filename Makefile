CC = clang++
COMPILER_FLAGS = -std=c++11 -Wall -g -D SPDLOG_COMPILED_LIB
LINKER_FLAGS = -lspdlog

HEADERS = -I./include -I3rd/spdlog/include
LIBS =  -L3rd/spdlog

APP_OBJS = main.o class_file.o class_parser.o

EXE = avm.bin

class_file.o:
	$(CC) -c $(COMPILER_FLAGS) $(HEADERS) $(LIBS) $(LINKER_FLAGS) -o class_file.o src/class_file.cpp
class_parser.o:
	$(CC) -c $(COMPILER_FLAGS) $(HEADERS) $(LIBS) $(LINKER_FLAGS) -o class_parser.o src/class_parser.cpp
	
all : $(APP_OBJS)
	$(CC) $(APP_OBJS) $(COMPILER_FLAGS) $(HEADERS) $(LIBS) $(LINKER_FLAGS) -o $(EXE)


.PHONY: clean
clean:
	rm -f *.o $(EXE)


