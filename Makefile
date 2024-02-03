default:
	clang++ src/* -g -lglfw -std=c++11 -arch arm64 -I include -L/opt/homebrew/lib/ -framework OpenGL -lGLEW -o bin/main
clean:
	rm bin/main
