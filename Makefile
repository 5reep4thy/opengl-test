default:
	clang++ src/main.cpp -g -lglfw -std=c++11 -arch arm64 -L/opt/homebrew/lib/ -framework OpenGL -lGLEW -o bin/main
