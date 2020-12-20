#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -O3

#This is the target that compiles our executable

default: build

build:
	g++ *.cpp -o app.exe $(COMPILER_FLAGS) && app.exe
