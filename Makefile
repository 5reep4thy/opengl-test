default:
	clang++ src/main.cpp -lglfw -std=c++11 -arch arm64 -L/opt/homebrew/lib/ -framework OpenGL -lGLEW -o bin/main
