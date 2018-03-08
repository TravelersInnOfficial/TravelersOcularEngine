 ifeq ($(OS),Windows_NT)
    Target				:= EngineTest.exe
    CXXFLAGS			:= -O3 -g -Wall -std=c++11 -m64
    CCFLAGS				:= -O3 -g -Wall
    CPPFLAGS        	:= -I/mingw64/include -I/mingw64/include/bullet -I./src/Common
    LDFLAGS				:= -L/mingw64/lib
    LIBS 				:= -lopengl32 -lglew32 -lassimp -lglfw3
else
    Target				:= EngineTest
    CXXFLAGS			:= -O3 -g -Wall -std=c++11
    CCFLAGS				:= -O3 -g -Wall
    CPPFLAGS        	:= -I/usr/include -I/usr/include/bullet -I./src/Common -I/usr/local/include/assimp -I/usr/include/GLFW
    LDFLAGS				:= -L./libs/Linux -L./usr/local/lib/
    LIBS 				:= -lGL -lGLEW -lassimp -lglfw
endif

BinPath 			:= ./bin
BuildPath 			:= ./obj

SOURCE_DIRS			:= $(shell find ./src -type d -not -path "./src/.vscode" -not -path "./src")
SourcePath			:= $(shell find src -name '*.c*')

CXX					:= clang++
CC					:= clang

EXECUTABLE 			:= $(BinPath)/$(Target)
OBJ					:= $(patsubst src/%.cpp,obj/%.o,$(SourcePath))
OBJ					:= $(patsubst src/%.c,obj/%.o,$(OBJ))

# Assuming four folders to ignore
SOURCE_DIRS 		:= $(patsubst ./src/%,./obj/%,$(SOURCE_DIRS))

#MAKE OPTIONS
.PHONY: all clean

all: prepare $(OBJ)
	$(info ==============================================)
	$(info Linking executable $(Target)...)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OBJ) -o $(EXECUTABLE) $(LDFLAGS) $(LIBS)
	$(info ==============================================)	
	$(info Compile OK)

obj/%.o: src/%.cpp
	$(info Compiling-> $@)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
	
obj/%.o: src/%.c
	$(info Compiling-> $@)
	@$(CC) $(CCFLAGS) $(CPPFLAGS) -c $< -o $@

prepare:
	$(info ==============================================)
	$(info Creating folder structure)
	$(info ==============================================)
	@mkdir -p $(BinPath)
	@mkdir -p $(SOURCE_DIRS)

clean:
	$(info ==============================================)
	$(info Cleaning every Objects and Binaries... )
	$(info ==============================================)
	@$(RM) $(OBJ)
	@$(RM) $(EXECUTABLE)