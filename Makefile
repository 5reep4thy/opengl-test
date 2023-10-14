default:
	clang++ src/main.cpp -lglfw -arch arm64 -L/opt/homebrew/lib/ -framework OpenGL -lGLEW -o bin/main
