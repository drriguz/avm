CC = clang++
COMPILER_FLAGS = -std=c++11 -Wall -g -D SPDLOG_COMPILED_LIB
LINKER_FLAGS = -lspdlog

HEADERS = -I./include -I3rd/spdlog/include
LIBS =  -L3rd/spdlog

APP_OBJS = main.cpp \
		src/class_file.cpp \
		src/class_parser.cpp

EXE = avm.bin
	
all : $(APP_OBJS)
	$(CC) $(APP_OBJS) $(COMPILER_FLAGS) $(HEADERS) $(LIBS) $(LINKER_FLAGS) -o $(EXE)


.PHONY: clean
clean:
	rm -f *.o $(EXE)


