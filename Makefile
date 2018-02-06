ifeq ($(OS),Windows_NT)
    Target				:= EngineTest.exe
    CXXFLAGS			:= -O3 -ffast-math -Wall -std=c++11 -m64
    CPPFLAGS        	:= -I./src/Includes -I/mingw64/include -I/mingw64/include/bullet
    LDFLAGS				:= -L/mingw64/lib
    LIBS 				:= -lopengl32 -lm -lIrrlicht -lBulletDynamics -lBulletCollision -lLinearMath -lRakNet -lfmod64 -lfmodstudio64
else
    Target				:= EngineTest
    CXXFLAGS			:= -O3 -g -Wall -std=c++11
    CPPFLAGS        	:= -I/usr/include -I/usr/include/bullet -I./src/Includes
    LDFLAGS				:= -L./libs/Linux
    LIBS 				:= -lIrrlicht -lXxf86vm -lXext -lX11 -lXcursor -lGL 
endif

BinPath 			:= ./bin
BuildPath 			:= ./obj

SOURCE_DIRS			:= $(shell find ./src -type d -not -path "./src/.vscode" -not -path "./src")
SourcePath			:= $(shell find src -name '*.cpp')

CXX					:= clang++

EXECUTABLE 			:= $(BinPath)/$(Target)
SRC 	   			:= $(wildcard $(SourcePath)/*.cpp)
OBJ					:= $(patsubst src/%.cpp,obj/%.o,$(SourcePath))

# Assuming four folders to ignore
SOURCE_DIRS 		:= $(patsubst ./src/%,./obj/%,$(SOURCE_DIRS))

#MAKE OPTIONS
.PHONY: all clean cleanall

all: prepare $(OBJ)
	$(info ==============================================)
	$(info Linking executable $(Target)...)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OBJ) -o $(EXECUTABLE) $(LDFLAGS) $(LIBS)
	$(info ==============================================)	
	$(info Compile OK)

obj/%.o: src/%.cpp
	$(info Compiling-> $@)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

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